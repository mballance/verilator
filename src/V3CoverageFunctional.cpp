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
// Not yet implemented (future PRs):
//   - Auto-bins expansion (PR-3): expandAutomaticBins, createImplicitAutoBins,
//     extractValuesFromRange, getExcludedValues, hasRegularBins, getAutoBinMax,
//     generateArrayBins, generateArrayBinMatchCode
//   - Transition bins (PR-4): createPrevValueVar, createSeqStateVar,
//     generateTransitionBinMatchCode, generateMultiValueTransitionCode,
//     generateSingleTransitionCode, generateTransitionArrayBins,
//     buildTransitionItemCondition, generateTransitionStateCase
//   - Cross coverage (PR-5): generateCrossBinsRecursive, generateOneCrossBin,
//     generateNWayCrossBinMatchCode, generateCrossCode
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
    AstFunc* m_sampleFuncp = nullptr;  // Current sample() function
    AstFunc* m_constructorp = nullptr;  // Current constructor
    std::vector<AstCoverpoint*> m_coverpoints;  // Coverpoints in current covergroup
    std::vector<AstCoverCross*> m_coverCrosses;  // Cross coverage items in current covergroup

    // Structure to track bins with their variables and options
    struct BinInfo final {
        AstCoverBin* binp;
        AstVar* varp;
        int atLeast;  // Minimum hits required for coverage (from option.at_least)
        AstCoverpoint* coverpointp;  // Associated coverpoint (or nullptr for cross bins)
        AstCoverCross* crossp;  // Associated cross (or nullptr for coverpoint bins)
        BinInfo(AstCoverBin* b, AstVar* v, int al = 1, AstCoverpoint* cp = nullptr,
                AstCoverCross* cr = nullptr)
            : binp{b}
            , varp{v}
            , atLeast{al}
            , coverpointp{cp}
            , crossp{cr} {}
    };
    std::vector<BinInfo> m_binInfos;  // All bins in current covergroup

    // METHODS
    void clearBinInfos() {
        // Delete pseudo-bins created for cross coverage (they're never inserted into the AST)
        for (const BinInfo& bi : m_binInfos) {
            if (!bi.coverpointp && bi.crossp && bi.binp) {
                VL_DO_DANGLING(bi.binp->deleteTree(), bi.binp);
            }
        }
        m_binInfos.clear();
    }

    void processCovergroup() {
        if (!m_covergroupp) return;

        UINFO(4, "Processing covergroup: " << m_covergroupp->name() << " with "
                                           << m_coverpoints.size() << " coverpoints and "
                                           << m_coverCrosses.size() << " crosses" << endl);

        // Clear bin info for this covergroup (deleting any orphaned cross pseudo-bins)
        clearBinInfos();

        // For each coverpoint, generate sampling code
        for (AstCoverpoint* cpp : m_coverpoints) { generateCoverpointCode(cpp); }

        // Cross coverage is not yet supported (PR-5); nodes were already deleted in visit()

        // Generate coverage computation code (even for empty covergroups)
        generateCoverageComputationCode();

        // TODO: Generate instance registry infrastructure for static get_coverage()
        // This requires:
        // - Static registry members (t_instances, s_mutex)
        // - registerInstance() / unregisterInstance() methods
        // - Proper C++ emission in EmitC backend
        // For now, get_coverage() returns 0.0 (placeholder)

        // Generate coverage database registration if coverage is enabled
        if (v3Global.opt.coverage()) { generateCoverageRegistration(); }

        // Clean up orphaned cross pseudo-bins now that we're done with them
        clearBinInfos();
    }

    int getCoverpointAtLeast(AstCoverpoint* coverpointp) {
        // Look for option.at_least in coverpoint options
        for (AstNode* optionp = coverpointp->optionsp(); optionp; optionp = optionp->nextp()) {
            if (AstCoverOption* optp = VN_CAST(optionp, CoverOption)) {
                if (optp->optionType() == VCoverOptionType::AT_LEAST) {
                    // Extract the value from the option expression
                    if (AstConst* constp = VN_CAST(optp->valuep(), Const)) {
                        return constp->toSInt();
                    }
                }
            }
        }
        return 1;  // Default: at least 1 hit required
    }

    void generateCoverpointCode(AstCoverpoint* coverpointp) {
        if (!m_sampleFuncp || !m_constructorp) {
            coverpointp->v3warn(E_UNSUPPORTED,
                                "Coverpoint without sample() or constructor");  // LCOV_EXCL_LINE
            return;
        }

        UINFO(4, "  Generating code for coverpoint: " << coverpointp->name() << endl);

        // Get the coverpoint expression
        AstNodeExpr* exprp = coverpointp->exprp();
        if (!exprp) {
            coverpointp->v3warn(E_UNSUPPORTED, "Coverpoint without expression");  // LCOV_EXCL_LINE
            return;
        }

        // TODO (PR-3): Expand automatic bins and create implicit auto-bins here
        // expandAutomaticBins(coverpointp, exprp);
        // createImplicitAutoBins(coverpointp, exprp);

        // Extract option values for this coverpoint
        int atLeastValue = getCoverpointAtLeast(coverpointp);
        UINFO(6, "    Coverpoint at_least = " << atLeastValue << endl);

        // Generate member variables and matching code for each bin
        // Process in two passes: first non-default bins, then default bins
        std::vector<AstCoverBin*> defaultBins;
        int binCount = 0;
        for (AstNode* binp = coverpointp->binsp(); binp; binp = binp->nextp()) {
            if (++binCount > 1000) {
                coverpointp->v3error("Too many bins or infinite loop detected in bin iteration");
                break;
            }
            AstCoverBin* const cbinp = VN_CAST(binp, CoverBin);
            if (!cbinp) continue;

            // Defer default bins to second pass
            if (cbinp->binsType() == VCoverBinsType::DEFAULT) {
                defaultBins.push_back(cbinp);
                continue;
            }

            // TODO (PR-3): Handle AUTO bins expansion here
            if (cbinp->binsType() == VCoverBinsType::AUTO) {
                UINFO(4, "    Skipping AUTO bin (not yet implemented, PR-3): " << cbinp->name()
                                                                               << endl);
                continue;
            }

            // TODO (PR-3/4): Handle array bins here
            // if (cbinp->isArray()) { generateArrayBins/generateTransitionArrayBins ... }
            if (cbinp->isArray()) {
                UINFO(4,
                      "    Skipping array bin (not yet implemented): " << cbinp->name() << endl);
                continue;
            }

            // TODO (PR-4): Handle transition bins here
            if (cbinp->binsType() == VCoverBinsType::TRANSITION) {
                UINFO(4, "    Skipping TRANSITION bin (not yet implemented, PR-4): "
                             << cbinp->name() << endl);
                continue;
            }

            // Create a member variable to track hits for this bin
            // Sanitize bin name to make it a valid C++ identifier
            string binName = cbinp->name();
            std::replace(binName.begin(), binName.end(), '[', '_');
            std::replace(binName.begin(), binName.end(), ']', '_');
            const string varName = "__Vcov_" + coverpointp->name() + "_" + binName;
            AstVar* const varp = new AstVar{cbinp->fileline(), VVarType::MEMBER, varName,
                                            cbinp->findUInt32DType()};
            varp->isStatic(false);
            m_covergroupp->addMembersp(varp);
            UINFO(4, "    Created member variable: "
                         << varName << " type=" << static_cast<int>(cbinp->binsType())
                         << (cbinp->binsType() == VCoverBinsType::BINS_IGNORE    ? " (IGNORE)"
                             : cbinp->binsType() == VCoverBinsType::BINS_ILLEGAL ? " (ILLEGAL)"
                                                                                 : " (USER)")
                         << endl);

            // Track this bin for coverage computation with at_least value
            m_binInfos.push_back(BinInfo(cbinp, varp, atLeastValue, coverpointp));

            // Generate bin matching code in sample()
            generateBinMatchCode(coverpointp, cbinp, exprp, varp);
        }

        // Second pass: Handle default bins
        // Default bin matches when value doesn't match any other explicit bin
        for (AstCoverBin* defBinp : defaultBins) {
            // Create member variable for default bin
            string binName = defBinp->name();
            std::replace(binName.begin(), binName.end(), '[', '_');
            std::replace(binName.begin(), binName.end(), ']', '_');
            const string varName = "__Vcov_" + coverpointp->name() + "_" + binName;
            AstVar* const varp = new AstVar{defBinp->fileline(), VVarType::MEMBER, varName,
                                            defBinp->findUInt32DType()};
            varp->isStatic(false);
            m_covergroupp->addMembersp(varp);
            UINFO(4, "    Created default bin variable: " << varName << endl);

            // Track for coverage computation
            m_binInfos.push_back(BinInfo(defBinp, varp, atLeastValue, coverpointp));

            // Generate matching code: if (NOT (bin1 OR bin2 OR ... OR binN))
            generateDefaultBinMatchCode(coverpointp, defBinp, exprp, varp);
        }
    }

    void generateBinMatchCode(AstCoverpoint* coverpointp, AstCoverBin* binp, AstNodeExpr* exprp,
                              AstVar* hitVarp) {
        UINFO(4, "    Generating bin match for: " << binp->name() << endl);

        // Build the bin matching condition using the shared function
        AstNodeExpr* fullCondp = buildBinCondition(binp, exprp);

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
            binp->fileline(), new AstVarRef{binp->fileline(), hitVarp, VAccess::WRITE},
            new AstAdd{binp->fileline(), new AstVarRef{binp->fileline(), hitVarp, VAccess::READ},
                       new AstConst{binp->fileline(), AstConst::WidthedValue{}, 32, 1}}};

        // For illegal_bins, add an error message
        if (binp->binsType() == VCoverBinsType::BINS_ILLEGAL) {
            const string errMsg = "Illegal bin '" + binp->name() + "' hit in coverpoint '"
                                  + coverpointp->name() + "'";
            AstDisplay* errorp = new AstDisplay{binp->fileline(), VDisplayType::DT_ERROR, errMsg,
                                                nullptr, nullptr};
            errorp->fmtp()->timeunit(m_covergroupp->timeunit());
            stmtp = stmtp->addNext(errorp);
            stmtp = stmtp->addNext(new AstStop{binp->fileline(), true});
        }

        // Create: if (condition) { hitVar++; [error if illegal] }
        AstIf* const ifp = new AstIf{binp->fileline(), fullCondp, stmtp, nullptr};

        UINFO(4, "      Adding bin match if statement to sample function" << endl);
        if (!m_sampleFuncp)
            binp->v3fatalSrc("m_sampleFuncp is null when trying to add bin match code");
        m_sampleFuncp->addStmtsp(ifp);
        UINFO(4, "      Successfully added if statement for bin: " << binp->name() << endl);
    }

    // Generate matching code for default bins
    // Default bins match when value doesn't match any other explicit bin
    void generateDefaultBinMatchCode(AstCoverpoint* coverpointp, AstCoverBin* defBinp,
                                     AstNodeExpr* exprp, AstVar* hitVarp) {
        UINFO(4, "    Generating default bin match for: " << defBinp->name() << endl);

        // Build OR of all non-default, non-ignore bins
        AstNodeExpr* anyBinMatchp = nullptr;

        for (AstNode* binp = coverpointp->binsp(); binp; binp = binp->nextp()) {
            AstCoverBin* const cbinp = VN_CAST(binp, CoverBin);
            if (!cbinp) continue;

            // Skip default, ignore, and illegal bins
            if (cbinp->binsType() == VCoverBinsType::DEFAULT
                || cbinp->binsType() == VCoverBinsType::BINS_IGNORE
                || cbinp->binsType() == VCoverBinsType::BINS_ILLEGAL) {
                continue;
            }

            // Build condition for this bin
            AstNodeExpr* binCondp = buildBinCondition(cbinp, exprp);
            if (!binCondp) continue;

            // OR with previous conditions
            if (anyBinMatchp) {
                anyBinMatchp = new AstOr{defBinp->fileline(), anyBinMatchp, binCondp};
            } else {
                anyBinMatchp = binCondp;
            }
        }

        // Default matches when NO explicit bin matches
        AstNodeExpr* defaultCondp = nullptr;
        if (anyBinMatchp) {
            // NOT (bin1 OR bin2 OR ... OR binN)
            defaultCondp = new AstNot{defBinp->fileline(), anyBinMatchp};
        } else {
            // No other bins - default always matches (shouldn't happen in practice)
            defaultCondp = new AstConst{defBinp->fileline(), AstConst::BitTrue{}};
        }

        // Apply iff condition if present
        if (AstNodeExpr* iffp = coverpointp->iffp()) {
            defaultCondp = new AstAnd{defBinp->fileline(), iffp->cloneTree(false), defaultCondp};
        }

        // Create increment statement
        AstNode* stmtp = new AstAssign{
            defBinp->fileline(), new AstVarRef{defBinp->fileline(), hitVarp, VAccess::WRITE},
            new AstAdd{defBinp->fileline(),
                       new AstVarRef{defBinp->fileline(), hitVarp, VAccess::READ},
                       new AstConst{defBinp->fileline(), AstConst::WidthedValue{}, 32, 1}}};

        // Create if statement
        AstIf* const ifp = new AstIf{defBinp->fileline(), defaultCondp, stmtp, nullptr};

        if (!m_sampleFuncp) defBinp->v3fatalSrc("m_sampleFuncp is null for default bin");
        m_sampleFuncp->addStmtsp(ifp);
        UINFO(4, "      Successfully added default bin if statement" << endl);
    }

    AstNodeExpr* buildBinCondition(AstCoverBin* binp, AstNodeExpr* exprp) {
        // Get the range list from the bin
        AstNode* rangep = binp->rangesp();
        if (!rangep) return nullptr;

        // Check if this is a wildcard bin
        bool isWildcard = (binp->binsType() == VCoverBinsType::BINS_WILDCARD);

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
                        AstConst* minConstp = VN_CAST(minExprp, Const);
                        AstConst* maxConstp = VN_CAST(maxExprp, Const);

                        if (minConstp && maxConstp && minConstp->toSInt() == maxConstp->toSInt()) {
                            // Single value
                            if (isWildcard) {
                                rangeCondp = buildWildcardCondition(binp, exprClonep, minConstp);
                            } else {
                                rangeCondp = new AstEq{binp->fileline(), exprClonep,
                                                       minExprp->cloneTree(false)};
                            }
                        } else {
                            // Range - use signed comparisons if expression is signed
                            AstNodeExpr* gep;
                            AstNodeExpr* lep;
                            if (exprClonep->isSigned()) {
                                AstNodeExpr* const exprClone2p = exprp->cloneTree(false);
                                gep = new AstGteS{binp->fileline(), exprClonep,
                                                  minExprp->cloneTree(false)};
                                lep = new AstLteS{binp->fileline(), exprClone2p,
                                                  maxExprp->cloneTree(false)};
                                rangeCondp = new AstAnd{binp->fileline(), gep, lep};
                            } else {
                                // For unsigned, skip >= 0 check as it's always true
                                AstConst* minConstp = VN_CAST(minExprp, Const);
                                AstConst* maxConstp = VN_CAST(maxExprp, Const);
                                const int exprWidth = exprClonep->widthMin();
                                bool skipLowerCheck = (minConstp && minConstp->toUQuad() == 0);
                                bool skipUpperCheck = false;
                                if (maxConstp && exprWidth > 0 && exprWidth <= 64) {
                                    const uint64_t maxVal = (exprWidth == 64)
                                                                ? ~static_cast<uint64_t>(0)
                                                                : ((1ULL << exprWidth) - 1ULL);
                                    skipUpperCheck = (maxConstp->toUQuad() == maxVal);
                                }

                                if (skipLowerCheck && skipUpperCheck) {
                                    rangeCondp
                                        = new AstConst{binp->fileline(), AstConst::BitTrue{}};
                                } else if (skipLowerCheck) {
                                    // Only check upper bound for [0:max]
                                    lep = new AstLte{binp->fileline(), exprClonep,
                                                     maxExprp->cloneTree(false)};
                                    rangeCondp = lep;
                                } else if (skipUpperCheck) {
                                    // Only check lower bound when upper is maximal
                                    gep = new AstGte{binp->fileline(), exprClonep,
                                                     minExprp->cloneTree(false)};
                                    rangeCondp = gep;
                                } else {
                                    AstNodeExpr* const exprClone2p = exprp->cloneTree(false);
                                    lep = new AstLte{binp->fileline(), exprClone2p,
                                                     maxExprp->cloneTree(false)};
                                    gep = new AstGte{binp->fileline(), exprClonep,
                                                     minExprp->cloneTree(false)};
                                    rangeCondp = new AstAnd{binp->fileline(), gep, lep};
                                }
                            }
                        }
                    }
                }
            } else if (AstConst* constp = VN_CAST(currRangep, Const)) {
                if (isWildcard) {
                    rangeCondp = buildWildcardCondition(binp, exprClonep, constp);
                } else {
                    rangeCondp = new AstEq{binp->fileline(), exprClonep, constp->cloneTree(false)};
                }
            }

            if (rangeCondp) {
                fullCondp
                    = fullCondp ? new AstOr{binp->fileline(), fullCondp, rangeCondp} : rangeCondp;
            }
        }

        return fullCondp;
    }

    // Build a wildcard condition: (expr & mask) == (value & mask)
    // where mask has 1s for defined bits and 0s for wildcard bits
    AstNodeExpr* buildWildcardCondition(AstCoverBin* binp, AstNodeExpr* exprp, AstConst* constp) {
        FileLine* fl = binp->fileline();

        // Extract mask from constant (bits that are not X/Z)
        V3Number mask{constp, constp->width()};
        V3Number value{constp, constp->width()};

        for (int bit = 0; bit < constp->width(); ++bit) {
            // If bit is X or Z (don't care), set mask bit to 0
            // Otherwise set to 1 and keep the value
            if (constp->num().bitIs0(bit) || constp->num().bitIs1(bit)) {
                mask.setBit(bit, 1);
                value.setBit(bit, constp->num().bitIs1(bit) ? 1 : 0);
            } else {
                mask.setBit(bit, 0);
                value.setBit(bit, 0);
            }
        }

        // Generate: (expr & mask) == (value & mask)
        AstConst* maskConstp = new AstConst{fl, mask};
        AstConst* valueConstp = new AstConst{fl, value};

        AstNodeExpr* exprMasked = new AstAnd{fl, exprp, maskConstp};
        AstNodeExpr* valueMasked = new AstAnd{fl, valueConstp, maskConstp->cloneTree(false)};

        return new AstEq{fl, exprMasked, valueMasked};
    }

    void generateCoverageComputationCode() {
        UINFO(4, "  Generating coverage computation code" << endl);

        // Find get_coverage() and get_inst_coverage() methods
        AstFunc* getCoveragep = nullptr;
        AstFunc* getInstCoveragep = nullptr;

        int memberCount = 0;
        for (AstNode* itemp = m_covergroupp->membersp(); itemp; itemp = itemp->nextp()) {
            if (++memberCount > 10000) {
                m_covergroupp->v3error(
                    "Too many members or infinite loop in membersp iteration (1)");
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

        // Even if there are no bins, we still need to generate the coverage methods
        // Empty covergroups should return 100% coverage
        if (m_binInfos.empty()) {
            UINFO(4, "    No bins found, will generate method to return 100%" << endl);
        } else {
            UINFO(6, "    Found " << m_binInfos.size() << " bins for coverage" << endl);
        }

        // Generate code for get_inst_coverage()
        if (getInstCoveragep) { generateCoverageMethodBody(getInstCoveragep); }

        // Generate code for get_coverage() (type-level)
        // NOTE: Full type-level coverage requires instance tracking infrastructure
        // For now, return 0.0 as a placeholder
        if (getCoveragep) {
            AstVar* returnVarp = VN_AS(getCoveragep->fvarp(), Var);
            if (returnVarp) {
                // TODO: Implement proper type-level coverage aggregation
                // This requires tracking all instances and averaging their coverage
                // For now, return 0.0
                getCoveragep->addStmtsp(new AstAssign{
                    getCoveragep->fileline(),
                    new AstVarRef{getCoveragep->fileline(), returnVarp, VAccess::WRITE},
                    new AstConst{getCoveragep->fileline(), AstConst::RealDouble{}, 0.0}});
                UINFO(4, "    Added placeholder get_coverage() (returns 0.0)" << endl);
            }
        }
    }

    void generateCoverageMethodBody(AstFunc* funcp) {
        FileLine* fl = funcp->fileline();

        // Count total bins (excluding ignore_bins and illegal_bins)
        int totalBins = 0;
        for (const BinInfo& bi : m_binInfos) {
            UINFO(6, "      Bin: " << bi.binp->name() << " type=" << (int)bi.binp->binsType()
                                   << " IGNORE=" << (int)VCoverBinsType::BINS_IGNORE
                                   << " ILLEGAL=" << (int)VCoverBinsType::BINS_ILLEGAL << endl);
            if (bi.binp->binsType() != VCoverBinsType::BINS_IGNORE
                && bi.binp->binsType() != VCoverBinsType::BINS_ILLEGAL) {
                totalBins++;
            }
        }

        UINFO(4, "    Total regular bins: " << totalBins << " of " << m_binInfos.size() << endl);

        if (totalBins == 0) {
            // No coverage to compute - return 100%
            UINFO(4, "    Empty covergroup, returning 100.0" << endl);
            AstVar* returnVarp = VN_AS(funcp->fvarp(), Var);

            // Find and replace existing assignment to return variable
            AstAssign* existingReturnAssign = nullptr;
            for (AstNode* stmtp = funcp->stmtsp(); stmtp; stmtp = stmtp->nextp()) {
                if (AstAssign* assignp = VN_CAST(stmtp, Assign)) {
                    if (AstVarRef* lhsVarRef = VN_CAST(assignp->lhsp(), VarRef)) {
                        if (lhsVarRef->varp() == returnVarp) {
                            existingReturnAssign = assignp;
                            break;
                        }
                    }
                }
            }

            if (existingReturnAssign) {
                // Replace the RHS of existing assignment from 0 to 100.0
                AstNode* oldRhs = existingReturnAssign->rhsp();
                if (oldRhs) VL_DO_DANGLING(oldRhs->unlinkFrBack()->deleteTree(), oldRhs);
                existingReturnAssign->rhsp(new AstConst{fl, AstConst::RealDouble{}, 100.0});
                UINFO(4, "    Replaced return value assignment to 100.0" << endl);
            } else if (returnVarp) {
                // No existing assignment found, add one
                AstAssign* assignp
                    = new AstAssign{fl, new AstVarRef{fl, returnVarp, VAccess::WRITE},
                                    new AstConst{fl, AstConst::RealDouble{}, 100.0}};
                funcp->addStmtsp(assignp);
                UINFO(4, "    Added assignment to return 100.0" << endl);
            }
            return;
        }

        // Create local variable to count covered bins
        AstVar* coveredCountp
            = new AstVar{fl, VVarType::BLOCKTEMP, "__Vcovered_count", funcp->findUInt32DType()};
        coveredCountp->funcLocal(true);
        funcp->addStmtsp(coveredCountp);

        // Initialize: covered_count = 0
        funcp->addStmtsp(new AstAssign{fl, new AstVarRef{fl, coveredCountp, VAccess::WRITE},
                                       new AstConst{fl, AstConst::WidthedValue{}, 32, 0}});

        // For each regular bin, if count > 0, increment covered_count
        for (const BinInfo& bi : m_binInfos) {
            // Skip ignore_bins and illegal_bins in coverage calculation
            if (bi.binp->binsType() == VCoverBinsType::BINS_IGNORE
                || bi.binp->binsType() == VCoverBinsType::BINS_ILLEGAL) {
                continue;
            }

            // if (bin_count >= at_least) covered_count++;
            AstIf* ifp = new AstIf{
                fl,
                new AstGte{fl, new AstVarRef{fl, bi.varp, VAccess::READ},
                           new AstConst{fl, AstConst::WidthedValue{}, 32,
                                        static_cast<uint32_t>(bi.atLeast)}},
                new AstAssign{fl, new AstVarRef{fl, coveredCountp, VAccess::WRITE},
                              new AstAdd{fl, new AstVarRef{fl, coveredCountp, VAccess::READ},
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
        AstNodeExpr* coveredReal
            = new AstIToRD{fl, new AstVarRef{fl, coveredCountp, VAccess::READ}};

        // Create total bins as a double constant
        AstNodeExpr* totalReal
            = new AstConst{fl, AstConst::RealDouble{}, static_cast<double>(totalBins)};

        // Divide using AstDivD (double division that emits native /)
        AstNodeExpr* divExpr = new AstDivD{fl, coveredReal, totalReal};

        // Multiply by 100 using AstMulD (double multiplication that emits native *)
        AstNodeExpr* hundredConst = new AstConst{fl, AstConst::RealDouble{}, 100.0};
        AstNodeExpr* coverageExpr = new AstMulD{fl, hundredConst, divExpr};

        // Assign to return variable
        funcp->addStmtsp(
            new AstAssign{fl, new AstVarRef{fl, returnVarp, VAccess::WRITE}, coverageExpr});

        UINFO(6, "    Added coverage computation to " << funcp->name() << " with " << totalBins
                                                      << " bins (excluding ignore/illegal)"
                                                      << endl);
    }

    int countBins(AstCoverpoint* nodep) {
        int count = 0;
        for (AstNode* binp = nodep->binsp(); binp; binp = binp->nextp()) { count++; }
        return count;
    }

    void generateCoverageRegistration() {
        // Generate VL_COVER_INSERT calls for each bin in the covergroup
        // This registers the bins with the coverage database so they can be reported

        UINFO(4, "  Generating coverage database registration for " << m_binInfos.size() << " bins"
                                                                    << endl);

        if (m_binInfos.empty()) return;

        // We need to add the registration code to the constructor
        // The registration should happen after member variables are initialized
        if (!m_constructorp) {
            m_covergroupp->v3warn(
                E_UNSUPPORTED,
                "Cannot generate coverage registration without constructor");  // LCOV_EXCL_LINE
            return;
        }

        // For each bin, generate a VL_COVER_INSERT call
        // The calls use CCall nodes to invoke VL_COVER_INSERT macro
        for (const BinInfo& binInfo : m_binInfos) {
            AstVar* varp = binInfo.varp;
            AstCoverBin* binp = binInfo.binp;
            AstCoverpoint* coverpointp = binInfo.coverpointp;
            AstCoverCross* crossp = binInfo.crossp;

            // Skip illegal and ignore bins - they don't count towards coverage
            if (binp->binsType() == VCoverBinsType::BINS_IGNORE
                || binp->binsType() == VCoverBinsType::BINS_ILLEGAL) {
                continue;
            }

            FileLine* fl = binp->fileline();

            // Build hierarchical name: covergroup.coverpoint.bin or covergroup.cross.bin
            std::string hierName = m_covergroupp->name();
            std::string binName = binp->name();

            if (coverpointp) {
                // Coverpoint bin: use coverpoint name or generate from expression
                std::string cpName = coverpointp->name();
                if (cpName.empty()) {
                    // Generate name from expression
                    if (coverpointp->exprp()) {
                        cpName = coverpointp->exprp()->name();
                        if (cpName.empty()) cpName = "cp";
                    } else {
                        cpName = "cp";
                    }
                }
                hierName += "." + cpName;
            } else if (crossp) {
                // Cross bin: use cross name
                std::string crossName = crossp->name();
                if (crossName.empty()) crossName = "cross";
                hierName += "." + crossName;
            }
            hierName += "." + binName;

            // Generate: VL_COVER_INSERT(contextp, hier, &binVar, "page", "v_funccov/...", ...)

            UINFO(6, "    Registering bin: " << hierName << " -> " << varp->name() << endl);

            // Build the coverage insert as a C statement
            // The variable reference needs to be &this->varname, where varname gets mangled to
            // __PVT__varname Use "page" field with v_funccov prefix so type is extracted correctly
            // (consistent with code coverage)
            std::string pageName = "v_funccov/" + m_covergroupp->name();
            std::string insertCall = "VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), ";
            insertCall += "\"" + hierName + "\", ";
            insertCall += "&(this->__PVT__" + varp->name() + "), ";
            insertCall += "\"page\", \"" + pageName + "\", ";
            insertCall += "\"filename\", \"" + fl->filename() + "\", ";
            insertCall += "\"lineno\", \"" + std::to_string(fl->lineno()) + "\", ";
            insertCall += "\"column\", \"" + std::to_string(fl->firstColumn()) + "\", ";
            insertCall += "\"bin\", \"" + binName + "\");";

            // Create a statement node with the coverage insert call
            AstCStmt* cstmtp = new AstCStmt{fl, insertCall};

            // Add to constructor
            m_constructorp->addStmtsp(cstmtp);

            UINFO(6, "      Added VL_COVER_INSERT call to constructor" << endl);
        }
    }

    // VISITORS
    void visit(AstClass* nodep) override {
        UINFO(9, "Visiting class: " << nodep->name() << " isCovergroup=" << nodep->isCovergroup()
                                    << endl);
        if (nodep->isCovergroup()) {
            VL_RESTORER(m_covergroupp);
            m_covergroupp = nodep;
            m_sampleFuncp = nullptr;
            m_constructorp = nullptr;
            m_coverpoints.clear();
            m_coverCrosses.clear();

            // Extract and store the clocking event from AstCovergroup node
            // The parser creates this node to preserve the event information
            bool hasUnsupportedEvent = false;
            for (AstNode* itemp = nodep->membersp(); itemp;) {
                AstNode* nextp = itemp->nextp();
                if (AstCovergroup* const cgp = VN_CAST(itemp, Covergroup)) {
                    // Store the event in the global map for V3Active to retrieve later
                    if (cgp->eventp()) {
                        // Check if the clocking event references a member variable (unsupported)
                        // Clocking events should be on signals/nets, not class members
                        bool eventUnsupported = false;
                        for (AstNode* senp = cgp->eventp()->sensesp(); senp;
                             senp = senp->nextp()) {
                            if (AstSenItem* const senItemp = VN_CAST(senp, SenItem)) {
                                if (AstVarRef* const varrefp
                                    = VN_CAST(senItemp->sensp(), VarRef)) {
                                    if (varrefp->varp() && varrefp->varp()->isClassMember()) {
                                        cgp->v3warn(COVERIGN, "Ignoring unsupported: covergroup "
                                                              "clocking event on member variable");
                                        eventUnsupported = true;
                                        hasUnsupportedEvent = true;
                                        break;
                                    }
                                }
                            }
                        }

                        if (!eventUnsupported) {
                            // Leave cgp in the class membersp so the SenTree stays
                            // linked in the AST. V3Active will find it via membersp,
                            // use the event, then delete the AstCovergroup itself.
                            UINFO(4, "Keeping covergroup event node for V3Active: "
                                         << nodep->name() << endl);
                            itemp = nextp;
                            continue;
                        }
                    }
                    // Remove the AstCovergroup node - either unsupported event or no event
                    cgp->unlinkFrBack();
                    VL_DO_DANGLING(cgp->deleteTree(), cgp);
                }
                itemp = nextp;
            }

            // If covergroup has unsupported clocking event, skip processing it
            if (hasUnsupportedEvent) return;

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
        // Cross coverage is not yet supported in this PR (deferred to PR-5)
        // Silently delete cross nodes; cross is implemented in a later PR
        VL_DO_DANGLING(nodep->unlinkFrBack()->deleteTree(), nodep);
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
    UINFO(4, __FUNCTION__ << ": " << endl);
    { FunctionalCoverageVisitor{nodep}; }  // Destruct before checking
    V3Global::dumpCheckGlobalTree("coveragefunc", 0, dumpTreeEitherLevel() >= 3);
}
