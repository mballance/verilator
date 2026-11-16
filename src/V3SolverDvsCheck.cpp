// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: dv-solve constraint solver back-end: support check
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
// V3SolverDvsCheck's Transformations:
//
// Checks that the constraints of a randomize site are within what
// V3SolverDvsBuild maps to a dv-solve problem, before it builds one, and
// reports each construct that is not as 'Unsupported: ... with
// --solver-dvs'. There is no fallback to another solver (design D2).
//
// Supported: random variables of this object (or its base classes) that are
// integral scalars (including enums and packed structs) of 1 to 64 bits, or
// wider ones read through bit selects at constant positions (packed struct
// members) and in 'solve before', or fixed-size unpacked arrays of them read
// element by element, at any index, or reduced (sum etc., with or without
// 'with', and as 'inside' set members); dynamic arrays and queues of them, or
// of unpacked structs whose rand members are such scalars (read as 'q[i].m',
// and in 'solve before'), and associative arrays of them with integral keys
// (read 'a[k]' at a key read before the call), read the same ways or as a
// whole in 'unique' and 'solve before', with size() a state value in a
// 'foreach' over them, and their size() (solved before the elements when read
// outside a 'foreach' over them); 'foreach' over fixed-size arrays and vectors
// and over one dimension of a dynamic array or queue; operands that do not
// depend on a random variable, whatever they are, when they are integral and
// at most 64 bits, and arrays of them as 'inside' set members; in a 'foreach'
// over one, the integral members of the elements of a dynamic array or queue
// of unpacked structs or class handles that is not random ('q[i].m'); the
// operators of dvsIsMappable(); 'if' constraints and implications; soft
// constraints; 'dist', with values and weights read before the call, under
// conditions that read no random variable; 'unique' outside conditions and
// constraint_mode() blocks; 'solve before'. In the part of a class, also
// random variables of other objects reached through rand class handles of this
// object ('s.x', 's.t.x', and elements of their fixed-size arrays), read as
// operands (not in 'dist', 'unique', 'solve before' or reductions); not their
// dynamic arrays and queues. A dynamic array or queue of rand class handles of
// this object is iterated by 'foreach' ('q[i].x', 'q[i] != null'), and its
// size() read. In a site part, the random variables of the object randomized
// are imports: not its dynamic arrays and queues, nor in 'solve before'.
//
//*************************************************************************

#include "V3PchAstNoMT.h"  // VL_MT_DISABLED_CODE_UNIT

#ifdef HAVE_DV_SOLVE

#include "V3SolverDvsBuild.h"

#include <set>

namespace {

// Most loop levels one dv-solve expression binds (DVS_MAX_LOOP_LEVELS)
static constexpr uint32_t DVS_MAX_LEVELS = 8;

// A problem array: a dynamic array or queue, or an associative array (its elements in key
// order, and their keys)
bool isDynArray(const AstNodeDType* dtypep) {
    dtypep = dtypep->skipRefp();
    return VN_IS(dtypep, DynArrayDType) || VN_IS(dtypep, QueueDType)
           || VN_IS(dtypep, AssocArrayDType);
}

class DvsCheckVisitor final : public VNVisitorConst {
    // NODE STATE
    //  AstNodeExpr::user1()   -> bool. Depends on a random variable (RandomizeMarkVisitor),
    //                                  or on the 'item' of a reduction (markItem())

    // STATE
    const bool m_part;  // Checking the part of a class: imports are supported
    const bool m_inlinePart;  // Checking a site part: this object's variables are imports
    bool m_supported = true;  // No unsupported construct found
    bool m_conditional = false;  // In a conditional constraint or a constraint_mode() block
    bool m_randCondition = false;  // In a constraint whose condition depends on a random variable
    bool m_soft = false;  // In a 'soft foreach'
    std::set<const AstVar*> m_loopVars;  // Loop variables of 'foreach' over dynamic arrays
    uint32_t m_levels = 0;  // Loop levels over dynamic arrays bound
    bool m_slotForeach = false;  // In a 'foreach' over an array of class handles
    bool m_dynItem = false;  // In the 'with' of a reduction over a dynamic array

    // METHODS
    void unsupported(const AstNode* nodep, const std::string& what) {
        m_supported = false;
        nodep->v3error("Unsupported: " << what << " with --solver-dvs");
    }
    void checkRandVar(const AstNode* refp, const AstVar* varp) {
        if (m_inlinePart && VN_IS(refp, VarRef) && isDynArray(varp->dtypep())) {
            unsupported(refp, "dynamic array or queue in randomize() with {...} on a class with"
                              " rand class handles, or extended with constraints");
            return;
        }
        const std::string why = dvsRandVarUnsupported(varp);
        if (!why.empty()) unsupported(refp, why);
    }
    // A random variable or an element of a random array: its variable, else nullptr
    static const AstVarRef* randRefp(const AstNode* nodep) {
        while (const AstArraySel* const selp = VN_CAST(nodep, ArraySel)) nodep = selp->fromp();
        const AstVarRef* const refp = VN_CAST(nodep, VarRef);
        return refp && refp->varp()->rand().isRandomizable() ? refp : nullptr;
    }
    // Why selp, a random variable of another object, is not an import
    static std::string otherObject(const AstMemberRef* selp) {
        const AstNodeExpr* const fromp = selp->fromp();
        if (VN_IS(fromp, ArraySel) || VN_IS(fromp, AssocSel) || VN_IS(fromp, CMethodHard)) {
            return "random variable of an object in an array of class handles in a constraint";
        }
        return "random variable of another object in a constraint";
    }
    // nodep, a random variable or an element of a random array, read in a constraint; an
    // unpacked array if whole; wider than 64 bits if words (of its 32-bit words)
    void checkRandElement(const AstNodeExpr* nodep, bool whole = false, bool words = false) {
        const AstNode* basep = nodep;
        while (const AstArraySel* const selp = VN_CAST(basep, ArraySel)) basep = selp->fromp();
        const AstMemberRef* const importp = VN_CAST(basep, MemberRef);
        const bool isImport = importp && m_part && dvsIsSlotPath(importp->fromp());
        if (importp && !isImport) {
            unsupported(nodep, otherObject(importp));
            return;
        }
        if (isImport && isDynArray(importp->dtypep())) {
            unsupported(nodep, "dynamic array or queue of another object in a constraint");
            return;
        }
        if (!whole && VN_IS(nodep->dtypep()->skipRefp(), UnpackArrayDType)) {
            unsupported(nodep, "unpacked array as a whole in a constraint");
        }
        if (!whole && isDynArray(nodep->dtypep())) {
            unsupported(nodep, "dynamic array or queue as a whole in a constraint");
        }
        if (!words && elementWidth(nodep) > VL_QUADSIZE) {
            unsupported(nodep, "random variable wider than 64 bits");
        }
        if (isImport) {
            checkRandVar(importp, importp->varp());
            return;
        }
        const AstVarRef* const refp = randRefp(nodep);
        if (!refp) {
            unsupported(nodep, "array select of an array that is not a random variable of this"
                               " object");
            return;
        }
        checkRandVar(refp, refp->varp());
    }
    // A random variable or an element of a random array, alone; or an unpacked array of them
    // if whole
    void checkRandVarRef(const AstNode* nodep, const std::string& what, bool whole = false,
                         bool words = false) {
        if (!randRefp(nodep)) {
            unsupported(nodep, what + " of an expression");
            return;
        }
        checkRandElement(VN_AS(nodep, NodeExpr), whole, words);
    }
    static int elementWidth(const AstNode* nodep) {
        const AstNodeDType* dtypep = nodep->dtypep()->skipRefp();
        if (isDynArray(dtypep)) return dtypep->subDTypep()->width();
        while (const AstUnpackArrayDType* const adtypep = VN_CAST(dtypep, UnpackArrayDType)) {
            dtypep = adtypep->subDTypep()->skipRefp();
        }
        return dtypep->width();
    }
    // Marks the nodes of a reduction's 'with' expression that depend on its 'item', which is
    // an element of a random array; returns if nodep does
    static bool markItem(AstNodeExpr* nodep) {
        const AstLambdaArgRef* const refp = VN_CAST(nodep, LambdaArgRef);
        bool dependent = nodep->user1() || (refp && !refp->index());
        for (AstNode* const opp : {nodep->op1p(), nodep->op2p(), nodep->op3p(), nodep->op4p()}) {
            AstNodeExpr* const exprp = VN_CAST(opp, NodeExpr);
            if (exprp && markItem(exprp)) dependent = true;
        }
        nodep->user1(dependent);
        return dependent;
    }
    void checkReduction(AstCMethodHard* nodep) {
        const AstNodeDType* const dtypep = nodep->fromp()->dtypep()->skipRefp();
        const bool dyn = isDynArray(dtypep);
        if (!VN_IS(dtypep, UnpackArrayDType) && !dyn) {
            unsupported(nodep, "array reduction over " + dtypep->prettyDTypeNameQ());
            return;
        }
        checkRandVarRef(nodep->fromp(), "array reduction", true);
        if (dyn && !checkLevel(nodep)) return;
        VL_RESTORER(m_levels);
        VL_RESTORER(m_dynItem);
        if (dyn) {
            ++m_levels;
            m_dynItem = true;
        }
        if (AstWith* const withp = nodep->withp()) {
            markItem(VN_AS(withp->exprp(), NodeExpr));
            iterateConst(withp->exprp());
        }
    }
    // 'x inside {arr}', folded over the elements of arr (V3SolverDvsBuild inside())
    void checkInside(AstCMethodHard* nodep) {
        AstNodeExpr* const fromp = nodep->fromp();
        const AstNodeDType* const elemDTypep = fromp->dtypep()->skipRefp()->subDTypep();
        if (!elemDTypep->skipRefp()->isIntegralOrPacked()) {
            unsupported(nodep, "'inside' over " + fromp->dtypep()->skipRefp()->prettyDTypeNameQ());
            return;
        }
        if (fromp->user1()) {
            checkRandVarRef(fromp, "'inside' set member", true);
        } else if (readsLoopIndex(fromp)) {
            unsupported(fromp, "'inside' array at the index of a 'foreach' over a dynamic array");
            return;
        }
        if (isDynArray(fromp->dtypep()) && !checkLevel(nodep)) return;
        iterateConst(nodep->pinsp());
    }
    bool checkLevel(const AstNode* nodep) {
        if (m_levels < DVS_MAX_LEVELS) return true;
        unsupported(nodep, "more than " + std::to_string(DVS_MAX_LEVELS)
                               + " nested loops over dynamic arrays");
        return false;
    }
    // An element of a dynamic array or queue: random, of this object, or read before the call
    void checkElement(AstCMethodHard* nodep) {
        AstNodeExpr* const fromp = nodep->fromp();
        const AstVarRef* const refp = VN_CAST(fromp, VarRef);
        if (refp && refp->varp()->rand().isRandomizable()) {
            checkRandVar(refp, refp->varp());
        } else if (fromp->user1()) {
            iterateConst(fromp);  // E.g. an element of a random array of arrays
        }
        iterateConst(nodep->pinsp());
    }
    // A member of a struct, read in a constraint: a rand member of the elements of a random
    // dynamic array or queue of unpacked structs ('q[i].m'), or an integral member of one that
    // is not random, at the index of a 'foreach' over a dynamic array
    void checkField(AstStructSel* nodep) {
        AstCMethodHard* const atp = VN_CAST(nodep->fromp(), CMethodHard);
        const AstVarRef* const refp = atp ? VN_CAST(atp->fromp(), VarRef) : nullptr;
        bool isField = false;
        if (refp && atp->method() == VCMethod::ARRAY_AT && isDynArray(refp->dtypep())) {
            for (const AstMemberDType* const memberp :
                 dvsStructFields(refp->dtypep()->skipRefp()->subDTypep(),
                                 refp->varp()->rand().isRandomizable())) {
                isField = isField || memberp->name() == nodep->name();
            }
        }
        if (!isField) {
            unsupported(nodep, "member of a struct other than a rand member of an element of a"
                               " random dynamic array or queue, or an integral one of a"
                               " dynamic array or queue that is not random");
            return;
        }
        checkElement(atp);
    }
    // A member of an object, at the index of a 'foreach' over a dynamic array: an integral
    // member of an element of a dynamic array or queue of class handles that is not random
    // ('q[i].m')
    void checkHandleMember(AstMemberRef* nodep) {
        AstCMethodHard* const atp = VN_CAST(nodep->fromp(), CMethodHard);
        const AstVarRef* const refp = atp ? VN_CAST(atp->fromp(), VarRef) : nullptr;
        const AstNodeDType* const dtypep = nodep->dtypep()->skipRefp();
        if (!refp || atp->method() != VCMethod::ARRAY_AT || !isDynArray(refp->dtypep())
            || !dtypep->isIntegralOrPacked() || dtypep->width() > VL_QUADSIZE) {
            unsupported(nodep, "member of an object other than an integral one of an element of"
                               " a dynamic array or queue of class handles");
            return;
        }
        checkElement(atp);
    }
    // Whether nodep reads the index of a loop over a dynamic array, so is built over it
    bool readsLoopIndex(const AstNodeExpr* nodep) const {
        return nodep->exists([&](const AstNode* np) {
            if (const AstVarRef* const refp = VN_CAST(np, VarRef)) {
                return m_loopVars.count(refp->varp()) != 0;
            }
            const AstLambdaArgRef* const argp = VN_CAST(np, LambdaArgRef);
            return argp && argp->index() && m_dynItem;
        });
    }
    void checkDist(AstDist* distp) {
        if (m_slotForeach) {
            unsupported(distp, "'dist' in a 'foreach' over an array of class handles");
            return;
        }
        if (m_soft) {
            unsupported(distp, "'dist' in a 'soft foreach'");
            return;
        }
        if (m_randCondition) {
            unsupported(distp, "'dist' under a condition that depends on a random variable");
            return;
        }
        const AstNode* targetp = distp->exprp();
        if (const AstNodeUniop* const extp = VN_CAST(targetp, NodeUniop)) targetp = extp->lhsp();
        AstCMethodHard* const atp = VN_CAST(const_cast<AstNode*>(targetp), CMethodHard);
        if (atp && atp->method() == VCMethod::ARRAY_AT && atp->fromp()->user1()) {
            // dv-solve draws an element of an array in a foreach over it
            if (!m_levels) {
                unsupported(distp, "'dist' on an element of a dynamic array outside a"
                                   " 'foreach' over a dynamic array");
                return;
            }
            checkElement(atp);
        } else if (m_levels) {
            unsupported(distp, "'dist' on a variable in a 'foreach' over a dynamic array");
            return;
        } else {
            checkRandVarRef(targetp, "'dist'");
        }
        // Values and weights are read before the call (dv-solve evaluates them per call)
        for (AstDistItem* itemp = distp->itemsp(); itemp;
             itemp = VN_AS(itemp->nextp(), DistItem)) {
            AstInsideRange* const rangep = VN_CAST(itemp->rangep(), InsideRange);
            for (AstNodeExpr* const operandp :
                 {itemp->weightp(), rangep ? rangep->lhsp() : itemp->rangep(),
                  rangep ? rangep->rhsp() : nullptr}) {
                if (!operandp) continue;
                if (operandp->user1()) {
                    unsupported(operandp,
                                "'dist' with a value or weight that depends on a random variable");
                } else {
                    iterateConst(operandp);
                }
            }
        }
    }

    // VISITORS - constraint items
    void visit(AstConstraintExpr* nodep) override {
        if (nodep->isDisableSoft()) {
            unsupported(nodep, "'disable soft'");
        } else if (AstDist* const distp = VN_CAST(nodep->exprp(), Dist)) {
            checkDist(distp);
        } else {
            iterateConst(nodep->exprp());
        }
    }
    void visit(AstConstraintIf* nodep) override {
        iterateConst(nodep->condp());
        VL_RESTORER(m_conditional);
        VL_RESTORER(m_randCondition);
        m_conditional = true;
        m_randCondition = m_randCondition || nodep->condp()->user1();
        iterateAndNextConstNull(nodep->thensp());
        iterateAndNextConstNull(nodep->elsesp());
    }
    void visit(AstConstraintUnique* nodep) override {
        if (m_levels) {
            unsupported(nodep, "'unique' in a 'foreach' over a dynamic array");
            return;
        }
        if (m_conditional) {
            unsupported(nodep, "'unique' in a conditional constraint or a block with"
                               " constraint_mode()");
            return;
        }
        for (const AstNode* itemp = nodep->rangesp(); itemp; itemp = itemp->nextp()) {
            checkRandVarRef(itemp, "'unique'", true);
            if (elementWidth(itemp) != elementWidth(nodep->rangesp())) {
                unsupported(itemp, "'unique' of variables of different widths");
            }
        }
    }
    void visit(AstConstraintBefore* nodep) override {
        if (m_inlinePart) {
            unsupported(nodep, "'solve before' in randomize() with {...} on a class with rand"
                               " class handles, or extended with constraints");
            return;
        }
        for (AstNode* const listp : {nodep->lhssp(), nodep->rhssp()}) {
            for (AstNode* itemp = listp; itemp; itemp = itemp->nextp()) {
                if (AstStructSel* const selp = VN_CAST(itemp, StructSel)) {
                    checkField(selp);  // All the elements' member
                } else {
                    checkRandVarRef(itemp, "'solve before'", true, true);
                }
            }
        }
    }
    void visit(AstConstraintForeach* nodep) override {
        AstNodeExpr* const fromp = nodep->headerp()->fromp();
        if (isDynArray(fromp->dtypep())) {
            // One loop variable, the index of a dynamic array or queue of scalars
            AstVar* const varp = VN_CAST(nodep->headerp()->elementsp(), Var);
            if (!varp || varp->nextp()) {
                unsupported(nodep, "'foreach' over more than one dimension of "
                                       + fromp->dtypep()->skipRefp()->prettyDTypeNameQ());
                return;
            }
            const AstVarRef* const refp = VN_CAST(fromp, VarRef);
            const bool rand = refp && refp->varp()->rand().isRandomizable();
            // An array of class handles of this object is a slot array: its handles' objects
            const bool slots = rand && dvsIsSlotArray(fromp->dtypep());
            const AstMemberRef* const importp = VN_CAST(fromp, MemberRef);
            if (rand) {
                if (!slots) checkRandVar(refp, refp->varp());
            } else if (importp && importp->varp()->rand().isRandomizable()
                       && dvsIsSlotPath(importp->fromp())) {
                // Its size is solved with its object. Not user1(): V3Randomize marks the
                // expressions of constraints, not 'foreach' headers.
                unsupported(nodep, "dynamic array or queue of another object in a constraint");
            } else if ((elementWidth(fromp) > VL_QUADSIZE
                        || !fromp->dtypep()
                                ->skipRefp()
                                ->subDTypep()
                                ->skipRefp()
                                ->isIntegralOrPacked())
                       && dvsStructFields(fromp->dtypep()->skipRefp()->subDTypep(), false).empty()
                       // Of class handles: their members read
                       && !VN_IS(fromp->dtypep()->skipRefp()->subDTypep()->skipRefp(),
                                 ClassRefDType)) {
                unsupported(nodep,
                            "'foreach' over " + fromp->dtypep()->skipRefp()->prettyDTypeNameQ());
            }
            // Of class handles that are not random: an array per member read, one at least
            if (!rand && VN_IS(fromp->dtypep()->skipRefp()->subDTypep()->skipRefp(), ClassRefDType)
                && (!refp || !nodep->bodyp()
                    || !nodep->bodyp()->existsAndNext([&](const AstMemberRef* selp) {
                           const AstCMethodHard* const atp = VN_CAST(selp->fromp(), CMethodHard);
                           const AstVarRef* const atRefp
                               = atp ? VN_CAST(atp->fromp(), VarRef) : nullptr;
                           return atRefp && atRefp->varp() == refp->varp();
                       }))) {
                unsupported(nodep, "'foreach' over a dynamic array or queue of class handles"
                                   " that is not random, other than a variable of this object"
                                   " whose elements' members it reads");
            }
            if (!checkLevel(nodep)) return;
            VL_RESTORER(m_levels);
            VL_RESTORER(m_soft);
            VL_RESTORER(m_slotForeach);
            ++m_levels;
            m_soft = m_soft || nodep->isSoft();
            m_slotForeach = m_slotForeach || slots;
            m_loopVars.insert(varp);
            iterateAndNextConstNull(nodep->bodyp());
            m_loopVars.erase(varp);
            return;
        }
        // Each loop variable iterates a dimension of a fixed-size array, or the bits of a
        // vector (the last dimension, V3Width checked)
        const AstNodeDType* dtypep = nodep->headerp()->fromp()->dtypep();
        for (const AstNode* elemp = nodep->headerp()->elementsp(); elemp; elemp = elemp->nextp()) {
            const AstNodeDType* const skipp = dtypep->skipRefp();
            const AstBasicDType* const basicp = VN_CAST(skipp, BasicDType);
            if (const AstNodeArrayDType* const adtypep = VN_CAST(skipp, NodeArrayDType)) {
                dtypep = adtypep->subDTypep();
            } else if (!basicp || !basicp->isRanged()) {
                unsupported(nodep, "'foreach' over " + skipp->prettyDTypeNameQ());
                return;
            }
        }
        VL_RESTORER(m_soft);
        m_soft = m_soft || nodep->isSoft();
        iterateAndNextConstNull(nodep->bodyp());
    }

    // VISITORS - expressions
    void visit(AstNodeExpr* nodep) override {
        AstCMethodHard* const nullp = dvsSlotNullComparep(nodep);
        if (nullp && VN_IS(nullp->fromp(), VarRef)
            && VN_AS(nullp->fromp(), VarRef)->varp()->rand().isRandomizable()) {
            return;  // An element of a slot array
        }
        if (!nodep->user1() && readsLoopIndex(nodep)) {
            // Built over the loop index, of the operators dvsIsMappable() maps
            if (VN_IS(nodep, VarRef) || VN_IS(nodep, LambdaArgRef)) return;
            if (VN_IS(nodep, ArraySel)) {
                unsupported(nodep, "element of a fixed-size array that is not random at the"
                                   " index of a 'foreach' over a dynamic array");
                return;
            }
            if (AstStructSel* const selp = VN_CAST(nodep, StructSel)) {
                checkField(selp);
                return;
            }
            if (AstMemberRef* const selp = VN_CAST(nodep, MemberRef)) {
                checkHandleMember(selp);
                return;
            }
            if (!dvsIsMappable(nodep)) {
                unsupported(nodep, nodep->prettyOperatorName()
                                       + " of the index of a 'foreach' over a dynamic array");
                return;
            }
            if (nodep->width() > VL_QUADSIZE) {
                unsupported(nodep, "operand wider than 64 bits in a constraint");
                return;
            }
            AstCMethodHard* const callp = VN_CAST(nodep, CMethodHard);
            if (callp && callp->method() == VCMethod::ARRAY_AT
                && VN_IS(callp->dtypep()->skipRefp(), ClassRefDType)) {
                unsupported(nodep, "class handle in a dynamic array or queue that is not random,"
                                   " other than read through a member");
            } else if (callp && callp->method() == VCMethod::ARRAY_AT) {
                checkElement(callp);
            } else if (callp && callp->method() == VCMethod::ARRAY_INSIDE) {
                checkInside(callp);
            } else if (callp) {
                checkReduction(callp);
            } else {
                iterateChildrenConst(nodep);
            }
            return;
        }
        if (!nodep->user1()) {
            // Evaluated before the call, as a STATE variable or a constant
            const AstConst* const constp = VN_CAST(nodep, Const);
            // The operators of dvsIsMappable() take integral operands only
            if (constp && constp->num().isFourState()) {
                unsupported(nodep, "constant with X or Z bits in a constraint");
            } else if (nodep->width() > VL_QUADSIZE) {
                unsupported(nodep, "operand wider than 64 bits in a constraint");
            }
            return;
        }
        if (VN_IS(nodep, VarRef) || VN_IS(nodep, ArraySel) || VN_IS(nodep, MemberRef)) {
            checkRandElement(nodep);
            return;
        }
        if (AstAssocSel* const selp = VN_CAST(nodep, AssocSel)) {
            // An element of a random associative array, at a key read before the call or the
            // key of a 'foreach' over an associative array
            const AstVarRef* const refp = VN_CAST(selp->fromp(), VarRef);
            if (!refp || !refp->varp()->rand().isRandomizable()) {
                unsupported(nodep, "associative array that is not a random variable of this"
                                   " object");
            } else if (selp->bitp()->user1()) {
                unsupported(nodep, "associative array key that depends on a random variable");
            } else {
                checkRandVar(refp, refp->varp());
                iterateConst(selp->bitp());
            }
            return;
        }
        if (AstStructSel* const selp = VN_CAST(nodep, StructSel)) {
            checkField(selp);
            return;
        }
        if (!dvsIsMappable(nodep)) {
            unsupported(nodep, nodep->prettyOperatorName() + " on random variables");
            return;
        }
        if (nodep->width() > VL_QUADSIZE) {
            unsupported(nodep, "expression wider than 64 bits on random variables");
            return;
        }
        if (AstCMethodHard* const callp = VN_CAST(nodep, CMethodHard)) {
            if (callp->method() == VCMethod::ARRAY_AT) {
                checkElement(callp);
            } else if (callp->method() == VCMethod::DYN_SIZE) {
                // A state value in a 'foreach' over the array (IEEE 1800-2023 18.5.8.1);
                // elsewhere a constraint on the size, solved before the elements
                const AstVarRef* const refp = VN_CAST(callp->fromp(), VarRef);
                if (!refp || !refp->varp()->rand().isRandomizable()) {
                    iterateConst(callp->fromp());  // E.g. the result of find()
                } else if (!dvsIsSlotArray(refp->varp()->dtypep())) {
                    checkRandVar(refp, refp->varp());
                }
            } else if (callp->method() == VCMethod::ARRAY_INSIDE) {
                checkInside(callp);
            } else {
                checkReduction(callp);
            }
            return;
        }
        if (const AstSel* const selp = VN_CAST(nodep, Sel)) {
            if (selp->lsbp()->user1()) {
                unsupported(nodep, "bit select at a non-constant position of a random value");
                return;
            }
            const AstNodeExpr* const fromp = selp->fromp();
            if (fromp->width() > VL_QUADSIZE
                && (VN_IS(fromp, VarRef) || VN_IS(fromp, ArraySel) || VN_IS(fromp, MemberRef))) {
                checkRandElement(fromp, false, true);
                return;
            }
        }
        iterateChildrenConst(nodep);
    }
    void visit(AstNode* nodep) override {  // LCOV_EXCL_START
        nodep->v3fatalSrc("Unexpected constraint item");
    }  // LCOV_EXCL_STOP

public:
    // CONSTRUCTORS
    explicit DvsCheckVisitor(const DvsSite& site)
        : m_part{site.part}
        , m_inlinePart{site.inlinePart} {
        for (const DvsSite::Block& block : site.blocks) {
            VL_RESTORER(m_conditional);
            m_conditional = block.modeVarp;
            iterateAndNextConstNull(block.itemsp);
        }
    }
    ~DvsCheckVisitor() override = default;
    bool supported() const { return m_supported; }
};

}  // namespace

bool dvsSiteSupported(const DvsSite& site) { return DvsCheckVisitor{site}.supported(); }

#endif  // HAVE_DV_SOLVE
