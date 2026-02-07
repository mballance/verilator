// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: Functional coverage implementation
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
// FUNCTIONAL COVERAGE TRANSFORMATIONS:
//      For each covergroup (AstClass with isCovergroup()):
//          For each coverpoint (AstCoverpoint):
//              Generate member variable for VerilatedCoverpoint
//              Generate initialization in constructor
//              Generate sample code in sample() method
//
//*************************************************************************

#include "V3PchAstNoMT.h"  // VL_MT_DISABLED_CODE_UNIT

#include "V3CoverageFunctional.h"

VL_DEFINE_DEBUG_FUNCTIONS;

//######################################################################
// Functional coverage visitor

class FunctionalCoverageVisitor final : public VNVisitor {
    // STATE
    AstClass* m_covergroupp = nullptr;  // Current covergroup being processed
    AstFunc* m_sampleFuncp = nullptr;   // Current sample() function
    AstFunc* m_constructorp = nullptr;  // Current constructor
    std::vector<AstCoverpoint*> m_coverpoints;  // Coverpoints in current covergroup

    // METHODS
    void processCovergroup() {
        if (!m_covergroupp || m_coverpoints.empty()) return;
        
        UINFO(4, "Processing covergroup: " << m_covergroupp->name() 
              << " with " << m_coverpoints.size() << " coverpoints" << endl);
        
        // For each coverpoint, generate sampling code
        for (AstCoverpoint* cpp : m_coverpoints) {
            generateCoverpointCode(cpp);
        }
        
        // Generate coverage computation code
        generateCoverageComputationCode();
    }
    
    void generateCoverpointCode(AstCoverpoint* coverpointp) {
        if (!m_sampleFuncp || !m_constructorp) {
            coverpointp->v3warn(E_UNSUPPORTED, "Coverpoint without sample() or constructor");
            return;
        }
        
        UINFO(4, "  Generating code for coverpoint: " << coverpointp->name() << endl);
        
        // Get the coverpoint expression  
        AstNodeExpr* exprp = coverpointp->exprp();
        if (!exprp) {
            coverpointp->v3warn(E_UNSUPPORTED, "Coverpoint without expression");
            return;
        }
        
        // Generate member variables and matching code for each bin
        int binCount = 0;
        for (AstNode* binp = coverpointp->binsp(); binp; binp = binp->nextp()) {
            if (++binCount > 1000) {
                coverpointp->v3error("Too many bins or infinite loop detected in bin iteration");
                break;
            }
            AstCoverBin* const cbinp = VN_CAST(binp, CoverBin);
            if (!cbinp) continue;
            
            // Create a member variable to track hits for this bin
            const string varName = "__Vcov_" + coverpointp->name() + "_" + cbinp->name();
            AstVar* const varp = new AstVar{
                cbinp->fileline(), VVarType::MEMBER, varName,
                cbinp->findUInt32DType()};
            varp->isStatic(false);
            m_covergroupp->addMembersp(varp);
            UINFO(6, "    Created member variable: " << varName << endl);
            
            // Generate bin matching code in sample()
            generateBinMatchCode(coverpointp, cbinp, exprp, varp);
        }
    }
    
    void generateBinMatchCode(AstCoverpoint* coverpointp, AstCoverBin* binp,
                              AstNodeExpr* exprp, AstVar* hitVarp) {
        UINFO(4, "    Generating bin match for: " << binp->name() << endl);
        
        // Get the range from the bin
        AstNode* rangep = binp->rangesp();
        if (!rangep) {
            UINFO(4, "      No range found for bin" << endl);
            return;
        }
        
        // Clone the expression for evaluation
        AstNodeExpr* exprClonep = exprp->cloneTree(false);
        
        // Build condition based on the range type
        AstNodeExpr* condp = nullptr;
        
        if (AstInsideRange* irp = VN_CAST(rangep, InsideRange)) {
            // INSIDERANGE has min and max as children
            // Convert to: (expr >= min) && (expr <= max)
            // But optimize: if min is 0 and unsigned, skip the >= check
            AstNode* minp = irp->lhsp();
            AstNode* maxp = irp->rhsp();
            
            if (minp && maxp) {
                // minp and maxp should be expressions, cast them safely
                AstNodeExpr* minExprp = VN_CAST(minp, NodeExpr);
                AstNodeExpr* maxExprp = VN_CAST(maxp, NodeExpr);
                if (minExprp && maxExprp) {
                    AstNodeExpr* exprClone2p = exprp->cloneTree(false);
                    
                    // Check if min is constant 0 - skip the >= check to avoid UNSIGNED warning
                    bool skipMinCheck = false;
                    if (const AstConst* constp = VN_CAST(minExprp, Const)) {
                        if (constp->toUInt() == 0) skipMinCheck = true;
                    }
                    
                    if (skipMinCheck) {
                        // Just check upper bound
                        condp = new AstLte{binp->fileline(), exprClonep, maxExprp->cloneTree(false)};
                        exprClone2p->deleteTree();
                    } else {
                        // Check both bounds
                        condp = new AstAnd{
                            binp->fileline(),
                            new AstGte{binp->fileline(), exprClonep, minExprp->cloneTree(false)},
                            new AstLte{binp->fileline(), exprClone2p, maxExprp->cloneTree(false)}};
                    }
                } else {
                    UINFO(4, "      Min or max is not an expression" << endl);
                    exprClonep->deleteTree();
                    return;
                }
            } else {
                UINFO(4, "      Could not extract min/max from INSIDERANGE" << endl);
                exprClonep->deleteTree();
                return;
            }
        } else {
            // Fallback: just check equality
            AstNodeExpr* rangeExprp = VN_CAST(rangep, NodeExpr);
            if (!rangeExprp) {
                UINFO(4, "      Cannot convert range to expression" << endl);
                exprClonep->deleteTree();
                return;
            }
            condp = new AstEq{binp->fileline(), exprClonep, rangeExprp->cloneTree(false)};
        }
        
        // Apply iff condition if present - wraps the bin match condition
        if (AstNodeExpr* iffp = coverpointp->iffp()) {
            UINFO(6, "      Adding iff condition" << endl);
            condp = new AstAnd{binp->fileline(), iffp->cloneTree(false), condp};
        }
        
        // Create: if (condition) hitVar++;
        AstIf* const ifp = new AstIf{
            binp->fileline(), condp,
            new AstAssign{
                binp->fileline(),
                new AstVarRef{binp->fileline(), hitVarp, VAccess::WRITE},
                new AstAdd{binp->fileline(),
                    new AstVarRef{binp->fileline(), hitVarp, VAccess::READ},
                    new AstConst{binp->fileline(), AstConst::WidthedValue{}, 32, 1}}},
            nullptr};
        
        m_sampleFuncp->addStmtsp(ifp);
        UINFO(6, "      Added if statement for bin matching" << endl);
    }
    
    void generateCoverageComputationCode() {
        UINFO(4, "  Generating coverage computation code" << endl);
        
        // Find get_coverage() and get_inst_coverage() methods
        AstFunc* getCoveragep = nullptr;
        AstFunc* getInstCoveragep = nullptr;
        
        int memberCount = 0;
        for (AstNode* itemp = m_covergroupp->membersp(); itemp; itemp = itemp->nextp()) {
            if (++memberCount > 10000) {
                m_covergroupp->v3error("Too many members or infinite loop in membersp iteration (1)");
                break;
            }
            if (AstFunc* funcp = VN_CAST(itemp, Func)) {
                if (funcp->name() == "get_coverage") {
                    getCoveragep = funcp;
                } else if (funcp->name() == "get_inst_coverage") {
                    getInstCoveragep = funcp;
                }
            }
        }
        
        if (!getCoveragep || !getInstCoveragep) {
            UINFO(4, "    Warning: Could not find get_coverage methods" << endl);
            return;
        }
        
        // Collect all bin counter variables
        std::vector<AstVar*> binVars;
        memberCount = 0;
        for (AstNode* itemp = m_covergroupp->membersp(); itemp; itemp = itemp->nextp()) {
            if (++memberCount > 10000) {
                m_covergroupp->v3error("Too many members or infinite loop in membersp iteration (2)");
                break;
            }
            if (AstVar* varp = VN_CAST(itemp, Var)) {
                if (varp->name().find("__Vcov_") == 0) {
                    binVars.push_back(varp);
                }
            }
        }
        
        if (binVars.empty()) {
            UINFO(4, "    No bins found for coverage computation" << endl);
            return;
        }
        
        UINFO(6, "    Found " << binVars.size() << " bins for coverage" << endl);
        
        // Generate code for get_inst_coverage() only (get_coverage() needs aggregation)
        if (getInstCoveragep) {
            generateCoverageMethodBody(getInstCoveragep, binVars);
        }
    }
    
    void generateCoverageMethodBody(AstFunc* funcp, const std::vector<AstVar*>& binVars) {
        FileLine* fl = funcp->fileline();
        
        // Create local variable to count covered bins
        AstVar* coveredCountp = new AstVar{
            fl, VVarType::BLOCKTEMP, "__Vcovered_count",
            funcp->findUInt32DType()};
        coveredCountp->funcLocal(true);
        funcp->addStmtsp(coveredCountp);
        
        // Initialize: covered_count = 0
        funcp->addStmtsp(new AstAssign{
            fl,
            new AstVarRef{fl, coveredCountp, VAccess::WRITE},
            new AstConst{fl, AstConst::WidthedValue{}, 32, 0}});
        
        // For each bin, if count > 0, increment covered_count
        for (AstVar* binVarp : binVars) {
            // if (bin_count > 0) covered_count++;
            AstIf* ifp = new AstIf{
                fl,
                new AstGt{fl,
                    new AstVarRef{fl, binVarp, VAccess::READ},
                    new AstConst{fl, AstConst::WidthedValue{}, 32, 0}},
                new AstAssign{
                    fl,
                    new AstVarRef{fl, coveredCountp, VAccess::WRITE},
                    new AstAdd{fl,
                        new AstVarRef{fl, coveredCountp, VAccess::READ},
                        new AstConst{fl, AstConst::WidthedValue{}, 32, 1}}},
                nullptr};
            funcp->addStmtsp(ifp);
        }
        
        // Find the return variable
        AstVar* returnVarp = VN_AS(funcp->fvarp(), Var);
        if (!returnVarp) {
            UINFO(4, "    Warning: No return variable found in " << funcp->name() << endl);
            return;
        }
        
        // Calculate coverage: (covered_count / total_bins) * 100.0
        // return_var = (double)covered_count / (double)total_bins * 100.0
        
        // Cast covered_count to real/double
        AstNodeExpr* coveredReal = new AstIToRD{fl,
            new AstVarRef{fl, coveredCountp, VAccess::READ}};
        
        // Create total bins as a double constant
        AstNodeExpr* totalReal = new AstConst{fl, AstConst::RealDouble{}, 
                                              static_cast<double>(binVars.size())};
        
        // Divide using AstDivD (double division that emits native /)
        AstNodeExpr* divExpr = new AstDivD{fl, coveredReal, totalReal};
        
        // Multiply by 100 using AstMulD (double multiplication that emits native *)
        AstNodeExpr* hundredConst = new AstConst{fl, AstConst::RealDouble{}, 100.0};
        AstNodeExpr* coverageExpr = new AstMulD{fl, hundredConst, divExpr};
        
        // Assign to return variable
        funcp->addStmtsp(new AstAssign{
            fl,
            new AstVarRef{fl, returnVarp, VAccess::WRITE},
            coverageExpr});
        
        UINFO(6, "    Added coverage computation to " << funcp->name() << endl);
    }
    
    int countBins(AstCoverpoint* nodep) {
        int count = 0;
        for (AstNode* binp = nodep->binsp(); binp; binp = binp->nextp()) {
            count++;
        }
        return count;
    }

    // VISITORS
    void visit(AstClass* nodep) override {
        UINFO(9, "Visiting class: " << nodep->name() 
              << " isCovergroup=" << nodep->isCovergroup() << endl);
        if (nodep->isCovergroup()) {
            VL_RESTORER(m_covergroupp);
            m_covergroupp = nodep;
            m_sampleFuncp = nullptr;
            m_constructorp = nullptr;
            m_coverpoints.clear();
            
            // Find the sample() method and constructor
            int findCount = 0;
            for (AstNode* itemp = nodep->membersp(); itemp; itemp = itemp->nextp()) {
                if (++findCount > 10000) {
                    nodep->v3error("Too many members or infinite loop in membersp iteration (3)");
                    break;
                }
                if (AstFunc* const funcp = VN_CAST(itemp, Func)) {
                    if (funcp->name() == "sample") {
                        m_sampleFuncp = funcp;
                        UINFO(9, "Found sample() method" << endl);
                    } else if (funcp->name() == "new") {
                        m_constructorp = funcp;
                        UINFO(9, "Found constructor" << endl);
                    }
                }
            }
            
            iterateChildren(nodep);
            processCovergroup();
        } else {
            iterateChildren(nodep);
        }
    }

    void visit(AstCoverpoint* nodep) override {
        UINFO(9, "Found coverpoint: " << nodep->name() << endl);
        m_coverpoints.push_back(nodep);
        iterateChildren(nodep);
    }

    void visit(AstNode* nodep) override { iterateChildren(nodep); }

public:
    // CONSTRUCTORS
    explicit FunctionalCoverageVisitor(AstNetlist* nodep) { iterate(nodep); }
    ~FunctionalCoverageVisitor() override = default;
};

//######################################################################
// Functional coverage class functions

void V3CoverageFunctional::coverageFunctional(AstNetlist* nodep) {
    UINFO(2, __FUNCTION__ << ": " << endl);
    { FunctionalCoverageVisitor{nodep}; }  // Destruct before checking
    V3Global::dumpCheckGlobalTree("coveragefunc", 0, dumpTreeEitherLevel() >= 3);
}
