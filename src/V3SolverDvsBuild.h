// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: dv-solve constraint solver back-end: problem builder
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
// Internal interface of the dv-solve back-end (V3SolverDvs*.cpp). Only
// included when Verilator is configured --with-dv-solve.
//
//*************************************************************************

#ifndef VERILATOR_V3SOLVERDVSBUILD_H_
#define VERILATOR_V3SOLVERDVSBUILD_H_

#include "config_build.h"
#include "verilatedos.h"

#include "V3Ast.h"

#include <vector>

//######################################################################
// The constraints of one randomize site

struct DvsSite final {
    // A block of constraint items, enabled by a constraint_mode() bit if modeVarp is set
    struct Block final {
        AstNode* itemsp;  // First constraint item (not owned)
        AstVar* modeVarp;  // constraint_mode() array, or nullptr if always enabled
        uint32_t modeIndex;  // Index of the block's bit in modeVarp
    };
    AstClass* classp;  // Class randomized
    FileLine* flp;  // Location of the site, for UNSATCONSTR
    std::vector<Block> blocks;  // Class constraint blocks, base class first, then inline items
    bool checkOnly;  // randomize(null): check the current values, solve nothing
    bool part = false;  // The part of the class, see V3SolverDvs.cpp: exports, slots, imports
    // With part, the site part of a randomize() with {...}: only imports, through slot 0, the
    // object randomized, of class classp; no exports
    bool inlinePart = false;
    // A std::randomize() with {...} site, of no class (classp is nullptr): the module's
    // generator, which seeds the solve. Its random variables are the arguments.
    AstVar* stdrandp = nullptr;

    bool hasItems() const {
        for (const Block& block : blocks) {
            if (block.itemsp) return true;
        }
        return false;
    }
};

// The value of nodep, if it is a constant expression, as a new node; else nullptr
AstConst* dvsNewConstp(AstNodeExpr* nodep) VL_MT_DISABLED;

// Why the builder cannot solve random variable varp, or "" if it can
std::string dvsRandVarUnsupported(const AstVar* varp) VL_MT_DISABLED;

// The members of unpacked struct dtypep that the elements of a dynamic array or queue of it
// have a problem array for, in order: the rand members of a random one, else the integral
// members of at most 64 bits; empty if not an unpacked struct
std::vector<const AstMemberDType*> dvsStructFields(const AstNodeDType* dtypep,
                                                   bool rand) VL_MT_DISABLED;

// True if the builder can map nodep, a constraint expression, to a dv-solve operator
bool dvsIsMappable(const AstNodeExpr* nodep) VL_MT_DISABLED;

// Report the first construct of the site the builder does not support, and return false; or
// return true if all are supported (V3SolverDvsCheck.cpp)
bool dvsSiteSupported(const DvsSite& site) VL_MT_DISABLED;

// The class of a class handle of dtypep, or of the elements of a fixed-size unpacked array, a
// dynamic array or a queue of them; else nullptr
AstClass* dvsHandleClassp(const AstNodeDType* dtypep) VL_MT_DISABLED;

// True if dtypep is a dynamic array or queue of class handles: a slot array
bool dvsIsSlotArray(const AstNodeDType* dtypep) VL_MT_DISABLED;

// The element of a slot array that nodep compares with null ('a[i] != null', 'a[i] == null'),
// or nullptr
AstCMethodHard* dvsSlotNullComparep(const AstNodeExpr* nodep) VL_MT_DISABLED;

// The slots of the part of classp: its rand class-handle members, each element of its rand
// fixed-size unpacked arrays of them (in storage order), and each of its rand dynamic arrays
// and queues of them (a slot array), base class first, in declaration order. Returns the
// members.
std::vector<AstVar*> dvsSlots(const AstClass* classp) VL_MT_DISABLED;

// True if nodep is a rand class handle of this object, or a rand class-handle member of one
// ('s', 's.t'), or an element of such an array ('a[1].t', 'q[i].t'): a slot path of the part
// of this object's class
bool dvsIsSlotPath(const AstNodeExpr* nodep) VL_MT_DISABLED;

// Build the dv-solve problem of the site, adding the statements it needs to funcp, and
// return the solver call; or report an unsupported construct and return nullptr.
// If ownVars, mark the random variables solved as owned by the solver (AstVar::user3()).
AstNodeExpr* dvsNewSolveCallp(const DvsSite& site, AstNodeFTask* funcp,
                              bool ownVars) VL_MT_DISABLED;

// Build the part of the site's class (site.part), adding the statements that evaluate its
// state values to funcp (its __Vdvs_part method, or for a site part the randomize() with
// {...} function), and return the call that registers it; or report an unsupported construct
// and return nullptr. If ownVars, as dvsNewSolveCallp, for the variables its constraints
// name.
AstNodeExpr* dvsNewPartCallp(const DvsSite& site, AstNodeFTask* funcp,
                             bool ownVars) VL_MT_DISABLED;

#endif  // Guard
