// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: Create triggers necessary for scheduling across
//                         virtual interfaces
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2003-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************
// V3SchedVirtIface's Transformations:
//
// Identify interface members written through virtual interface variables (VIF writes).
// For each such member, collect all VarScopes across all instantiations of that
// interface type. Each VarScope gets its own value-change trigger in the scheduler.
//
// Also disables lifetime optimization for variables in AlwaysPost blocks that
// write through virtual interfaces.
//
//*************************************************************************

#include "V3PchAstNoMT.h"  // VL_MT_DISABLED_CODE_UNIT

#include "V3AstNodeExpr.h"
#include "V3Sched.h"
#include "V3Stats.h"

VL_DEFINE_DEBUG_FUNCTIONS;

namespace V3Sched {

namespace {

class VirtIfaceVisitor final : public VNVisitor {
private:
    // STATE
    using IfaceMember = std::pair<const AstIface*, std::string>;
    using IfaceCallable = std::pair<AstIface*, AstCFunc*>;

    // Set of (iface, member) pairs written through VIF -- defines which members need triggers
    std::set<IfaceMember> m_vifWrittenMembers;
    // All candidate VarScopes of interface members (keyed by interface type + member name)
    std::map<IfaceMember, std::vector<AstVarScope*>> m_candidateVscps;
    std::set<std::pair<IfaceMember, AstVarScope*>> m_seenCandidateVscps;
    // VarScope index and callable worklist for VIF method-body writes.
    std::map<const AstVar*, std::vector<AstVarScope*>> m_vscpsByVar;
    // Worklist of reachable interface callables
    std::vector<IfaceCallable> m_reachableIfaceCallables;
    // Callables already added to the worklist
    std::set<IfaceCallable> m_seenReachableIfaceCallables;
    VirtIfaceTriggers m_triggers;  // Triggers found for virtual interface writes

    // METHODS
    // Returns true if statement writes across a virtual interface boundary
    static bool writesToVirtIface(const AstNode* const nodep) {
        return nodep->exists([](const AstMemberSel* const memberSelp) {
            if (!memberSelp->access().isWriteOrRW()) return false;
            AstIfaceRefDType* const dtypep
                = VN_CAST(memberSelp->fromp()->dtypep()->skipRefp(), IfaceRefDType);
            return dtypep && dtypep->isVirtual();
        });
    }

    // VISITORS
    void visit(AstMemberSel* nodep) override {
        // Detect writes through VIF: the MemberSel's fromp resolves to a virtual interface type.
        // Handles both direct VIF access (vif.member) and class chain (obj.vif.member).
        if (nodep->access().isWriteOrRW()) {
            AstIfaceRefDType* const dtypep
                = VN_CAST(nodep->fromp()->dtypep()->skipRefp(), IfaceRefDType);
            if (dtypep && dtypep->isVirtual()) {
                m_vifWrittenMembers.emplace(dtypep->ifacep(), nodep->varp()->name());
            }
        }
        iterateChildren(nodep);
    }
    void visit(AstCMethodCall* nodep) override {
        if (const AstIfaceRefDType* const dtypep
            = VN_CAST(nodep->fromp()->dtypep()->skipRefp(), IfaceRefDType)) {
            if (VL_UNCOVERABLE(!dtypep->isVirtual())) {
                // Concrete interface method calls are lowered before this pass.
            } else {
                addReachableIfaceCallable(dtypep->ifaceViaCellp(), nodep->funcp());
            }
        }
        iterateChildren(nodep);
    }
    void visit(AstVarScope* nodep) override {
        // Collect candidate VarScopes. sensIfacep() is set on interface members
        // accessed via any MemberSel (virtual or non-virtual).
        AstVar* const varp = nodep->varp();
        if (varp->isTemp()) return;
        m_vscpsByVar[varp].push_back(nodep);
        if (const AstIface* const ifacep = varp->sensIfacep()) addCandidateVscp(ifacep, nodep);
    }
    void visit(AstNodeProcedure* nodep) override {
        // Disable lifetime optimization for variables in AlwaysPost blocks
        // that write to virtual interface members, as VIF reads may observe them
        if (VN_IS(nodep, AlwaysPost) && writesToVirtIface(nodep)) {
            nodep->foreach([](AstVarRef* refp) { refp->varScopep()->optimizeLifePost(false); });
        }
        iterateChildren(nodep);
    }
    void visit(AstNode* nodep) override { iterateChildren(nodep); }

    void addCandidateVscp(const AstIface* const ifacep, AstVarScope* const vscp) {
        const IfaceMember member{ifacep, vscp->varp()->name()};
        if (m_seenCandidateVscps.emplace(member, vscp).second)
            m_candidateVscps[member].push_back(vscp);
    }

    void addReachableIfaceCallable(AstIface* const ifacep, AstCFunc* const funcp) {
        const IfaceCallable callable{ifacep, funcp};
        if (m_seenReachableIfaceCallables.emplace(callable).second) {
            m_reachableIfaceCallables.push_back(callable);
        }
    }

    // Build final trigger list by intersecting VIF writes with candidate VarScopes
    void buildTriggers() {
        for (const auto& written : m_vifWrittenMembers) {
            const auto it = m_candidateVscps.find(written);
            if (it == m_candidateVscps.end()) continue;
            for (AstVarScope* const vscp : it->second) {
                const AstIface* const ifacep = written.first;
                m_triggers.addTrigger(ifacep, vscp->varp(), vscp);
            }
        }
    }

    // Returns true if a write to this member must always be checked by value compare
    static bool mustStayUngated(const AstVar* const varp) {
        return varp->isSigUserRWPublic() || varp->isSigPublic() || varp->isForceable()
               || varp->isPrimaryIO();
    }

    // Decide which triggers are gated and add 'dirty = 1' after each write to them.
    // A trigger is gated only if every write is the plain LHS of a procedural
    // assignment (VarRef in the member's scope, or MemberSel through a VIF).
    void gateTriggers(AstNetlist* const netlistp) {
        std::set<const AstVarScope*> trigVscps;
        for (const VirtIfaceTriggers::TriggerEntry& entry : m_triggers.m_triggers) {
            if (!mustStayUngated(entry.m_memberp)) trigVscps.insert(entry.m_vscp);
        }
        if (trigVscps.empty()) {
            addGateStats();
            return;
        }
        // Writes through a VIF MemberSel: hook only on the plain LHS of a procedural
        // assignment with a pure 'fromp' (cloned into the hook); else ungate the member
        std::set<IfaceMember> ungatedMembers;
        std::vector<std::pair<AstNodeAssign*, AstMemberSel*>> selSites;
        netlistp->foreach([&](AstMemberSel* const selp) {
            if (!selp->access().isWriteOrRW()) return;
            AstIfaceRefDType* const dtypep
                = VN_CAST(selp->fromp()->dtypep()->skipRefp(), IfaceRefDType);
            if (!dtypep || !dtypep->isVirtual()) return;
            const IfaceMember member{dtypep->ifacep(), selp->varp()->name()};
            AstNodeAssign* const assp = VN_CAST(selp->backp(), NodeAssign);
            if (assp && assp->lhsp() == selp && selp->access().isWriteOnly()
                && (VN_IS(assp, Assign) || VN_IS(assp, AssignDly)) && selp->fromp()->isPure()) {
                selSites.emplace_back(assp, selp);
            } else {
                ungatedMembers.insert(member);
            }
        });
        // Find hook sites; any other write shape ungates the VarScope
        std::set<const AstVarScope*> ungated;
        std::vector<std::pair<AstNodeAssign*, AstVarScope*>> sites;
        netlistp->foreach([&](AstVarRef* const refp) {
            if (!refp->access().isWriteOrRW()) return;
            AstVarScope* const vscp = refp->varScopep();
            if (!trigVscps.count(vscp)) return;
            AstNodeAssign* const assp = VN_CAST(refp->backp(), NodeAssign);
            if (assp && assp->lhsp() == refp && refp->access().isWriteOnly()
                && (VN_IS(assp, Assign) || VN_IS(assp, AssignDly))) {
                sites.emplace_back(assp, vscp);
            } else {
                ungated.insert(vscp);
            }
        });
        // Dirty flags: one variable per interface module, one VarScope per scope
        std::map<AstNodeModule*, std::pair<AstVar*, AstVar*>> modVars;
        std::map<AstScope*, std::pair<AstVarScope*, AstVarScope*>> scopeFlags;
        const auto getFlags = [&](AstScope* const scopep) {
            auto it = scopeFlags.find(scopep);
            if (it != scopeFlags.end()) return it->second;
            AstNodeModule* const modp = scopep->modp();
            FileLine* const flp = modp->fileline();
            auto mit = modVars.find(modp);
            if (mit == modVars.end()) {
                const auto newVar = [&](const string& name) {
                    AstVar* const varp
                        = new AstVar{flp, VVarType::MODULETEMP, name, netlistp->findBitDType()};
                    modp->addStmtsp(varp);
                    return varp;
                };
                mit = modVars
                          .emplace(modp, std::make_pair(newVar("__Vvifdirty_ico"),
                                                        newVar("__Vvifdirty_act")))
                          .first;
            }
            const auto newVscp = [&](AstVar* const varp) {
                AstVarScope* const vscp = new AstVarScope{flp, scopep, varp};
                scopep->addVarsp(vscp);
                return vscp;
            };
            const auto flags
                = std::make_pair(newVscp(mit->second.first), newVscp(mit->second.second));
            scopeFlags.emplace(scopep, flags);
            return flags;
        };
        for (VirtIfaceTriggers::TriggerEntry& entry : m_triggers.m_triggers) {
            if (!trigVscps.count(entry.m_vscp) || ungated.count(entry.m_vscp)) continue;
            if (ungatedMembers.count({entry.m_ifacep, entry.m_memberp->name()})) continue;
            const auto flags = getFlags(entry.m_vscp->scopep());
            entry.m_gated = true;
            entry.m_dirtyIcop = flags.first;
            entry.m_dirtyActp = flags.second;
        }
        // Hooks: 'dirty_ico = 1; dirty_act = 1;' after each write of a gated VarScope
        for (const auto& site : sites) {
            if (ungated.count(site.second)) continue;
            const auto flags = scopeFlags.at(site.second->scopep());
            FileLine* const flp = site.first->fileline();
            for (AstVarScope* const flagp : {flags.first, flags.second}) {
                site.first->addNextHere(new AstAssign{
                    flp, new AstVarRef{flp, flagp, VAccess::WRITE}, new AstConst{flp, 1}});
            }
        }
        // Hooks: 'vif.dirty_ico = 1; vif.dirty_act = 1;' after each VIF MemberSel write.
        // The flags exist in every instance of the interface, so the hook may set one
        // that no trigger reads (instance not gated); that is harmless.
        for (const auto& site : selSites) {
            AstMemberSel* const selp = site.second;
            AstIfaceRefDType* const dtypep
                = VN_AS(selp->fromp()->dtypep()->skipRefp(), IfaceRefDType);
            if (ungatedMembers.count({dtypep->ifacep(), selp->varp()->name()})) continue;
            const auto mit = modVars.find(dtypep->ifacep());
            if (mit == modVars.end()) continue;  // No gated instance of this interface
            FileLine* const flp = site.first->fileline();
            for (AstVar* const flagp : {mit->second.first, mit->second.second}) {
                AstMemberSel* const hookp
                    = new AstMemberSel{flp, selp->fromp()->cloneTree(false), flagp};
                hookp->access(VAccess::WRITE);
                site.first->addNextHere(new AstAssign{flp, hookp, new AstConst{flp, 1}});
            }
        }
        addGateStats();
    }

    void addGateStats() const {
        size_t nGated = 0;
        for (const VirtIfaceTriggers::TriggerEntry& entry : m_triggers.m_triggers) {
            if (entry.m_gated) ++nGated;
        }
        V3Stats::addStat("Scheduling, vif triggers, gated", nGated);
        V3Stats::addStat("Scheduling, vif triggers, ungated",
                         m_triggers.m_triggers.size() - nGated);
    }

public:
    // CONSTRUCTORS
    explicit VirtIfaceVisitor(AstNetlist* nodep) {
        iterate(nodep);
        for (size_t i = 0; i < m_reachableIfaceCallables.size(); ++i) {
            const IfaceCallable callable = m_reachableIfaceCallables[i];
            callable.second->foreach([this, callable](AstNodeExpr* const nodep) {
                if (AstVarRef* const refp = VN_CAST(nodep, VarRef)) {
                    // Only persistent interface storage is observable through a VIF read.
                    UASSERT_OBJ(refp->varScopep(), refp, "No var scope");
                    AstVar* const varp = refp->varp();
                    if (!refp->access().isWriteOrRW() || varp->isFuncLocal() || varp->isTemp()
                        || varp->isEvent() || !VN_IS(refp->varScopep()->scopep()->modp(), Iface)) {
                        return;
                    }
                    varp->sensIfacep(callable.first);
                    m_vifWrittenMembers.emplace(callable.first, varp->name());
                    const auto it = m_vscpsByVar.find(varp);
                    UASSERT_OBJ(it != m_vscpsByVar.end(), varp,
                                "No VarScope for interface member");
                    for (AstVarScope* const vscp : it->second)
                        addCandidateVscp(callable.first, vscp);
                } else if (AstNodeCCall* const callp = VN_CAST(nodep, NodeCCall)) {
                    addReachableIfaceCallable(callable.first, callp->funcp());
                }
            });
        }
        buildTriggers();
        gateTriggers(nodep);
    }
    ~VirtIfaceVisitor() override = default;

    // METHODS
    VirtIfaceTriggers take_triggers() { return std::move(m_triggers); }
};

}  //namespace

VirtIfaceTriggers makeVirtIfaceTriggers(AstNetlist* nodep) {
    UINFO(2, __FUNCTION__ << ":");
    VirtIfaceTriggers triggers{};
    if (v3Global.hasVirtIfaces()) {
        triggers = VirtIfaceVisitor{nodep}.take_triggers();
        // Dump after destructor so VNDeleter runs
        V3Global::dumpCheckGlobalTree("sched_vif", 0, dumpTreeEitherLevel() >= 6);
    }
    return triggers;
}

}  //namespace V3Sched
