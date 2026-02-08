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
    std::vector<AstCoverCross*> m_coverCrosses;  // Cross coverage items in current covergroup
    
    // Structure to track bins with their variables
    struct BinInfo {
        AstCoverBin* binp;
        AstVar* varp;
        BinInfo(AstCoverBin* b, AstVar* v) : binp{b}, varp{v} {}
    };
    std::vector<BinInfo> m_binInfos;  // All bins in current covergroup

    // METHODS
    void processCovergroup() {
        if (!m_covergroupp || (m_coverpoints.empty() && m_coverCrosses.empty())) return;
        
        UINFO(4, "Processing covergroup: " << m_covergroupp->name() 
              << " with " << m_coverpoints.size() << " coverpoints and "
              << m_coverCrosses.size() << " crosses" << endl);
        
        // Clear bin info for this covergroup
        m_binInfos.clear();
        
        // For each coverpoint, generate sampling code
        for (AstCoverpoint* cpp : m_coverpoints) {
            generateCoverpointCode(cpp);
        }
        
        // For each cross, generate sampling code
        for (AstCoverCross* crossp : m_coverCrosses) {
            generateCrossCode(crossp);
        }
        
        // Generate coverage computation code
        generateCoverageComputationCode();
    }
    
    void expandAutomaticBins(AstCoverpoint* coverpointp, AstNodeExpr* exprp) {
        // Find and expand any automatic bins
        AstNode* prevBinp = nullptr;
        for (AstNode* binp = coverpointp->binsp(); binp;) {
            AstCoverBin* const cbinp = VN_CAST(binp, CoverBin);
            AstNode* nextBinp = binp->nextp();
            
            if (cbinp && cbinp->binsType() == VCoverBinsType::AUTO) {
                UINFO(4, "  Expanding automatic bin: " << cbinp->name() << endl);
                
                // Get array size - must be a constant
                AstNodeExpr* sizep = cbinp->arraySizep();
                if (!sizep) {
                    cbinp->v3error("Automatic bins requires array size [N]");
                    binp = nextBinp;
                    continue;
                }
                
                // Evaluate as constant
                const AstConst* constp = VN_CAST(sizep, Const);
                if (!constp) {
                    cbinp->v3error("Automatic bins array size must be a constant");
                    binp = nextBinp;
                    continue;
                }
                
                const int numBins = constp->toSInt();
                if (numBins <= 0 || numBins > 10000) {
                    cbinp->v3error("Automatic bins array size must be 1-10000, got " 
                                   + std::to_string(numBins));
                    binp = nextBinp;
                    continue;
                }
                
                // Calculate range division
                const int width = exprp->width();
                const uint64_t maxVal = (width >= 64) ? UINT64_MAX : ((1ULL << width) - 1);
                const uint64_t binSize = (maxVal + 1) / numBins;
                
                UINFO(4, "    Width=" << width << " maxVal=" << maxVal 
                      << " numBins=" << numBins << " binSize=" << binSize << endl);
                
                // Create expanded bins
                for (int i = 0; i < numBins; i++) {
                    const uint64_t lo = i * binSize;
                    const uint64_t hi = (i == numBins - 1) ? maxVal : ((i + 1) * binSize - 1);
                    
                    // Create constants for range
                    AstConst* loConstp = new AstConst{cbinp->fileline(), V3Number(cbinp->fileline(), width, lo)};
                    AstConst* hiConstp = new AstConst{cbinp->fileline(), V3Number(cbinp->fileline(), width, hi)};
                    
                    // Create InsideRange [lo:hi]
                    AstInsideRange* rangep = new AstInsideRange{cbinp->fileline(), loConstp, hiConstp};
                    rangep->dtypeFrom(exprp);  // Set dtype from coverpoint expression
                    
                    // Create new bin
                    const string binName = cbinp->name() + "[" + std::to_string(i) + "]";
                    AstCoverBin* newBinp = new AstCoverBin{
                        cbinp->fileline(), binName, rangep, false, false};
                    
                    // Insert after previous bin
                    if (prevBinp) {
                        prevBinp->addNext(newBinp);
                    } else {
                        coverpointp->addBinsp(newBinp);
                    }
                    prevBinp = newBinp;
                }
                
                // Remove the AUTO bin from the list
                binp->unlinkFrBack();
                VL_DO_DANGLING(binp->deleteTree(), binp);
            } else {
                prevBinp = binp;
            }
            
            binp = nextBinp;
        }
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
        
        // Expand automatic bins before processing
        expandAutomaticBins(coverpointp, exprp);
        
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
            // Sanitize bin name to make it a valid C++ identifier
            string binName = cbinp->name();
            std::replace(binName.begin(), binName.end(), '[', '_');
            std::replace(binName.begin(), binName.end(), ']', '_');
            const string varName = "__Vcov_" + coverpointp->name() + "_" + binName;
            AstVar* const varp = new AstVar{
                cbinp->fileline(), VVarType::MEMBER, varName,
                cbinp->findUInt32DType()};
            varp->isStatic(false);
            m_covergroupp->addMembersp(varp);
            UINFO(4, "    Created member variable: " << varName << " type=" 
                  << static_cast<int>(cbinp->binsType()) 
                  << (cbinp->binsType() == VCoverBinsType::IGNORE ? " (IGNORE)" :
                      cbinp->binsType() == VCoverBinsType::ILLEGAL ? " (ILLEGAL)" : " (USER)") << endl);
            
            // Track this bin for coverage computation
            m_binInfos.push_back(BinInfo(cbinp, varp));
            
            // TODO: Generate coverage database registration
            // Coverage declarations need special handling for classes vs modules
            // For now, bin counters exist but aren't registered with verilator_coverage
            
            // Generate bin matching code in sample()
            generateBinMatchCode(coverpointp, cbinp, exprp, varp);
        }
    }
    
    void generateBinMatchCode(AstCoverpoint* coverpointp, AstCoverBin* binp,
                              AstNodeExpr* exprp, AstVar* hitVarp) {
        UINFO(4, "    Generating bin match for: " << binp->name() << endl);
        
        // Get the range list from the bin
        AstNode* rangep = binp->rangesp();
        if (!rangep) {
            UINFO(4, "      No range found for bin" << endl);
            return;
        }
        
        // Build condition by OR-ing all ranges together
        AstNodeExpr* fullCondp = nullptr;
        int rangeCount = 0;
        
        for (AstNode* currRangep = rangep; currRangep; currRangep = currRangep->nextp()) {
            if (++rangeCount > 100) {
                binp->v3error("Too many ranges in bin (max 100)");
                break;
            }
            
            // Clone the expression for this range
            AstNodeExpr* exprClonep = exprp->cloneTree(false);
            
            // Build condition for this specific range
            AstNodeExpr* rangeCondp = nullptr;
            
            if (AstInsideRange* irp = VN_CAST(currRangep, InsideRange)) {
                // INSIDERANGE has min and max as children
                // Convert to: (expr >= min) && (expr <= max)
                AstNode* minp = irp->lhsp();
                AstNode* maxp = irp->rhsp();
                
                if (minp && maxp) {
                    AstNodeExpr* minExprp = VN_CAST(minp, NodeExpr);
                    AstNodeExpr* maxExprp = VN_CAST(maxp, NodeExpr);
                    if (minExprp && maxExprp) {
                        AstNodeExpr* exprClone2p = exprp->cloneTree(false);
                        
                        // Check if this is a single-value range (min == max)
                        bool isSingleValue = false;
                        if (const AstConst* minConstp = VN_CAST(minExprp, Const)) {
                            if (const AstConst* maxConstp = VN_CAST(maxExprp, Const)) {
                                if (minConstp->toUInt() == maxConstp->toUInt()) {
                                    isSingleValue = true;
                                }
                            }
                        }
                        
                        if (isSingleValue) {
                            // Single value: just check equality
                            rangeCondp = new AstEq{binp->fileline(), exprClonep, 
                                                   minExprp->cloneTree(false)};
                            exprClone2p->deleteTree();
                        } else {
                            // Check if min is constant 0 - skip the >= check to avoid UNSIGNED warning
                            bool skipMinCheck = false;
                            if (const AstConst* constp = VN_CAST(minExprp, Const)) {
                                if (constp->toUInt() == 0) skipMinCheck = true;
                            }
                            
                            if (skipMinCheck) {
                                // Just check upper bound
                                rangeCondp = new AstLte{binp->fileline(), exprClonep, 
                                                        maxExprp->cloneTree(false)};
                                exprClone2p->deleteTree();
                            } else {
                                // Check both bounds
                                rangeCondp = new AstAnd{
                                    binp->fileline(),
                                    new AstGte{binp->fileline(), exprClonep, 
                                              minExprp->cloneTree(false)},
                                    new AstLte{binp->fileline(), exprClone2p, 
                                              maxExprp->cloneTree(false)}};
                            }
                        }
                    } else {
                        UINFO(4, "      Min or max is not an expression" << endl);
                        exprClonep->deleteTree();
                        continue;
                    }
                } else {
                    UINFO(4, "      Could not extract min/max from INSIDERANGE" << endl);
                    exprClonep->deleteTree();
                    continue;
                }
            } else {
                // Fallback: just check equality with the range expression
                AstNodeExpr* rangeExprp = VN_CAST(currRangep, NodeExpr);
                if (!rangeExprp) {
                    UINFO(4, "      Cannot convert range to expression" << endl);
                    exprClonep->deleteTree();
                    continue;
                }
                rangeCondp = new AstEq{binp->fileline(), exprClonep, 
                                       rangeExprp->cloneTree(false)};
            }
            
            // Combine with previous conditions using OR
            if (fullCondp) {
                fullCondp = new AstOr{binp->fileline(), fullCondp, rangeCondp};
            } else {
                fullCondp = rangeCondp;
            }
        }
        
        if (!fullCondp) {
            UINFO(4, "      No valid conditions generated" << endl);
            return;
        }
        
        // Apply iff condition if present - wraps the bin match condition
        if (AstNodeExpr* iffp = coverpointp->iffp()) {
            UINFO(6, "      Adding iff condition" << endl);
            fullCondp = new AstAnd{binp->fileline(), iffp->cloneTree(false), fullCondp};
        }
        
        // Create the increment statement
        AstNode* stmtp = new AstAssign{
            binp->fileline(),
            new AstVarRef{binp->fileline(), hitVarp, VAccess::WRITE},
            new AstAdd{binp->fileline(),
                new AstVarRef{binp->fileline(), hitVarp, VAccess::READ},
                new AstConst{binp->fileline(), AstConst::WidthedValue{}, 32, 1}}};
        
        // For illegal_bins, add an error message
        if (binp->binsType() == VCoverBinsType::ILLEGAL) {
            const string errMsg = "Illegal bin '" + binp->name() + "' hit in coverpoint '" 
                                + coverpointp->name() + "'";
            AstDisplay* errorp = new AstDisplay{binp->fileline(), VDisplayType::DT_ERROR, 
                                             errMsg, nullptr, nullptr};
            errorp->fmtp()->timeunit(m_covergroupp->timeunit());
            stmtp = stmtp->addNext(errorp);
            stmtp = stmtp->addNext(new AstStop{binp->fileline(), true});
        }
        
        // Create: if (condition) { hitVar++; [error if illegal] }
        AstIf* const ifp = new AstIf{binp->fileline(), fullCondp, stmtp, nullptr};
        
        UINFO(4, "      Adding bin match if statement to sample function" << endl);
        if (!m_sampleFuncp) {
            binp->v3error("INTERNAL: m_sampleFuncp is null when trying to add bin match code");
            return;
        }
        m_sampleFuncp->addStmtsp(ifp);
        UINFO(4, "      Successfully added if statement for bin: " << binp->name() << endl);
    }
    
    // Recursive helper to generate Cartesian product of cross bins
    void generateCrossBinsRecursive(AstCoverCross* crossp,
                                    const std::vector<AstCoverpoint*>& coverpointRefs,
                                    const std::vector<std::vector<AstCoverBin*>>& allCpBins,
                                    std::vector<AstCoverBin*> currentCombination,
                                    size_t dimension) {
        if (dimension == allCpBins.size()) {
            // Base case: we have a complete combination, generate the cross bin
            generateOneCrossBin(crossp, coverpointRefs, currentCombination);
            return;
        }
        
        // Recursive case: iterate through bins at current dimension
        for (AstCoverBin* binp : allCpBins[dimension]) {
            currentCombination.push_back(binp);
            generateCrossBinsRecursive(crossp, coverpointRefs, allCpBins, 
                                       currentCombination, dimension + 1);
            currentCombination.pop_back();
        }
    }
    
    // Generate a single cross bin for a specific combination of bins
    void generateOneCrossBin(AstCoverCross* crossp,
                            const std::vector<AstCoverpoint*>& coverpointRefs,
                            const std::vector<AstCoverBin*>& bins) {
        // Build sanitized name from all bins
        string binName;
        string varName = "__Vcov_" + crossp->name();
        
        for (size_t i = 0; i < bins.size(); ++i) {
            string sanitized = bins[i]->name();
            std::replace(sanitized.begin(), sanitized.end(), '[', '_');
            std::replace(sanitized.begin(), sanitized.end(), ']', '_');
            
            if (i > 0) {
                binName += "_x_";
                varName += "_x_";
            }
            binName += sanitized;
            varName += "_" + sanitized;
        }
        
        // Create member variable for this cross bin
        AstVar* const varp = new AstVar{
            crossp->fileline(), VVarType::MEMBER, varName,
            bins[0]->findUInt32DType()};
        varp->isStatic(false);
        m_covergroupp->addMembersp(varp);
        
        UINFO(4, "      Created cross bin variable: " << varName << endl);
        
        // Track this for coverage computation
        AstCoverBin* pseudoBinp = new AstCoverBin{
            crossp->fileline(), binName, nullptr, false, false};
        m_binInfos.push_back(BinInfo(pseudoBinp, varp));
        
        // Generate matching code: if (bin1 && bin2 && ... && binN) varName++;
        generateNWayCrossBinMatchCode(crossp, coverpointRefs, bins, varp);
    }
    
    // Generate matching code for N-way cross bin
    void generateNWayCrossBinMatchCode(AstCoverCross* crossp,
                                       const std::vector<AstCoverpoint*>& coverpointRefs,
                                       const std::vector<AstCoverBin*>& bins,
                                       AstVar* hitVarp) {
        UINFO(4, "      Generating " << bins.size() << "-way cross bin match" << endl);
        
        // Build combined condition by ANDing all bin conditions
        AstNodeExpr* fullCondp = nullptr;
        
        for (size_t i = 0; i < bins.size(); ++i) {
            AstNodeExpr* exprp = coverpointRefs[i]->exprp();
            if (!exprp) continue;
            
            AstNodeExpr* condp = buildBinCondition(bins[i], exprp);
            if (!condp) continue;
            
            if (fullCondp) {
                fullCondp = new AstAnd{crossp->fileline(), fullCondp, condp};
            } else {
                fullCondp = condp;
            }
        }
        
        if (!fullCondp) return;
        
        // Generate: if (cond1 && cond2 && ... && condN) { ++varName; }
        AstNodeStmt* incrp = new AstAssign{
            crossp->fileline(),
            new AstVarRef{crossp->fileline(), hitVarp, VAccess::WRITE},
            new AstAdd{crossp->fileline(),
                      new AstVarRef{crossp->fileline(), hitVarp, VAccess::READ},
                      new AstConst{crossp->fileline(), AstConst::WidthedValue{}, 32, 1}}};
        
        AstIf* const ifp = new AstIf{crossp->fileline(), fullCondp, incrp};
        m_sampleFuncp->addStmtsp(ifp);
    }
    
    void generateCrossCode(AstCoverCross* crossp) {
        if (!m_sampleFuncp || !m_constructorp) {
            crossp->v3warn(E_UNSUPPORTED, "Cross coverage without sample() or constructor");
            return;
        }
        
        UINFO(4, "  Generating code for cross: " << crossp->name() << endl);
        
        // Resolve coverpoint references and build list
        std::vector<AstCoverpoint*> coverpointRefs;
        AstNode* itemp = crossp->itemsp();
        while (itemp) {
            AstNode* nextp = itemp->nextp();
            AstCoverpointRef* const refp = VN_CAST(itemp, CoverpointRef);
            if (refp) {
                // Find the referenced coverpoint
                AstCoverpoint* foundCpp = nullptr;
                for (AstCoverpoint* cpp : m_coverpoints) {
                    if (cpp->name() == refp->name()) {
                        foundCpp = cpp;
                        break;
                    }
                }
                
                if (!foundCpp) {
                    refp->v3warn(E_UNSUPPORTED, "Cross references unknown coverpoint: " + refp->name());
                    return;
                }
                
                coverpointRefs.push_back(foundCpp);
                
                // Delete the reference node - it's no longer needed
                VL_DO_DANGLING(refp->unlinkFrBack()->deleteTree(), refp);
            }
            itemp = nextp;
        }
        
        if (coverpointRefs.size() < 2) {
            crossp->v3warn(E_UNSUPPORTED, "Cross coverage requires at least 2 coverpoints");
            return;
        }
        
        UINFO(4, "    Generating " << coverpointRefs.size() << "-way cross" << endl);
        
        // Collect bins from all coverpoints (excluding ignore/illegal bins)
        std::vector<std::vector<AstCoverBin*>> allCpBins;
        for (AstCoverpoint* cpp : coverpointRefs) {
            std::vector<AstCoverBin*> cpBins;
            for (AstNode* binp = cpp->binsp(); binp; binp = binp->nextp()) {
                AstCoverBin* const cbinp = VN_CAST(binp, CoverBin);
                if (cbinp && cbinp->binsType() == VCoverBinsType::USER) {
                    cpBins.push_back(cbinp);
                }
            }
            UINFO(4, "      Found " << cpBins.size() << " bins in " << cpp->name() << endl);
            allCpBins.push_back(cpBins);
        }
        
        // Generate cross bins using Cartesian product
        generateCrossBinsRecursive(crossp, coverpointRefs, allCpBins, {}, 0);
    }
    
    AstNodeExpr* buildBinCondition(AstCoverBin* binp, AstNodeExpr* exprp) {
        // Get the range list from the bin
        AstNode* rangep = binp->rangesp();
        if (!rangep) return nullptr;
        
        // Build condition by OR-ing all ranges together
        AstNodeExpr* fullCondp = nullptr;
        
        for (AstNode* currRangep = rangep; currRangep; currRangep = currRangep->nextp()) {
            AstNodeExpr* exprClonep = exprp->cloneTree(false);
            AstNodeExpr* rangeCondp = nullptr;
            
            if (AstInsideRange* irp = VN_CAST(currRangep, InsideRange)) {
                AstNode* minp = irp->lhsp();
                AstNode* maxp = irp->rhsp();
                
                if (minp && maxp) {
                    AstNodeExpr* minExprp = VN_CAST(minp, NodeExpr);
                    AstNodeExpr* maxExprp = VN_CAST(maxp, NodeExpr);
                    if (minExprp && maxExprp) {
                        AstNodeExpr* exprClone2p = exprp->cloneTree(false);
                        
                        AstConst* minConstp = VN_CAST(minExprp, Const);
                        AstConst* maxConstp = VN_CAST(maxExprp, Const);
                        
                        if (minConstp && maxConstp && minConstp->toSInt() == maxConstp->toSInt()) {
                            // Single value
                            rangeCondp = new AstEq{binp->fileline(), exprClonep, 
                                                   minExprp->cloneTree(false)};
                        } else {
                            // Range
                            AstNodeExpr* gep = new AstGte{binp->fileline(), exprClonep, 
                                                          minExprp->cloneTree(false)};
                            AstNodeExpr* lep = new AstLte{binp->fileline(), exprClone2p, 
                                                          maxExprp->cloneTree(false)};
                            rangeCondp = new AstAnd{binp->fileline(), gep, lep};
                        }
                    }
                }
            } else if (AstConst* constp = VN_CAST(currRangep, Const)) {
                rangeCondp = new AstEq{binp->fileline(), exprClonep, constp->cloneTree(false)};
            }
            
            if (rangeCondp) {
                fullCondp = fullCondp ? new AstOr{binp->fileline(), fullCondp, rangeCondp} 
                                      : rangeCondp;
            }
        }
        
        return fullCondp;
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
        
        if (m_binInfos.empty()) {
            UINFO(4, "    No bins found for coverage computation" << endl);
            return;
        }
        
        UINFO(6, "    Found " << m_binInfos.size() << " bins for coverage" << endl);
        
        // Generate code for get_inst_coverage() only (get_coverage() needs aggregation)
        if (getInstCoveragep) {
            generateCoverageMethodBody(getInstCoveragep);
        }
    }
    
    void generateCoverageMethodBody(AstFunc* funcp) {
        FileLine* fl = funcp->fileline();
        
        // Count total bins (excluding ignore_bins and illegal_bins)
        int totalBins = 0;
        for (const BinInfo& bi : m_binInfos) {
            UINFO(6, "      Bin: " << bi.binp->name() << " type=" 
                  << (int)bi.binp->binsType() << " IGNORE=" << (int)VCoverBinsType::IGNORE 
                  << " ILLEGAL=" << (int)VCoverBinsType::ILLEGAL << endl);
            if (bi.binp->binsType() != VCoverBinsType::IGNORE 
                && bi.binp->binsType() != VCoverBinsType::ILLEGAL) {
                totalBins++;
            }
        }
        
        UINFO(4, "    Total regular bins: " << totalBins << " of " << m_binInfos.size() << endl);
        
        if (totalBins == 0) {
            // No coverage to compute - return 100%
            AstVar* returnVarp = VN_AS(funcp->fvarp(), Var);
            if (returnVarp) {
                funcp->addStmtsp(new AstAssign{
                    fl,
                    new AstVarRef{fl, returnVarp, VAccess::WRITE},
                    new AstConst{fl, AstConst::RealDouble{}, 100.0}});
            }
            return;
        }
        
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
        
        // For each regular bin, if count > 0, increment covered_count
        for (const BinInfo& bi : m_binInfos) {
            // Skip ignore_bins and illegal_bins in coverage calculation
            if (bi.binp->binsType() == VCoverBinsType::IGNORE 
                || bi.binp->binsType() == VCoverBinsType::ILLEGAL) {
                continue;
            }
            
            // if (bin_count > 0) covered_count++;
            AstIf* ifp = new AstIf{
                fl,
                new AstGt{fl,
                    new AstVarRef{fl, bi.varp, VAccess::READ},
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
                                              static_cast<double>(totalBins)};
        
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
        
        UINFO(6, "    Added coverage computation to " << funcp->name() << " with " 
              << totalBins << " bins (excluding ignore/illegal)" << endl);
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
            m_coverCrosses.clear();
            
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

    void visit(AstCoverCross* nodep) override {
        UINFO(9, "Found cross: " << nodep->name() << endl);
        m_coverCrosses.push_back(nodep);
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
