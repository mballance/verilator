// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: dv-solve constraint solver back-end
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************
// V3SolverDvs's Transformations:
//
// Implements V3SolverBackend for the dv-solve library, selected by
// --solver-dvs. This file compiles to nothing unless Verilator is configured
// --with-dv-solve.
//
// Each randomize site becomes a dv-solve problem (V3SolverDvsBuild.cpp),
// emitted as a constant-pool array of its bytes (the image). The site calls
// VL_DVS_SOLVE (verilated_solver_dvs.h) with the image, a constant-pool array
// describing each problem variable, one holding the location and source of
// each constraint, and the variables themselves; the runtime opens the image
// on its first solve. A site with a construct the builder does not support
// is reported as unsupported (V3SolverDvsCheck.cpp), and replaced by a
// failing solver result.
//
// Constraints across objects (IEEE 1800-2023 18.5.8) are solved from parts.
// A class with rand class handles (slots), the class of a slot, and the
// classes derived from them, each have a part: the problem of the class's own
// constraint blocks, whose variables are exported and which reads those of
// other objects through its slots (V3SolverDvsBuild.cpp). Its virtual
// __Vdvs_part method evaluates the part's state values, registers the part
// of the object (VL_DVS_PART), and then that of the object of each non-null
// slot. As the method is virtual, an object registers the part of its actual
// class. The randomize() of a class with slots registers the parts reached
// from the object (VL_DVS_PARTS_BEGIN, then __Vdvs_part), and dv-solve solves
// them together (VL_DVS_SOLVE_PARTS); that of any other class is unchanged.
// A randomize() with {...} on an object whose class has slots, or whose
// actual class may add constraints, is a part of its own (a site
// part): the inline constraints, which read the variables of the object
// through its slot 0. It registers itself (VL_DVS_SITE_PART), then the part of
// the object, so the object's actual class decides the object's constraints,
// and the inline constraints rank above them (IEEE 1800-2023 18.5.13).
// The constraints V3Randomize clones from the class of a rand handle into the
// class holding it are not solved, as they are those of the declared class,
// not of the object.
//
//*************************************************************************

#include "V3PchAstNoMT.h"  // VL_MT_DISABLED_CODE_UNIT

#ifdef HAVE_DV_SOLVE

#include "V3MemberMap.h"
#include "V3SolverBackend.h"
#include "V3SolverDvs.h"
#include "V3SolverDvsBuild.h"

#include <dv_solve/dvs_writer.h>

// Libraries of the dv-solve runtime that a model links, relative to $(DV_SOLVE_ROOT), not
// to where configure found dv-solve. Configure takes them from pkg-config when it can;
// otherwise these are the Libs and Libs.private of dv-solve.pc.
#ifndef DV_SOLVE_RUNTIME_LDLIBS
#define DV_SOLVE_RUNTIME_LDLIBS "$(DV_SOLVE_ROOT)/lib/libdv_solve.a -lpthread -lm -lstdc++ -ldl"
#endif

//######################################################################
// Lowering of the randomize sites of one V3Randomize pass

class SolverDvsLowering final : public V3SolverLowering {
    // NODE STATE
    //  AstClass::user1()   -> bool. Is randomized (V3Randomize)
    //  AstNodeExpr::user1() -> bool. Depends on a random variable (V3Randomize, and
    //                                markRandDependent())

    // Name of the method registering the part of an object
    static constexpr const char* PART_TASK_NAME = "__Vdvs_part";

    // STATE
    std::map<const AstClass*, bool> m_extendedWithConstraints;  // Cache, see that method
    std::set<const AstClass*> m_slotClasses;  // Classes of the slots of the classes randomized

public:
    // CONSTRUCTORS
    SolverDvsLowering(VMemberMap& memberMap, V3UniqueNames& uniqueNames,
                      const RandModeVars& modeVars, VNDeleter& deleter)
        : V3SolverLowering{memberMap, uniqueNames, modeVars, deleter} {
        v3Global.rootp()->foreach([&](const AstClass* classp) {
            if (!classp->user1()) return;
            for (const AstVar* const slotp : dvsSlots(classp)) {
                m_slotClasses.insert(dvsHandleClassp(slotp->dtypep()));
            }
        });
    }
    ~SolverDvsLowering() override = default;

private:
    // METHODS
    // Whether a constraint block is one V3Randomize cloned from the class of a rand handle
    static bool isClone(const AstConstraint* constrp) {
        return constrp->name().find(GLOBAL_CONSTRAINT_SEPARATOR) != std::string::npos;
    }
    // The site of a randomize() of classp: the constraint blocks of the class, a block of a
    // derived class replacing that of the same name of its base (IEEE 1800-2023 18.5.2)
    DvsSite classSite(AstClass* classp, FileLine* flp, bool checkOnly) const {
        DvsSite site{classp, flp, {}, checkOnly};
        std::map<std::string, const AstConstraint*> blocks;  // The block of each name
        classp->foreachMember([&](AstClass*, AstConstraint* constrp) {
            blocks[constrp->name()] = constrp;  // A base class's first
        });
        classp->foreachMember([&](AstClass*, AstConstraint* constrp) {
            if (isClone(constrp) || blocks[constrp->name()] != constrp) return;
            const RandomizeMode mode = {.asUQuad = constrp->user1()};
            AstVar* modeVarp = nullptr;
            if (mode.usesMode) {
                modeVarp = constrp->isStatic() ? m_modeVars.staticConstraintModeVarp(classp)
                                               : RandModeVars::constraintModeVarp(classp);
            }
            site.blocks.push_back({constrp->itemsp(), modeVarp, mode.index});
        });
        return site;
    }
    // True if a class derived from classp adds constraints. Unlike a class randomize(),
    // which is virtual, an inline or randomize(null) site is solved for the class of the
    // handle, and its problem would miss them.
    bool extendedWithConstraints(AstClass* classp) {
        if (!classp->isExtended()) return false;
        const auto pair = m_extendedWithConstraints.emplace(classp, false);
        if (pair.second) {
            v3Global.rootp()->foreach([&](const AstClass* derivedp) {
                if (derivedp == classp || !AstClass::isClassExtendedFrom(derivedp, classp)) return;
                for (const AstNode* itemp = derivedp->membersp(); itemp; itemp = itemp->nextp()) {
                    if (VN_IS(itemp, Constraint)) pair.first->second = true;
                }
            });
        }
        return pair.first->second;
    }
    // Whether an inline site on an object of classp is a site part: the objects of its
    // slots, or its actual class, may have constraints the problem of classp would miss
    bool hasSitePart(AstClass* classp) {
        return !dvsSlots(classp).empty() || extendedWithConstraints(classp);
    }
    // Whether classp has a part: it has slots, or it is or extends the class of a slot
    bool hasPart(const AstClass* classp) const {
        if (!dvsSlots(classp).empty()) return true;
        for (const AstClass* basep = classp; basep;
             basep = basep->extendsp() ? basep->extendsp()->classp() : nullptr) {
            if (m_slotClasses.count(basep)) return true;
        }
        return false;
    }
    // The __Vdvs_part method of classp, created on first use
    AstTask* partTaskp(AstClass* classp) {
        if (AstNode* const foundp = m_memberMap.findMember(classp, PART_TASK_NAME)) {
            return VN_AS(foundp, Task);
        }
        AstTask* const taskp = new AstTask{classp->fileline(), PART_TASK_NAME};
        taskp->classMethod(true);
        taskp->isVirtual(classp->isExtended());
        classp->addMembersp(taskp);
        m_memberMap.insert(classp, taskp);
        return taskp;
    }
    // Build the body of the __Vdvs_part method of classp, unless built already; return the
    // method, or nullptr if its part is not supported. If ownVars, the class's randomize()
    // solves the part.
    AstTask* makePartTask(AstClass* classp, bool ownVars) {
        if (AstNode* const foundp = m_memberMap.findMember(classp, PART_TASK_NAME)) {
            if (VN_AS(foundp, Task)->stmtsp()) return VN_AS(foundp, Task);
        }
        FileLine* const flp = classp->fileline();
        DvsSite site = classSite(classp, flp, false);
        site.part = true;
        for (const DvsSite::Block& block : site.blocks) {
            for (AstNode* itemp = block.itemsp; itemp; itemp = itemp->nextp()) {
                markRandDependent(itemp);
            }
        }
        AstTask* const taskp = partTaskp(classp);
        AstNodeExpr* const callp = dvsNewPartCallp(site, taskp, ownVars);
        if (!callp) return nullptr;
        // Once registered, the parts of the objects of its slots
        AstNodeStmt* slotsp = nullptr;
        for (AstVar* const slotp : dvsSlots(classp)) {
            AstTask* const slotTaskp = partTaskp(dvsHandleClassp(slotp->dtypep()));
            AstNodeModule* const modp = VN_AS(slotp->user2p(), NodeModule);
            const auto partOfp = [&](AstNodeExpr* refp) {
                AstMethodCall* const partCallp
                    = new AstMethodCall{flp, refp->cloneTree(false), PART_TASK_NAME, nullptr};
                partCallp->taskp(slotTaskp);
                partCallp->dtypeSetVoid();
                return new AstIf{flp, new AstNeq{flp, refp, new AstConst{flp, AstConst::Null{}}},
                                 partCallp->makeStmt()};
            };
            AstVarRef* const refp = new AstVarRef{flp, modp, slotp, VAccess::READ};
            if (dvsIsSlotArray(slotp->dtypep())) {
                // foreach (slot[i]) if (slot[i] != null) slot[i].__Vdvs_part();
                AstVar* const indexp
                    = new AstVar{flp, VVarType::BLOCKTEMP, "__Vdvs_i", classp->findIntDType()};
                AstCMethodHard* const elemp
                    = new AstCMethodHard{flp, refp->cloneTree(false), VCMethod::ARRAY_AT,
                                         new AstVarRef{flp, indexp, VAccess::READ}};
                elemp->dtypep(slotp->dtypep()->skipRefp()->subDTypep());
                // In a block, whose variables V3Begin moves to the method
                slotsp = AstNode::addNext(
                    slotsp,
                    new AstBegin{flp, "__Vdvs_" + slotp->name(),
                                 new AstForeach{flp, new AstForeachHeader{flp, refp, indexp},
                                                partOfp(elemp)},
                                 true});
                continue;
            }
            forEachHandle(refp, [&](AstNodeExpr* elemp) {
                slotsp = AstNode::addNext(slotsp, partOfp(elemp));
            });
        }
        taskp->addStmtsp(new AstIf{flp, callp, slotsp});
        return taskp;
    }
    // Call fn with each class handle of refp, a handle or a fixed-size unpacked array of them,
    // in storage order: refp, or a new select of each element; fn takes each, refp is taken
    static void forEachHandle(AstNodeExpr* refp, const std::function<void(AstNodeExpr*)>& fn) {
        const AstUnpackArrayDType* const adtypep
            = VN_CAST(refp->dtypep()->skipRefp(), UnpackArrayDType);
        if (!adtypep) {
            fn(refp);
            return;
        }
        for (int i = 0; i < adtypep->elementsConst(); ++i) {
            forEachHandle(new AstArraySel{refp->fileline(), refp->cloneTree(false), i}, fn);
        }
        VL_DO_DANGLING(refp->deleteTree(), refp);
    }
    // Add to funcp, a method of classp, the start of a solve of parts, then firstp (or
    // nullptr), then the registration of the part of the object; return the solver result
    static AstNodeExpr* newPartsSolvep(FileLine* flp, AstClass* classp, AstNodeFTask* funcp,
                                       AstTask* taskp, AstNodeExpr* firstp) {
        AstCFuncHard* const beginp = new AstCFuncHard{flp, VCFunction::DVS_PARTS_BEGIN};
        beginp->dtypeSetVoid();
        funcp->addStmtsp(beginp->makeStmt());
        if (firstp) funcp->addStmtsp(firstp->makeStmt());
        AstClassRefDType* const refDTypep = new AstClassRefDType{flp, classp, nullptr};
        v3Global.rootp()->typeTablep()->addTypesp(refDTypep);
        AstMethodCall* const partCallp
            = new AstMethodCall{flp, new AstThisRef{flp, refDTypep}, taskp->name(), nullptr};
        partCallp->taskp(taskp);
        partCallp->dtypeSetVoid();
        funcp->addStmtsp(partCallp->makeStmt());
        AstCFuncHard* const solvep = new AstCFuncHard{flp, VCFunction::DVS_SOLVE_PARTS};
        solvep->dtypeSetBit();
        // VL_DVS_SOLVE_PARTS draws its seed from the object's RNG
        classp->baseMostClassp()->needRNG(true);
        return solvep;
    }
    // Solver result of an inline site of a site part, adding its statements to funcp
    AstNodeExpr* newSitePartResultp(FileLine* flp, AstClass* classp, AstNodeFTask* funcp,
                                    AstNode* itemsp) {
        // The part of each class the object may have
        AstTask* taskp = makePartTask(classp, !dvsSlots(classp).empty());
        v3Global.rootp()->foreach([&](AstClass* derivedp) {
            if (derivedp != classp && AstClass::isClassExtendedFrom(derivedp, classp)
                && !makePartTask(derivedp, !dvsSlots(derivedp).empty())) {
                taskp = nullptr;
            }
        });
        DvsSite site{classp, flp, {{itemsp, nullptr, 0}}, false};
        site.part = true;
        site.inlinePart = true;
        AstNodeExpr* const sitePartp = dvsNewPartCallp(site, funcp, false);
        if (!taskp || !sitePartp) {
            if (sitePartp) VL_DO_DANGLING(sitePartp->deleteTree(), sitePartp);
            return new AstConst{flp, AstConst::BitFalseErroring{}};
        }
        return newPartsSolvep(flp, classp, funcp, taskp, sitePartp);
    }
    // Solver result of the site
    static AstNodeExpr* newResultp(const DvsSite& site, AstNodeFTask* funcp, bool ownVars) {
        if (AstNodeExpr* const callp = dvsNewSolveCallp(site, funcp, ownVars)) return callp;
        return new AstConst{site.flp, AstConst::BitFalseErroring{}};
    }

    // In this.randomize() with {...}, the caller's object is the one randomized: make its
    // random members, captured as '__Vthis.member', references to the random variables.
    // Return the new first item.
    AstNode* ownRandMembers(AstNode* itemsp, const AstVar* thisVarp) {
        // The items are constraint items, not statements: visit each one (an item is never
        // itself a member reference, so the head of the list is not replaced)
        for (AstNode* itemp = itemsp; itemp; itemp = itemp->nextp()) {
            itemp->foreach([&](AstMemberRef* selp) {
                const AstVarRef* const fromp = VN_CAST(selp->fromp(), VarRef);
                if (!fromp || fromp->varp() != thisVarp
                    || !selp->varp()->rand().isRandomizable()) {
                    return;
                }
                AstVar* const varp = selp->varp();
                AstVarRef* const refp = new AstVarRef{
                    selp->fileline(), VN_AS(varp->user2p(), NodeModule), varp, VAccess::READ};
                refp->user1(true);
                selp->replaceWith(refp);
                pushDeletep(selp);
            });
        }
        return itemsp;
    }
    // A class handle, or a fixed-size unpacked array of them (a dynamic array of them is a
    // random variable: its size)
    static bool isHandle(const AstNode* nodep) {
        return dvsHandleClassp(nodep->dtypep()) && !dvsIsSlotArray(nodep->dtypep());
    }
    // Set AstNodeExpr::user1() on the expressions that depend on a random variable. The marks
    // of RandomizeMarkVisitor predate the capture of the caller's variables, which made a
    // random member of the caller '__Vthis.member', a state value; only the marks of the
    // variable references, and of members of random objects, are kept. A class handle is
    // a state value: the objects solved are those the handles hold at the call.
    static bool markRandDependent(AstNode* nodep) {
        bool dependent = false;
        for (AstNode* const childp :
             {nodep->op1p(), nodep->op2p(), nodep->op3p(), nodep->op4p()}) {
            for (AstNode* itemp = childp; itemp; itemp = itemp->nextp()) {
                dependent |= markRandDependent(itemp);
            }
        }
        if (VN_IS(nodep, Arg)) return dependent;  // Of a function call
        if (!VN_IS(nodep, NodeExpr)) return false;
        if (VN_IS(nodep, NodeVarRef)) {
            dependent = nodep->user1() && !isHandle(nodep);
        } else if (const AstMemberRef* const selp = VN_CAST(nodep, MemberRef)) {
            // A random member of a random object, or of the 'item' of a reduction, or of an
            // object reached through rand handles of this one
            dependent = selp->user1() && !isHandle(nodep)
                        && (dependent || VN_IS(selp->fromp(), LambdaArgRef)
                            || dvsIsSlotPath(selp->fromp()));
        }
        nodep->user1(dependent);
        return dependent;
    }

public:
    // V3SolverLowering
    void prepareClass(AstClass*) override {}
    void startClass(AstClass*) override {}
    void lowerConstraintMethod(AstNodeModule*, AstConstraint*, AstCMethodHard*) override {}
    AstNodeExpr* lowerClassRandomize(AstClass* classp, AstFunc* randomizep, AstVar*) override {
        FileLine* const flp = classp->fileline();
        const bool hasSlots = !dvsSlots(classp).empty();
        AstTask* const taskp = hasPart(classp) ? makePartTask(classp, hasSlots) : nullptr;
        // The solver owns the variables it solves, __VBasicRand (emitted next) the others
        if (!hasSlots) return newResultp(classSite(classp, flp, false), randomizep, true);
        if (!taskp) return new AstConst{flp, AstConst::BitFalseErroring{}};
        // The parts of the objects reached from this one, solved together
        return newPartsSolvep(flp, classp, randomizep, taskp, nullptr);
    }
    // The solve of the parts sets all the objects' exports: __VBasicRand, which may reach a
    // sub-object constrained only by its holder's actual class, must not follow it
    bool basicRandomizeFirst(const AstClass* classp) const override {
        return !dvsSlots(classp).empty();
    }
    void addAfterClassSolve(AstClass*, AstFunc*) override {}
    void lowerInlineRandomize(AstNodeFTaskRef* nodep, AstClass* classp, AstFunc* randomizeFuncp,
                              AstNode* capturedTreep, const AstVar* thisVarp,
                              AstNodeExpr* basicRandomizeCallp) override {
        const AstMethodCall* const callp = VN_CAST(nodep, MethodCall);
        if (thisVarp && (!callp || VN_IS(callp->fromp(), ThisRef))) {
            capturedTreep = ownRandMembers(capturedTreep, thisVarp);
        }
        for (AstNode* itemp = capturedTreep; itemp; itemp = itemp->nextp()) {
            markRandDependent(itemp);
        }
        FileLine* const flp = nodep->fileline();
        AstNodeExpr* resultp;
        if (hasSitePart(classp)) {
            resultp = newSitePartResultp(flp, classp, randomizeFuncp, capturedTreep);
        } else {
            DvsSite site = classSite(classp, flp, false);
            site.blocks.push_back({capturedTreep, nullptr, 0});
            resultp = newResultp(site, randomizeFuncp, false);
        }
        // __VBasicRand of the class has been emitted already, and randomizes the variables
        // that only the inline constraints name: it is called first, and the solver then
        // overrides the variables it solves
        AstVar* const retVarp = randomizeFuncp->fvarp();
        randomizeFuncp->addStmtsp(new AstAssign{flp, new AstVarRef{flp, retVarp, VAccess::WRITE},
                                                new AstAnd{flp, basicRandomizeCallp, resultp}});
        pushDeletep(capturedTreep);
    }
    AstNodeExpr* lowerStdRandomizeWith(AstNodeFTaskRef* nodep, AstFunc* randomizeFuncp,
                                       AstNode* capturedTreep, AstVar* stdrandp) override {
        // The random variables are the arguments, the function's references to them
        for (AstNode* declp = randomizeFuncp->declsp(); declp; declp = declp->nextp()) {
            AstVar* const varp = VN_CAST(declp, Var);
            if (varp && varp->isStdRandomizeArg()) varp->rand(VRandAttr::RAND);
        }
        for (AstNode* itemp = capturedTreep; itemp; itemp = itemp->nextp()) {
            markRandDependent(itemp);
        }
        DvsSite site{nullptr, nodep->fileline(), {{capturedTreep, nullptr, 0}}, false};
        site.stdrandp = stdrandp;
        pushDeletep(capturedTreep);
        return newResultp(site, randomizeFuncp, false);
    }
    AstNodeExpr* lowerCheckOnly(AstClass* classp, AstFunc* funcp) override {
        // A class with rand class handles is refused by the front end
        if (extendedWithConstraints(classp)) {
            classp->v3error("Unsupported: randomize(null) on a handle of a class that a class"
                            " with constraints extends with --solver-dvs");
            return new AstConst{classp->fileline(), AstConst::BitFalseErroring{}};
        }
        return newResultp(classSite(classp, classp->fileline(), true), funcp, false);
    }
};

//######################################################################
// Back-end

class V3SolverDvs final : public V3SolverBackend {
public:
    std::string runtimeHeader() const override { return "verilated_solver_dvs.h"; }
    std::vector<std::string> runtimeCppFiles() const override {
        return {"verilated_random.cpp", "verilated_solver_dvs.cpp"};
    }
    std::vector<std::string> runtimeCFlags() const override {
        return {"-I$(DV_SOLVE_ROOT)/include", "-DDVS_STATIC"};
    }
    std::vector<std::string> runtimeLdLibs() const override { return {DV_SOLVE_RUNTIME_LDLIBS}; }
    std::vector<std::pair<std::string, std::string>> runtimeMakeVars() const override {
        return {{"DV_SOLVE_ROOT", V3Options::getenvDV_SOLVE_ROOT()}};
    }
    std::unique_ptr<V3SolverLowering> newLowering(VMemberMap& memberMap,
                                                  V3UniqueNames& uniqueNames,
                                                  const RandModeVars& modeVars,
                                                  VNDeleter& deleter) const override {
        return std::unique_ptr<V3SolverLowering>{
            new SolverDvsLowering{memberMap, uniqueNames, modeVars, deleter}};
    }
};

V3SolverBackend* newV3SolverDvs() { return new V3SolverDvs; }

uint32_t dvSolveFormatVersion() { return DVS_PROBLEM_FORMAT_VERSION; }

#else

uint32_t dvSolveFormatVersion() { return 0; }

#endif  // HAVE_DV_SOLVE
