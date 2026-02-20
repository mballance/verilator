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
// V3CoverageFunctional.cpp -- Functional coverage (covergroup) transformation
//
// This pass transforms covergroup AST nodes into C++ class implementations.
// Currently a stub: accepts covergroup syntax and removes the AST nodes so
// downstream passes do not see them.
//
//*************************************************************************

#include "config_build.h"
#ifndef VERILATOR_V3COVERAGEFUNCTIONAL_H_
#include "V3CoverageFunctional.h"
#endif

#include "V3Ast.h"
#include "V3AstNodeFuncCov.h"
#include "V3Global.h"

VL_DEFINE_DEBUG_FUNCTIONS;

//######################################################################
// Stub visitor: removes covergroup AST nodes so downstream passes are clean

class FunctionalCoverageVisitor final : public VNVisitor {
    void visit(AstClass* nodep) override {
        if (!nodep->isCovergroup()) {
            iterateChildren(nodep);
            return;
        }
        // Remove all funccov-specific children to avoid crashes in downstream passes.
        // Code generation is not yet implemented in this PR.
        AstNode* nextp;
        for (AstNode* childp = nodep->membersp(); childp; childp = nextp) {
            nextp = childp->nextp();
            if (VN_IS(childp, Coverpoint) || VN_IS(childp, CoverCross) || VN_IS(childp, Covergroup)
                || VN_IS(childp, CgOptionAssign)) {
                VL_DO_DANGLING(childp->unlinkFrBack()->deleteTree(), childp);
            }
        }
    }
    void visit(AstNode* nodep) override { iterateChildren(nodep); }

public:
    explicit FunctionalCoverageVisitor(AstNetlist* nodep) { iterate(nodep); }
};

//######################################################################
// V3CoverageFunctional static entry point

void V3CoverageFunctional::coverageFunctional(AstNetlist* nodep) {
    UINFO(2, __FUNCTION__ << ": " << endl);
    { FunctionalCoverageVisitor{nodep}; }
    V3Global::dumpCheckGlobalTree("coverage_functional", 0, dumpTreeEitherLevel() >= 3);
}
