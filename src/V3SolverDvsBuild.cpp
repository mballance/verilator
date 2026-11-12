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
// V3SolverDvsBuild's Transformations:
//
// Builds the dv-solve problem of one randomize site with the dv-solve writer
// library, after V3SolverDvsCheck has accepted the site, and emits the call
// that solves it (see V3SolverDvs.cpp).
//
// The problem is EXPLICIT: V3Width has fixed every width and signedness, so
// each Verilator operator maps to one dv-solve operator over operands that
// already have its width. dv-solve takes the signedness of an operator from
// its operands, so the builder tracks the signedness of each expression it
// builds, and makes the operands of an operator agree: a full-width extract
// reads a signed value as unsigned, and a cast of the same width (dv-solve's
// conversion of an EXPLICIT problem) reads an unsigned value as signed.
//
// Problem variables, numbered in the order they are met:
//  * RAND: a random variable of the site, passed by reference. A random
//    unpacked array is one per element, numbered in storage order, and is
//    passed as one argument. For a randomize(null) site they are STATE
//    instead, so they are checked, not solved.
//  * STATE: each maximal sub-expression that does not depend on a random
//    variable (AstNodeExpr::user1() clear, as marked by the front end), other
//    than a constant expression (folded by V3Const), and the constraint_mode()
//    bit of each block that has one. It is evaluated into a local of the
//    function before the call, and the local is passed by reference. A
//    variable read directly is one STATE variable however often it is read.
//  * The enable of a block is applied as 'en -> c' to each of its items, as
//    are the conditions of 'if' constraints.
//  * A random variable that another site's constraints named is solved at
//    every class site, since __VBasicRand skips it (AstVar::user3()).
//
// 'foreach' is unrolled over the declared indices of the array. While it is,
// a sub-expression that reads a loop variable is built from a copy with the
// loop variables replaced by their values, so element indices are constants.
// An element at an index out of range reads 0, as an out-of-range read does
// (IEEE 1800-2023 7.4.6), so 'i > 0 -> a[i] > a[i - 1]' needs no special case.
// An index that is not a constant (random, or read before the call) selects
// with a choice over the elements, 0 if none matches.
//
// An array reduction (sum, product, and, or, xor) folds the elements of a
// random array, or the 'with' expression built once per element, with 'item'
// the element and 'item.index' its index (IEEE 1800-2023 7.12.3). An array
// in an 'inside' set is the OR reduction of 'item == x' (11.4.13); a fixed-size
// one read before the call is one STATE variable per element.
//
// A dynamic array or queue is a problem array: its size is given on each
// call, so its constraints are written once, over a loop index, and dv-solve
// instantiates them for the sizes of the call. A 'foreach' over it is a
// dv-solve foreach, an element is an element at an index expression, and a
// reduction over it a dv-solve reduction. Within a 'foreach' over it, its
// size() is a state value (IEEE 1800-2023 18.5.8.1); read anywhere else, its
// size is random, and dv-solve solves it, with the constraints that read no
// element, before the elements. An array whose size is not constrained is not
// resized (18.4). A random one is passed by reference; any other is copied
// into a local before the call.
//
// The part of a class (DvsSite::part) is the problem of its own constraint
// blocks, for a solve across objects (IEEE 1800-2023 18.5.8):
//  * Its slots are its rand class-handle members, an array of them one per
//    element (dvsSlots). An element is selected by a constant or a 'foreach'
//    index, so a path names one slot. A dynamic array or queue of them is one
//    slot, a dv-solve slot array: a 'foreach' over it is instantiated by
//    dv-solve once per element of the call, an import through its element
//    names the element by a constant or the loop level, 'q[i] != null' is the
//    element's bit, and its size() a size (random outside a 'foreach' over it).
//    A site part iterates the object's array through a mirror, a slot array of
//    its own passed the same queue.
//  * Its exports are its random variables (each element of an unpacked
//    array), in the class's layout: the base class's layout, then the class's
//    own members in declaration order, so the layout of a class is a prefix
//    of that of a class derived from it. Dynamic arrays, and variables the
//    builder cannot solve, are not in the layout.
//  * A random variable of an object reached through rand handles ('s.t.x')
//    is an import: a problem variable bound to the slot path and to the index
//    of the variable in the layout of the declared class of the last handle.
//  * Its STATE values are evaluated into members of the class rather than
//    locals, as the part is registered by its __Vdvs_part method and solved
//    after it returns (VL_DVS_PART, verilated_solver_dvs.h). A comparison of
//    handles ('s != null') is a STATE value, so a guard of a read through a
//    null handle is one dv-solve sees.
//
// The constraint-information array holds the site's location, then the
// location and source text of each hard constraint, in the order they are
// added to the problem (the order of the image's ConstraintSpec list, those
// in the body of a dv-solve foreach left out), which is how a future dv-solve
// unsat-core API would report them.
//
//*************************************************************************

#include "V3PchAstNoMT.h"  // VL_MT_DISABLED_CODE_UNIT

#ifdef HAVE_DV_SOLVE

#include "V3Const.h"
#include "V3ConstPool.h"
#include "V3File.h"
#include "V3SolverBackend.h"
#include "V3SolverDvsBuild.h"

#include <map>
#include <set>

#include <dv_solve/dvs_writer.h>

namespace {

// Most soft constraints dv-solve solves: its active set is a 64-bit mask
static constexpr size_t DVS_MAX_SOFTS = 64;
// Priority of the first soft constraint; each later one takes the next lower number, so
// is more important (IEEE 1800-2023 18.5.13; dv-solve's priority 0 is the highest)
static constexpr uint32_t DVS_FIRST_SOFT = 0xFFFFFFFF;
// Most solve-before stages, set_var_order() takes a uint8_t
static constexpr uint32_t DVS_MAX_STAGE = 255;
// Most slots of a part: their states are passed as a 64-bit mask
static constexpr size_t DVS_MAX_SLOTS = 64;
// Variable and array information: the width, and these flags (verilated_solver_dvs.h)
static constexpr uint32_t DVS_INFO_SIGNED = 1U << 31;
static constexpr uint32_t DVS_INFO_IMPORT = 1U << 30;  // An import: no argument
static constexpr uint32_t DVS_INFO_WIDTH = DVS_INFO_IMPORT - 1;

bool isDynArray(const AstNodeDType* dtypep) {
    dtypep = dtypep->skipRefp();
    return VN_IS(dtypep, DynArrayDType) || VN_IS(dtypep, QueueDType);
}
// Whether varp is in the layout of the part of its class (exported)
bool isLayoutVar(const AstVar* varp) {
    return varp->rand().isRandomizable() && !isDynArray(varp->dtypep())
           && dvsRandVarUnsupported(varp).empty();
}

//######################################################################
// The dv-solve problem of one randomize site

class DvsProblemBuilder final {
    // TYPES
    struct Value final {  // An expression built
        dvs_expr_t expr;  // The expression
        uint32_t width;  // Its width
        bool isSigned;  // dv-solve reads it as signed
        bool isBool;  // dv-solve takes it as a condition as is
    };
    struct Arg final {  // A variable passed to the solver: one problem variable per element
        AstVar* varp;  // The variable
        bool local;  // varp is a local of the function, else a member of the class
    };

    // MEMBERS
    const DvsSite& m_site;  // Site being built
    AstNodeFTask* const m_funcp;  // Function the call is in
    bool m_ownVars;  // Mark random variables as owned by the solver
    dvs_builder_t* const m_builderp;  // dv-solve problem builder
    std::vector<Arg> m_args;  // Variables passed, in problem variable order
    std::vector<uint32_t> m_varInfos;  // Width and signedness of each problem variable, by id
    std::map<const AstVar*, uint32_t> m_varIds;  // First problem variable of a variable read
    // First problem variable of an import, by slot path and variable
    std::map<std::pair<std::vector<uint32_t>, const AstVar*>, uint32_t> m_importIds;
    std::map<const AstClass*, std::vector<AstVar*>> m_slots;  // Slots of each class seen
    // Export index of each variable in the layout of each class seen
    std::map<const AstClass*, std::map<const AstVar*, uint32_t>> m_layouts;
    std::map<const AstVar*, int64_t> m_loopValues;  // Value of each foreach loop variable
    std::map<const AstVar*, uint32_t> m_arrayIds;  // Problem array of a dynamic array read
    std::vector<uint32_t> m_arrayInfos;  // Element width and signedness of each array, by id
    std::map<const AstVar*, uint32_t> m_loopLevels;  // Level of each loop variable of a
                                                     // 'foreach' over a dynamic array
    std::set<const AstVar*> m_slotLoopVars;  // Those of a 'foreach' over an array of handles
    std::vector<AstVar*> m_mirrors;  // Site part: the object's arrays of handles iterated
    uint32_t m_levels = 0;  // Loop levels bound
    std::set<uint32_t> m_foreachArrays;  // Arrays of the 'foreach' over dynamic arrays around
    std::set<uint32_t> m_sizedArrays;  // Random arrays whose size() is constrained
    struct EnumVar final {  // A variable, or the elements of an array, of an enum type
        Value value;  // The variable, or the element at loop level 0
        const AstEnumDType* enump;  // Its type
        FileLine* flp;  // Its declaration
        int64_t arrayId;  // The array, or -1
    };
    std::vector<EnumVar> m_enumVars;  // Constrained to their values after all items
    bool m_soft = false;  // In a 'soft foreach': expressions are soft
    const Value* m_itemp = nullptr;  // 'item' of the 'with' expression being built
    int64_t m_itemIndex = 0;  // 'item.index' of the 'with' expression being built
    int64_t m_itemLevel = -1;  // Level of 'item.index' in a reduction over a dynamic array
    std::vector<std::string> m_constraintInfos;  // Site, then location and source per hard
    size_t m_nSofts = 0;  // Soft constraints added
    std::vector<std::pair<uint32_t, uint32_t>> m_befores;  // 'solve first before second'
    bool m_failed = false;  // An unsupported construct was reported

    // METHODS
    void unsupported(AstNode* nodep, const std::string& what) {
        if (m_failed) return;
        m_failed = true;
        nodep->v3error("Unsupported: " << what << " with --solver-dvs");
    }
    static std::string location(FileLine* flp) {
        return VIdProtect::protect(flp->filename()) + ":" + std::to_string(flp->lineno());
    }

    // Problem variables
    uint32_t newVar(uint32_t width, bool isSigned, bool state) {
        const uint32_t id = m_varInfos.size();
        m_varInfos.push_back(width | (isSigned ? DVS_INFO_SIGNED : 0));
        // Full range of the type: a STATE value outside its bounds would be UNSAT
        int64_t lo = 0;
        int64_t hi = -1;  // All ones: 64-bit unsigned
        if (isSigned) {
            hi = static_cast<int64_t>(VL_MASK_Q(width - 1));
            lo = -hi - 1;
        } else if (width < VL_QUADSIZE) {
            hi = static_cast<int64_t>(VL_MASK_Q(width));
        }
        dvs_builder_add_var(m_builderp, id, width, isSigned, lo, hi);
        if (state) dvs_builder_set_var_kind(m_builderp, id, DVS_VAR_STATE);
        return id;
    }
    // First problem variable of random variable varp
    uint32_t randVarId(AstVar* varp) {
        const auto pair = m_varIds.emplace(varp, m_varInfos.size());
        if (!pair.second) return pair.first->second;
        m_args.push_back({varp, false});
        if (m_ownVars) varp->user3(true);
        const AstNodeDType* elemDTypep = varp->dtypep()->skipRefToEnump();
        uint32_t count = 1;
        while (const AstUnpackArrayDType* const adtypep = VN_CAST(elemDTypep, UnpackArrayDType)) {
            count *= adtypep->elementsConst();
            elemDTypep = adtypep->subDTypep()->skipRefToEnump();
        }
        for (uint32_t i = 0; i < count; ++i) {
            const Value var
                = varValue(newVar(elemDTypep->width(), elemDTypep->isSigned(), m_site.checkOnly));
            // Its values are constrained once all items are added, outside any foreach
            if (const AstEnumDType* const enump = VN_CAST(elemDTypep, EnumDType)) {
                m_enumVars.push_back({var, enump, varp->fileline(), -1});
            }
        }
        return pair.first->second;
    }
    // 'var' holds one of the values of enump
    Value enumMember(const Value& var, const AstEnumDType* enump) {
        Value member = falseValue();
        for (const AstEnumItem* itemp = enump->itemsp(); itemp;
             itemp = VN_AS(itemp->nextp(), EnumItem)) {
            const Value value
                = constant(VN_AS(itemp->valuep(), Const)->num(), var.width, var.isSigned);
            member = binary(DVS_BIN_OR, member, binary(DVS_BIN_EQ, var, value, true), true);
        }
        return member;
    }
    static const AstNodeDType* elemDTypep(const AstNodeExpr* arrayp) {
        return arrayp->dtypep()->skipRefp()->subDTypep()->skipRefToEnump();
    }
    // A new problem array of elements of elemDTypep
    uint32_t newArray(const AstNodeDType* elemDTypep, bool rand) {
        const uint32_t id = m_arrayInfos.size();
        m_arrayInfos.push_back(elemDTypep->width()
                               | (elemDTypep->isSigned() ? DVS_INFO_SIGNED : 0));
        dvs_builder_add_array(m_builderp, id, elemDTypep->width(), elemDTypep->isSigned(),
                              rand && !m_site.checkOnly ? DVS_VAR_RAND : DVS_VAR_STATE);
        return id;
    }
    // Problem array of random dynamic array or queue varp
    uint32_t randArrayId(AstVar* varp) {
        const auto it = m_arrayIds.find(varp);
        if (it != m_arrayIds.end()) return it->second;
        const AstNodeDType* const elemDTypep
            = varp->dtypep()->skipRefp()->subDTypep()->skipRefToEnump();
        const uint32_t id = newArray(elemDTypep, true);
        m_arrayIds.emplace(varp, id);
        m_args.push_back({varp, false});
        if (m_ownVars) varp->user3(true);
        if (const AstEnumDType* const enump = VN_CAST(elemDTypep, EnumDType)) {
            m_enumVars.push_back({elemValue(id, loopIndex(0)), enump, varp->fileline(), id});
        }
        return id;
    }
    // Problem array of varp, a dynamic array or queue of class handles of this object: a slot
    // array, at its slot; in a site part, a mirror of the object's, at a slot of its own
    uint32_t slotArrayId(AstVar* varp) {
        const auto it = m_arrayIds.find(varp);
        if (it != m_arrayIds.end()) return it->second;
        const uint32_t id = m_arrayInfos.size();
        m_arrayInfos.push_back(1);
        if (m_site.inlinePart) m_mirrors.push_back(varp);
        dvs_builder_add_slot_array(
            m_builderp, id, m_site.inlinePart ? m_mirrors.size() : slotIndex(m_site.classp, varp));
        m_arrayIds.emplace(varp, id);
        return id;
    }
    // In an import path, the word selecting an element of a slot array at indexp: a constant
    // index, or that of a 'foreach' over an array of handles; false if neither
    bool slotSelector(AstNodeExpr* indexp, uint32_t& word) {
        const AstVarRef* const refp = VN_CAST(indexp, VarRef);
        if (refp && m_slotLoopVars.count(refp->varp())) {
            word = DVS_PATH_LOOP(m_loopLevels.at(refp->varp()));
            return true;
        }
        AstConst* const constp = newBoundConstp(indexp);
        if (!constp) {
            unsupported(indexp, "index of an array of class handles that is not a constant or a"
                                " 'foreach' index");
            return false;
        }
        // An index out of range, negative included, selects a null handle
        word = std::min<uint64_t>(constp->num().toUQuad(), DVS_PATH_LOOP(0) - 1);
        VL_DO_DANGLING(constp->deleteTree(), constp);
        return true;
    }
    // Problem array of arrayp, a dynamic array or queue: a random variable of the site, or
    // any other value, copied into a local before the call
    uint32_t arrayId(AstNodeExpr* arrayp) {
        AstVarRef* const refp = VN_CAST(arrayp, VarRef);
        if (refp && dvsIsSlotArray(refp->varp()->dtypep())) return slotArrayId(refp->varp());
        if (refp && refp->varp()->rand().isRandomizable()) return randArrayId(refp->varp());
        if (refp) {
            const auto it = m_arrayIds.find(refp->varp());
            if (it != m_arrayIds.end()) return it->second;
        }
        const uint32_t id = newArray(elemDTypep(arrayp), false);
        if (refp) m_arrayIds.emplace(refp->varp(), id);
        newTempp(arrayp, "array" + std::to_string(id), arrayp->dtypep());
        return id;
    }
    Value loopIndex(uint32_t level) {
        return {dvs_builder_expr_loop_index(m_builderp, level), 32, true, false};
    }
    // Element of a problem array
    Value elemValue(uint32_t id, const Value& index) {
        return {dvs_builder_expr_elem(m_builderp, id, index.expr),
                m_arrayInfos[id] & DVS_INFO_WIDTH, (m_arrayInfos[id] >> 31) != 0, false};
    }
    // Whether nodep reads the index of a loop over a dynamic array (its loop variable, or
    // 'item.index' of a reduction over one), so cannot be read before the call
    bool readsLoopIndex(AstNodeExpr* nodep) const {
        return nodep->exists([&](const AstNode* np) {
            if (const AstVarRef* const refp = VN_CAST(np, VarRef)) {
                return m_loopLevels.count(refp->varp()) != 0;
            }
            const AstLambdaArgRef* const argp = VN_CAST(np, LambdaArgRef);
            return argp && argp->index() && m_itemLevel >= 0;
        });
    }
    // Elements of a value of dtypep: the product of its unpacked dimensions
    static uint32_t elementCount(const AstNodeDType* dtypep) {
        uint32_t count = 1;
        for (dtypep = dtypep->skipRefp();
             const AstUnpackArrayDType* const adtypep = VN_CAST(dtypep, UnpackArrayDType);
             dtypep = adtypep->subDTypep()->skipRefp()) {
            count *= adtypep->elementsConst();
        }
        return count;
    }
    // Slots of the part of classp
    const std::vector<AstVar*>& slots(const AstClass* classp) {
        const auto pair = m_slots.emplace(classp, std::vector<AstVar*>{});
        if (pair.second) pair.first->second = dvsSlots(classp);
        return pair.first->second;
    }
    // Number of slots of the part of classp: an array of handles has one per element
    uint32_t slotCount(const AstClass* classp) {
        uint32_t count = 0;
        for (const AstVar* const slotp : slots(classp)) count += elementCount(slotp->dtypep());
        return count;
    }
    // First slot of slotp, a slot member of classp
    uint32_t slotIndex(const AstClass* classp, const AstVar* slotp) {
        const std::vector<AstVar*>& classSlots = slots(classp);
        const auto it = std::find(classSlots.begin(), classSlots.end(), slotp);
        UASSERT_OBJ(it != classSlots.end(), slotp, "Not a slot");
        uint32_t index = 0;
        for (auto prevIt = classSlots.begin(); prevIt != it; ++prevIt) {
            index += elementCount((*prevIt)->dtypep());
        }
        return index;
    }
    // Export index of each variable in the layout of classp
    const std::map<const AstVar*, uint32_t>& layout(AstClass* classp) {
        const auto pair = m_layouts.emplace(classp, std::map<const AstVar*, uint32_t>{});
        if (pair.second) {
            uint32_t index = 0;
            classp->foreachMember([&](AstClass*, AstVar* varp) {
                if (!isLayoutVar(varp)) return;
                pair.first->second.emplace(varp, index);
                index += elementCount(varp->dtypep());
            });
        }
        return pair.first->second;
    }
    // First problem variable of the import of nodep: a random variable of an object reached
    // through a slot path (dvsIsSlotPath), or in a site part, one of the object randomized
    // through a slot path (dvsIsSlotPath), or in a site part, one of the object randomized; or
    // -1 if the path selects an element of an array of handles out of range
    int64_t importVarId(AstNodeExpr* nodep) {
        AstMemberSel* const selp = VN_CAST(nodep, MemberSel);
        AstVar* const varp = selp ? selp->varp() : VN_AS(nodep, VarRef)->varp();
        std::vector<uint32_t> path;
        for (AstNodeExpr* fromp = selp ? selp->fromp() : nullptr; fromp;) {
            // An element of a slot array: the word selecting it follows the array's slot
            if (AstCMethodHard* const atp = VN_CAST(fromp, CMethodHard)) {
                uint32_t word = 0;
                if (!slotSelector(atp->pinsp(), word)) return -1;
                path.insert(path.begin(), word);
                fromp = atp->fromp();
            }
            // An element of an array of handles: its index among the array's slots
            uint32_t element = 0;
            uint32_t stride = 1;
            while (AstArraySel* const arraySelp = VN_CAST(fromp, ArraySel)) {
                const uint32_t elements
                    = VN_AS(arraySelp->fromp()->dtypep()->skipRefp(), UnpackArrayDType)
                          ->elementsConst();
                AstConst* const indexp = newBoundConstp(arraySelp->bitp());
                if (!indexp) {
                    unsupported(arraySelp, "index of an array of class handles that is not a"
                                           " constant or a 'foreach' index");
                    return -1;
                }
                const uint64_t index = indexp->num().toUQuad();
                VL_DO_DANGLING(indexp->deleteTree(), indexp);
                if (index >= elements) return -1;
                element += index * stride;
                stride *= elements;
                fromp = arraySelp->fromp();
            }
            if (AstMemberSel* const fromSelp = VN_CAST(fromp, MemberSel)) {
                path.insert(path.begin(), slotIndex(dvsHandleClassp(fromSelp->fromp()->dtypep()),
                                                    fromSelp->varp())
                                              + element);
                fromp = fromSelp->fromp();
            } else {
                path.insert(path.begin(),
                            slotIndex(m_site.classp, VN_AS(fromp, VarRef)->varp()) + element);
                fromp = nullptr;
            }
        }
        if (m_site.inlinePart) path.insert(path.begin(), 0);
        const auto pair = m_importIds.emplace(std::make_pair(path, varp), m_varInfos.size());
        if (!pair.second) return pair.first->second;
        const uint32_t exportIndex
            = layout(selp ? dvsHandleClassp(selp->fromp()->dtypep()) : m_site.classp).at(varp);
        const AstNodeDType* elemDTypep = varp->dtypep()->skipRefToEnump();
        while (const AstUnpackArrayDType* const adtypep = VN_CAST(elemDTypep, UnpackArrayDType)) {
            elemDTypep = adtypep->subDTypep()->skipRefToEnump();
        }
        // The values of an enum are constrained in the part exporting it
        for (uint32_t i = 0; i < elementCount(varp->dtypep()); ++i) {
            const uint32_t id = newVar(elemDTypep->width(), elemDTypep->isSigned(), false);
            m_varInfos[id] |= DVS_INFO_IMPORT;
            dvs_builder_add_import(m_builderp, id, path.size(), path.data(), exportIndex + i);
        }
        return pair.first->second;
    }
    // Problem variable of nodep, a random variable or an element of a random array, or -1 if
    // an index is out of range
    int64_t randRefId(AstNodeExpr* nodep) {
        if (AstVarRef* const refp = VN_CAST(nodep, VarRef)) return varRefId(refp);
        if (AstMemberSel* const selp = VN_CAST(nodep, MemberSel)) return importVarId(selp);
        AstArraySel* const selp = VN_AS(nodep, ArraySel);
        const int64_t arrayId = randRefId(selp->fromp());
        const AstUnpackArrayDType* const adtypep
            = VN_AS(selp->fromp()->dtypep()->skipRefp(), UnpackArrayDType);
        AstConst* const indexp = newBoundConstp(selp->bitp());
        if (!indexp) {
            unsupported(selp, "array index that is not a constant or a 'foreach' index"
                              " in 'dist', 'unique' or 'solve before'");
            return -1;
        }
        const uint64_t index = indexp->num().toUQuad();
        VL_DO_DANGLING(indexp->deleteTree(), indexp);
        if (arrayId < 0 || index >= static_cast<uint64_t>(adtypep->elementsConst())) return -1;
        return arrayId + index * elementCount(adtypep->subDTypep());
    }
    // Problem variables of nodep, a random variable, an element of a random array, or an
    // unpacked array of them; refused if an index is out of range
    std::vector<uint32_t> randRefIds(AstNodeExpr* nodep) {
        const int64_t id = randRefId(nodep);
        if (id < 0) {
            unsupported(nodep, "array index out of range");
            return {newVar(1, false, true)};  // A placeholder: the problem is not built
        }
        std::vector<uint32_t> ids;  // An unpacked array's elements are consecutive
        for (uint32_t i = 0; i < elementCount(nodep->dtypep()); ++i) ids.push_back(id + i);
        return ids;
    }
    // Problem variable of refp, a random variable: of this object, or in a site part an import
    uint32_t varRefId(AstVarRef* refp) {
        return m_site.inlinePart ? importVarId(refp) : randVarId(refp->varp());
    }
    Value varValue(uint32_t id) {
        return {dvs_builder_expr_var(m_builderp, id), m_varInfos[id] & DVS_INFO_WIDTH,
                (m_varInfos[id] >> 31) != 0, false};
    }
    // A variable of dtypep passed to the call, assigned exprp before it: a local of the
    // function, or for a part a member of the class (it is read after the function returns)
    void newTempp(AstNodeExpr* exprp, const std::string& suffix, AstNodeDType* dtypep) {
        FileLine* const flp = exprp->fileline();
        // A site part is solved before its function returns
        const bool local = !m_site.part || m_site.inlinePart;
        AstVar* varp;
        if (!local) {
            varp = new AstVar{flp, VVarType::MEMBER, "__Vdvs_part_" + suffix, dtypep};
            varp->user2p(m_site.classp);
            m_site.classp->addMembersp(varp);
        } else {
            varp = new AstVar{flp, VVarType::BLOCKTEMP, "__Vdvs_" + suffix, dtypep};
            varp->funcLocal(true);
            m_funcp->addStmtsp(varp);
        }
        const Arg arg{varp, local};
        m_funcp->addStmtsp(
            new AstAssign{flp, newArgRefp(flp, arg, VAccess::WRITE), exprp->cloneTree(false)});
        m_args.push_back(arg);
    }
    static AstVarRef* newArgRefp(FileLine* flp, const Arg& arg, VAccess access) {
        if (arg.local) return new AstVarRef{flp, arg.varp, access};
        return new AstVarRef{flp, VN_AS(arg.varp->user2p(), NodeModule), arg.varp, access};
    }
    // STATE variable holding the value of exprp, evaluated before the call
    Value stateValue(AstNodeExpr* exprp) {
        const AstNodeVarRef* const refp = VN_CAST(exprp, NodeVarRef);
        if (refp) {
            const auto it = m_varIds.find(refp->varp());
            if (it != m_varIds.end()) return stateVarValue(it->second);
        }
        const uint32_t width = exprp->width();
        const bool isSigned = exprp->isSigned();
        newTempp(exprp, "state" + std::to_string(m_varInfos.size()),
                 exprp->findBitDType(width, width, VSigning::fromBool(isSigned)));
        const uint32_t id = newVar(width, isSigned, true);
        if (refp) m_varIds.emplace(refp->varp(), id);
        return stateVarValue(id);
    }
    // STATE variables holding the elements of arrayp, a fixed-size unpacked array evaluated
    // before the call, in storage order
    std::vector<Value> stateValues(AstNodeExpr* arrayp) {
        AstNodeExpr* const boundp = newBoundp(arrayp);
        newTempp(boundp, "state" + std::to_string(m_varInfos.size()), arrayp->dtypep());
        VL_DO_DANGLING(boundp->deleteTree(), boundp);
        const AstNodeDType* const elemp = elemDTypep(arrayp);
        std::vector<Value> result;
        for (uint32_t i = 0; i < elementCount(arrayp->dtypep()); ++i) {
            result.push_back(stateVarValue(newVar(elemp->width(), elemp->isSigned(), true)));
        }
        return result;
    }
    // A STATE bit is a condition as is, so dv-solve knows it before solving, as it must know
    // a guard of a read through a null handle ('h != null')
    Value stateVarValue(uint32_t id) {
        Value value = varValue(id);
        value.isBool = value.width == 1;
        return value;
    }

    // A copy of nodep, with each foreach loop variable and 'item.index' replaced by its value
    // ('item' itself depends on a random variable, so is not in nodep)
    AstNodeExpr* newBoundp(AstNodeExpr* nodep) {
        AstNodeExpr* clonep = nodep->cloneTree(false);
        std::vector<std::pair<AstNodeExpr*, int64_t>> binds;
        clonep->foreach([&](AstVarRef* refp) {
            const auto it = m_loopValues.find(refp->varp());
            if (it != m_loopValues.end()) binds.emplace_back(refp, it->second);
        });
        if (m_itemp) {
            std::set<const AstLambdaArgRef*> nested;  // Of a 'with' in nodep
            clonep->foreach([&](AstWith* withp) {
                withp->foreach([&](const AstLambdaArgRef* refp) { nested.insert(refp); });
            });
            clonep->foreach([&](AstLambdaArgRef* refp) {
                if (!nested.count(refp)) binds.emplace_back(refp, m_itemIndex);
            });
        }
        for (const auto& bind : binds) {
            AstNodeExpr* const refp = bind.first;
            V3Number num{refp, refp->width()};
            num.setQuad(bind.second);
            num.isSigned(refp->isSigned());
            AstConst* const constp = new AstConst{refp->fileline(), num};
            if (refp == clonep) {
                clonep = constp;
            } else {
                refp->replaceWith(constp);
            }
            VL_DO_DANGLING(refp->deleteTree(), refp);
        }
        return clonep;
    }
    // The value of nodep with the foreach loop variables replaced, if it is a constant, as a
    // new node; else nullptr
    AstConst* newBoundConstp(AstNodeExpr* nodep) {
        AstNodeExpr* const boundp = newBoundp(nodep);
        AstConst* const constp = dvsNewConstp(boundp);
        VL_DO_DANGLING(boundp->deleteTree(), boundp);
        return constp;
    }

    // Expressions
    Value constant(const V3Number& num, uint32_t width, bool isSigned) {
        return {dvs_builder_expr_const_sized(m_builderp, static_cast<int64_t>(num.toUQuad()),
                                             isSigned, width),
                width, isSigned, false};
    }
    Value constant(uint64_t value, uint32_t width, bool isSigned) {
        return {
            dvs_builder_expr_const_sized(m_builderp, static_cast<int64_t>(value), isSigned, width),
            width, isSigned, false};
    }
    Value falseValue() {
        return {dvs_builder_expr_const_sized(m_builderp, 0, 0, 1), 1, false, true};
    }
    Value binary(dvs_binop_t op, const Value& lhs, const Value& rhs, bool isBool) {
        return {dvs_builder_expr_binary(m_builderp, op, lhs.expr, rhs.expr),
                isBool ? 1 : lhs.width, !isBool && lhs.isSigned, isBool};
    }
    Value asUnsigned(const Value& value) {
        if (!value.isSigned) return value;
        return {dvs_builder_expr_extract(m_builderp, value.expr, value.width - 1, 0), value.width,
                false, false};
    }
    Value asSigned(const Value& value) {
        if (value.isSigned) return value;
        return {dvs_builder_expr_sv_cast(m_builderp, value.expr, value.width, value.width, 0, 1),
                value.width, true, false};
    }
    Value asBool(const Value& value) {
        if (value.isBool) return value;
        return binary(DVS_BIN_NEQ, value, constant(0, value.width, value.isSigned), true);
    }
    Value logNot(const Value& value) {
        return {dvs_builder_expr_unary(m_builderp, DVS_UN_NOT, asBool(value).expr), 1, false,
                true};
    }
    // Operator op on operands of the same signedness
    Value sameSign(dvs_binop_t op, Value lhs, Value rhs, bool isBool) {
        if (lhs.isSigned != rhs.isSigned) {
            lhs = asUnsigned(lhs);
            rhs = asUnsigned(rhs);
        }
        return binary(op, lhs, rhs, isBool);
    }
    // Comparison, signed if both operands are signed (IEEE 1800-2023 11.8.1)
    Value compare(dvs_binop_t op, const Value& lhs, const Value& rhs) {
        if (lhs.isSigned && rhs.isSigned) return binary(op, lhs, rhs, true);
        return binary(op, asUnsigned(lhs), asUnsigned(rhs), true);
    }
    // Operator op on signed or unsigned operands
    Value signedOp(dvs_binop_t op, AstNodeBiop* nodep, bool isSigned, bool isBool) {
        const Value lhs = expr(nodep->lhsp());
        const Value rhs = expr(nodep->rhsp());
        if (isSigned) return binary(op, asSigned(lhs), asSigned(rhs), isBool);
        return binary(op, asUnsigned(lhs), asUnsigned(rhs), isBool);
    }
    Value shift(dvs_binop_t op, AstNodeBiop* nodep, const Value& lhs) {
        return binary(op, lhs, asUnsigned(expr(nodep->rhsp())), false);
    }
    Value logic(dvs_binop_t op, AstNodeBiop* nodep) {
        return binary(op, asBool(expr(nodep->lhsp())), asBool(expr(nodep->rhsp())), true);
    }
    Value bitwise(dvs_binop_t op, AstNodeBiop* nodep) {
        const Value lhs = expr(nodep->lhsp());
        const Value rhs = expr(nodep->rhsp());
        Value result = sameSign(op, lhs, rhs, false);
        result.isBool = lhs.isBool && rhs.isBool;
        return result;
    }
    Value concat(const Value& hi, const Value& lo) {
        return {dvs_builder_expr_concat(m_builderp, asUnsigned(hi).expr, asUnsigned(lo).expr,
                                        lo.width),
                hi.width + lo.width, false, false};
    }
    // Values of nodep, a random variable, an element of a random array, or an unpacked array
    // of them, one per element in storage order
    std::vector<Value> values(AstNodeExpr* nodep) {
        AstArraySel* const selp = VN_CAST(nodep, ArraySel);
        if (!selp) {
            std::vector<Value> result;
            for (const uint32_t id : randRefIds(nodep)) result.push_back(varValue(id));
            return result;
        }
        const std::vector<Value> from = values(selp->fromp());
        const uint32_t stride = elementCount(nodep->dtypep());
        const uint32_t elements = from.size() / stride;
        std::vector<Value> result(stride, constant(0, from[0].width, from[0].isSigned));
        AstConst* const indexp = newBoundConstp(selp->bitp());
        if (indexp) {
            const uint64_t index = indexp->num().toUQuad();
            VL_DO_DANGLING(indexp->deleteTree(), indexp);
            if (index < elements) {
                std::copy_n(from.begin() + index * stride, stride, result.begin());
            }
            return result;
        }
        // A choice over the elements
        const Value index = asUnsigned(expr(selp->bitp()));
        for (uint32_t i = elements; i-- > 0;) {
            const Value cond = binary(DVS_BIN_EQ, index, constant(i, index.width, false), true);
            for (uint32_t j = 0; j < stride; ++j) {
                result[j].expr = dvs_builder_expr_ite(m_builderp, cond.expr,
                                                      from[i * stride + j].expr, result[j].expr);
            }
        }
        return result;
    }
    Value reduction(AstCMethodHard* nodep) {
        dvs_binop_t op;
        switch (nodep->method()) {
        case VCMethod::ARRAY_R_AND: op = DVS_BIN_BAND; break;
        case VCMethod::ARRAY_R_OR: op = DVS_BIN_BOR; break;
        case VCMethod::ARRAY_R_PRODUCT: op = DVS_BIN_MUL; break;
        case VCMethod::ARRAY_R_SUM: op = DVS_BIN_ADD; break;
        case VCMethod::ARRAY_R_XOR: op = DVS_BIN_BXOR; break;
        default: nodep->v3fatalSrc("Method not accepted by dvsIsMappable");
        }
        AstWith* const withp = nodep->withp();
        if (isDynArray(nodep->fromp()->dtypep())) {
            // One 'with' expression over a loop index, folded by dv-solve
            const uint32_t id = arrayId(nodep->fromp());
            const uint32_t level = m_levels++;
            VL_RESTORER(m_itemp);
            VL_RESTORER(m_itemLevel);
            const Value item = elemValue(id, loopIndex(level));
            m_itemp = &item;
            m_itemLevel = level;
            const Value body = withp ? expr(VN_AS(withp->exprp(), NodeExpr)) : item;
            --m_levels;
            return {dvs_builder_expr_reduce(m_builderp, op, id, level, body.expr), body.width,
                    body.isSigned, false};
        }
        const std::vector<Value> items = values(nodep->fromp());
        VL_RESTORER(m_itemp);
        VL_RESTORER(m_itemIndex);
        VL_RESTORER(m_itemLevel);
        m_itemLevel = -1;  // 'item.index' is bound by newBoundp
        Value result = items[0];
        for (size_t i = 0; i < items.size(); ++i) {
            m_itemp = &items[i];
            m_itemIndex = i;
            const Value term = withp ? expr(VN_AS(withp->exprp(), NodeExpr)) : items[i];
            result = i ? binary(op, result, term, false) : term;
        }
        return result;
    }
    // 'x inside {arr}': arr.or() with (item == x) (IEEE 1800-2023 11.4.13), false if empty
    Value inside(AstCMethodHard* nodep) {
        const Value value = expr(nodep->pinsp());
        AstNodeExpr* const fromp = nodep->fromp();
        if (isDynArray(fromp->dtypep())) {
            // Folded by dv-solve over the elements of the call
            AstNodeExpr* const boundp = newBoundp(fromp);
            const uint32_t id = arrayId(boundp);
            VL_DO_DANGLING(boundp->deleteTree(), boundp);
            const uint32_t level = m_levels++;
            const Value body = sameSign(DVS_BIN_EQ, elemValue(id, loopIndex(level)), value, true);
            --m_levels;
            return {dvs_builder_expr_reduce(m_builderp, DVS_BIN_BOR, id, level, body.expr), 1,
                    false, true};
        }
        Value result = falseValue();
        for (const Value& item : fromp->user1() ? values(fromp) : stateValues(fromp)) {
            result = binary(DVS_BIN_OR, result, sameSign(DVS_BIN_EQ, item, value, true), true);
        }
        return result;
    }
    Value expr(AstNodeExpr* nodep) {
        if (!nodep->user1() && !readsLoopIndex(nodep)) {
            // A constant expression is a constant, anything else is read before the call
            AstNodeExpr* const boundp = newBoundp(nodep);
            AstConst* const constp = dvsNewConstp(boundp);
            const Value value = constp
                                    ? constant(constp->num(), constp->width(), constp->isSigned())
                                    : stateValue(boundp);
            if (constp) VL_DO_DANGLING(constp->deleteTree(), constp);
            VL_DO_DANGLING(boundp->deleteTree(), boundp);
            return value;
        }
        if (AstCMethodHard* const atp = dvsSlotNullComparep(nodep)) {
            // Whether a handle is null is known when the parts are assembled, so is a guard
            uint32_t word;
            slotSelector(atp->pinsp(), word);
            Value bit = elemValue(arrayId(atp->fromp()), expr(atp->pinsp()));
            bit.isBool = true;
            return VN_IS(nodep, Eq) ? logNot(bit) : bit;
        }
        AstNodeBiop* const biopp = VN_CAST(nodep, NodeBiop);
        const uint32_t width = nodep->width();
        switch (nodep->type()) {
        case VNType::VarRef: {
            AstVar* const varp = VN_AS(nodep, VarRef)->varp();
            const auto it = m_loopLevels.find(varp);
            if (it == m_loopLevels.end()) return varValue(varRefId(VN_AS(nodep, VarRef)));
            // The index of a 'foreach' over a dynamic array, an int
            UASSERT_OBJ(nodep->width() == 32, nodep, "Loop variable not an int");
            return loopIndex(it->second);
        }
        case VNType::ArraySel:  // FALLTHRU
        case VNType::MemberSel: return values(nodep).front();
        case VNType::CMethodHard: {
            AstCMethodHard* const callp = VN_AS(nodep, CMethodHard);
            if (callp->method() == VCMethod::ARRAY_AT) {
                const uint32_t id = arrayId(callp->fromp());
                return elemValue(id, expr(callp->pinsp()));
            }
            if (callp->method() == VCMethod::DYN_SIZE) {
                const uint32_t id = arrayId(callp->fromp());
                // Outside a 'foreach' over the array, a constraint on its size
                if (!m_foreachArrays.count(id) && callp->fromp()->user1()) {
                    if (m_site.inlinePart) {
                        unsupported(callp, "size of an array of class handles in randomize()"
                                           " with {...}");
                    }
                    m_sizedArrays.insert(id);
                }
                return {dvs_builder_expr_array_size(m_builderp, id), 32, true, false};
            }
            if (callp->method() == VCMethod::ARRAY_INSIDE) return inside(callp);
            return reduction(callp);
        }
        case VNType::LambdaArgRef:
            if (VN_AS(nodep, LambdaArgRef)->index()) return loopIndex(m_itemLevel);
            return *m_itemp;
        case VNType::Extend: {
            const Value lhs = asUnsigned(expr(VN_AS(nodep, Extend)->lhsp()));
            return {dvs_builder_expr_extend(m_builderp, lhs.expr, lhs.width, width, 0), width,
                    false, false};
        }
        case VNType::ExtendS: {
            const Value lhs = asSigned(expr(VN_AS(nodep, ExtendS)->lhsp()));
            return {dvs_builder_expr_extend(m_builderp, lhs.expr, lhs.width, width, 1), width,
                    true, false};
        }
        case VNType::Add:
            return sameSign(DVS_BIN_ADD, expr(biopp->lhsp()), expr(biopp->rhsp()), false);
        case VNType::Sub:
            return sameSign(DVS_BIN_SUB, expr(biopp->lhsp()), expr(biopp->rhsp()), false);
        case VNType::Mul:  // FALLTHRU
        case VNType::MulS:
            return sameSign(DVS_BIN_MUL, expr(biopp->lhsp()), expr(biopp->rhsp()), false);
        case VNType::Div: return signedOp(DVS_BIN_DIV, biopp, false, false);
        case VNType::DivS: return signedOp(DVS_BIN_DIV, biopp, true, false);
        case VNType::ModDiv: return signedOp(DVS_BIN_MOD, biopp, false, false);
        case VNType::ModDivS: return signedOp(DVS_BIN_MOD, biopp, true, false);
        case VNType::And: return bitwise(DVS_BIN_BAND, biopp);
        case VNType::Or: return bitwise(DVS_BIN_BOR, biopp);
        case VNType::Xor: return bitwise(DVS_BIN_BXOR, biopp);
        case VNType::ShiftL: return shift(DVS_BIN_LSHIFT, biopp, expr(biopp->lhsp()));
        case VNType::ShiftR: return shift(DVS_BIN_RSHIFT, biopp, asUnsigned(expr(biopp->lhsp())));
        case VNType::ShiftRS: return shift(DVS_BIN_ASHR, biopp, asSigned(expr(biopp->lhsp())));
        case VNType::Eq:  // FALLTHRU
        case VNType::EqCase:  // FALLTHRU
        case VNType::EqWild:  // Constants with X or Z bits are refused
            return sameSign(DVS_BIN_EQ, expr(biopp->lhsp()), expr(biopp->rhsp()), true);
        case VNType::Neq:  // FALLTHRU
        case VNType::NeqCase:  // FALLTHRU
        case VNType::NeqWild:
            return sameSign(DVS_BIN_NEQ, expr(biopp->lhsp()), expr(biopp->rhsp()), true);
        case VNType::Lt: return signedOp(DVS_BIN_LT, biopp, false, true);
        case VNType::Lte: return signedOp(DVS_BIN_LTE, biopp, false, true);
        case VNType::Gt: return signedOp(DVS_BIN_GT, biopp, false, true);
        case VNType::Gte: return signedOp(DVS_BIN_GTE, biopp, false, true);
        case VNType::LtS: return signedOp(DVS_BIN_LT, biopp, true, true);
        case VNType::LteS: return signedOp(DVS_BIN_LTE, biopp, true, true);
        case VNType::GtS: return signedOp(DVS_BIN_GT, biopp, true, true);
        case VNType::GteS: return signedOp(DVS_BIN_GTE, biopp, true, true);
        case VNType::LogAnd: return logic(DVS_BIN_AND, biopp);
        case VNType::LogOr: return logic(DVS_BIN_OR, biopp);
        case VNType::LogEq: return logic(DVS_BIN_EQ, biopp);
        case VNType::LogIf:
            return binary(DVS_BIN_OR, logNot(expr(biopp->lhsp())), asBool(expr(biopp->rhsp())),
                          true);
        case VNType::LogNot: return logNot(expr(VN_AS(nodep, LogNot)->lhsp()));
        case VNType::Not: {
            const Value lhs = expr(VN_AS(nodep, Not)->lhsp());
            if (lhs.isBool) return logNot(lhs);
            return {dvs_builder_expr_unary(m_builderp, DVS_UN_INVERT, lhs.expr), width,
                    lhs.isSigned, false};
        }
        case VNType::Negate: {
            // As 0 - x, which wraps like the SystemVerilog operator
            const Value lhs = expr(VN_AS(nodep, Negate)->lhsp());
            return binary(DVS_BIN_SUB, constant(0, width, lhs.isSigned), lhs, false);
        }
        case VNType::RedOr: return asBool(asUnsigned(expr(VN_AS(nodep, RedOr)->lhsp())));
        case VNType::RedAnd: {
            const Value lhs = asUnsigned(expr(VN_AS(nodep, RedAnd)->lhsp()));
            return binary(DVS_BIN_EQ, lhs, constant(VL_MASK_Q(lhs.width), lhs.width, false), true);
        }
        case VNType::Sel: {
            AstSel* const selp = VN_AS(nodep, Sel);
            const Value from = expr(selp->fromp());
            AstConst* const lsbp = newBoundConstp(selp->lsbp());
            if (!lsbp) {
                unsupported(nodep, "bit select at a non-constant position of a random value");
                return from;
            }
            const uint32_t lsb = lsbp->toUInt();
            VL_DO_DANGLING(lsbp->deleteTree(), lsbp);
            return {dvs_builder_expr_extract(m_builderp, from.expr, lsb + width - 1, lsb), width,
                    false, false};
        }
        case VNType::Concat: return concat(expr(biopp->lhsp()), expr(biopp->rhsp()));
        case VNType::Replicate: {
            AstReplicate* const repp = VN_AS(nodep, Replicate);
            const Value src = expr(repp->srcp());
            Value result = src;
            for (uint32_t i = 1; i < VN_AS(repp->countp(), Const)->toUInt(); ++i) {
                result = concat(result, src);
            }
            return result;
        }
        case VNType::Cond: {
            AstCond* const condp = VN_AS(nodep, Cond);
            const Value cond = asBool(expr(condp->condp()));
            Value thenv = expr(condp->thenp());
            Value elsev = expr(condp->elsep());
            if (thenv.isSigned != elsev.isSigned) {
                thenv = asUnsigned(thenv);
                elsev = asUnsigned(elsev);
            }
            return {dvs_builder_expr_ite(m_builderp, cond.expr, thenv.expr, elsev.expr), width,
                    thenv.isSigned, thenv.isBool && elsev.isBool};
        }
        default: nodep->v3fatalSrc("Constraint operator not accepted by V3SolverDvsCheck");
        }
    }

    // Constraints
    // Every hard constraint is added here, so m_constraintInfos[1 + 2 * i] and [2 + 2 * i]
    // describe constraint i of the problem, in add order
    void addHard(dvs_expr_t root, FileLine* flp) {
        dvs_builder_add_constraint(m_builderp, root);
        m_constraintInfos.push_back(location(flp));
        std::string source;
        if (!v3Global.opt.protectIds()) {
            source = flp->prettySource();
            source.erase(0, source.find_first_not_of(" \t"));
        }
        m_constraintInfos.push_back(source);
    }
    // 'guards -> value', a constraint
    dvs_expr_t guarded(const std::vector<Value>& guards, const Value& value) {
        Value result = asBool(value);
        for (const Value& guard : guards) {
            result = binary(DVS_BIN_OR, logNot(guard), result, true);
        }
        return result.expr;
    }
    void addDist(AstDist* distp) {
        AstNodeExpr* targetp = distp->exprp();
        if (AstNodeUniop* const extp = VN_CAST(targetp, NodeUniop)) targetp = extp->lhsp();
        // An element of a dynamic array, in a 'foreach' over it; else a variable
        AstCMethodHard* const atp = VN_CAST(targetp, CMethodHard);
        uint32_t id = 0;
        Value index{};
        if (atp) {
            id = arrayId(atp->fromp());
            index = expr(atp->pinsp());
        } else {
            id = randRefIds(targetp).front();
        }
        const Value var = atp ? elemValue(id, index) : varValue(id);
        const bool isSigned = var.isSigned;
        const uint32_t width = var.width;
        const int64_t varLo = isSigned ? -static_cast<int64_t>(VL_MASK_Q(width - 1)) - 1 : 0;
        const uint64_t varHi = isSigned ? VL_MASK_Q(width - 1) : VL_MASK_Q(width);
        const auto inVar = [&](AstNodeExpr* nodep) {  // Value, as the variable reads it
            AstConst* const constp = newBoundConstp(nodep);
            const int64_t value = isSigned ? constp->num().toSQuad()
                                           : static_cast<int64_t>(constp->num().toUQuad());
            VL_DO_DANGLING(constp->deleteTree(), constp);
            return value;
        };
        // Weights select among the values. The values the variable may take are also a hard
        // constraint, since dv-solve does not enforce them on every engine; it compares the
        // variable at its own type, which dv-solve's CDCL engine compiles
        std::vector<dvs_dist_entry_t> entries;
        Value member = falseValue();
        for (AstDistItem* itemp = distp->itemsp(); itemp;
             itemp = VN_AS(itemp->nextp(), DistItem)) {
            const uint32_t weight = static_cast<uint32_t>(inVar(itemp->weightp()));
            if (!weight) continue;
            AstInsideRange* const rangep = VN_CAST(itemp->rangep(), InsideRange);
            // The entry, clipped to the values of the variable
            int64_t entryLo = inVar(rangep ? rangep->lhsp() : itemp->rangep());
            int64_t entryHi = inVar(rangep ? rangep->rhsp() : itemp->rangep());
            if (isSigned) {
                entryLo = std::max(entryLo, varLo);
                entryHi = std::min(entryHi, static_cast<int64_t>(varHi));
                if (entryLo > entryHi) continue;
            } else {
                if (static_cast<uint64_t>(entryLo) > varHi) continue;
                if (static_cast<uint64_t>(entryHi) > varHi) entryHi = static_cast<int64_t>(varHi);
                if (static_cast<uint64_t>(entryLo) > static_cast<uint64_t>(entryHi)) continue;
            }
            const Value lo = constant(entryLo, width, isSigned);
            const Value hi = constant(entryHi, width, isSigned);
            member = binary(DVS_BIN_OR, member,
                            binary(DVS_BIN_AND, binary(DVS_BIN_GTE, var, lo, true),
                                   binary(DVS_BIN_LTE, var, hi, true), true),
                            true);
            dvs_dist_entry_t entry{};
            entry.lo = entryLo;
            entry.hi = entryHi;
            entry.weight = weight;
            entry.is_per_value = !itemp->isWhole();
            entries.push_back(entry);
        }
        addHard(member.expr, distp->fileline());
        if (entries.empty()) return;
        if (atp) {
            dvs_builder_add_dist_elem(m_builderp, id, index.expr, entries.size(), entries.data());
        } else {
            dvs_builder_add_dist(m_builderp, id, entries.size(), entries.data());
        }
    }
    void addItems(AstNode* itemsp, const std::vector<Value>& guards) {
        for (AstNode* itemp = itemsp; itemp; itemp = itemp->nextp()) {
            if (AstConstraintExpr* const cexprp = VN_CAST(itemp, ConstraintExpr)) {
                if (AstDist* const distp = VN_CAST(cexprp->exprp(), Dist)) {
                    addDist(distp);
                } else if (cexprp->isSoft() || m_soft) {
                    // Added now, as it may be in the body of a dv-solve foreach
                    dvs_builder_add_soft_constraint(m_builderp,
                                                    guarded(guards, expr(cexprp->exprp())),
                                                    DVS_FIRST_SOFT - m_nSofts++);
                } else {
                    addHard(guarded(guards, expr(cexprp->exprp())), cexprp->fileline());
                }
            } else if (AstConstraintIf* const ifp = VN_CAST(itemp, ConstraintIf)) {
                const Value cond = asBool(expr(ifp->condp()));
                std::vector<Value> inner = guards;
                inner.push_back(cond);
                addItems(ifp->thensp(), inner);
                inner.back() = logNot(cond);
                addItems(ifp->elsesp(), inner);
            } else if (AstConstraintForeach* const foreachp = VN_CAST(itemp, ConstraintForeach)) {
                VL_RESTORER(m_soft);
                m_soft = m_soft || foreachp->isSoft();
                AstForeachHeader* const headerp = foreachp->headerp();
                if (isDynArray(headerp->fromp()->dtypep())) {
                    addDynForeach(foreachp, guards);
                } else {
                    addForeach(foreachp, headerp->fromp()->dtypep(), headerp->elementsp(), guards);
                }
            } else if (AstConstraintUnique* const uniquep = VN_CAST(itemp, ConstraintUnique)) {
                std::vector<uint32_t> ids;
                for (AstNode* refp = uniquep->rangesp(); refp; refp = refp->nextp()) {
                    AstNodeExpr* const exprp = VN_AS(refp, NodeExpr);
                    if (isDynArray(exprp->dtypep())) {
                        ids.push_back(DVS_ARRAY_MEMBER(arrayId(exprp)));
                        continue;
                    }
                    for (const uint32_t id : randRefIds(exprp)) ids.push_back(id);
                }
                dvs_builder_add_all_different(m_builderp, ids.size(), ids.data());
            } else {
                AstConstraintBefore* const beforep = VN_AS(itemp, ConstraintBefore);
                std::vector<uint32_t> rhsIds;
                for (AstNode* rhsp = beforep->rhssp(); rhsp; rhsp = rhsp->nextp()) {
                    for (const uint32_t id : randRefIds(VN_AS(rhsp, NodeExpr))) {
                        rhsIds.push_back(id);
                    }
                }
                for (AstNode* lhsp = beforep->lhssp(); lhsp; lhsp = lhsp->nextp()) {
                    for (const uint32_t lhsId : randRefIds(VN_AS(lhsp, NodeExpr))) {
                        for (const uint32_t rhsId : rhsIds) m_befores.emplace_back(lhsId, rhsId);
                    }
                }
            }
        }
    }
    // Items of nodep for each index of the dimensions of dtypep that loop variables from elemp
    // on iterate (AstEmpty: a dimension not iterated)
    void addForeach(AstConstraintForeach* nodep, AstNodeDType* dtypep, AstNode* elemp,
                    const std::vector<Value>& guards) {
        if (!elemp) {
            addItems(nodep->bodyp(), guards);
            return;
        }
        const AstUnpackArrayDType* const adtypep = VN_AS(dtypep->skipRefp(), UnpackArrayDType);
        AstVar* const varp = VN_CAST(elemp, Var);
        if (!varp) {
            addForeach(nodep, adtypep->subDTypep(), elemp->nextp(), guards);
            return;
        }
        for (int index = adtypep->lo(); index <= adtypep->hi(); ++index) {
            m_loopValues[varp] = index;
            addForeach(nodep, adtypep->subDTypep(), elemp->nextp(), guards);
        }
        m_loopValues.erase(varp);
    }
    // Items of nodep, a 'foreach' over a dynamic array: a dv-solve foreach, its loop
    // variable the loop index
    void addDynForeach(AstConstraintForeach* nodep, const std::vector<Value>& guards) {
        AstForeachHeader* const headerp = nodep->headerp();
        AstVar* const varp = VN_AS(headerp->elementsp(), Var);
        const uint32_t id = arrayId(headerp->fromp());
        const uint32_t level = m_levels++;
        const bool outer = m_foreachArrays.insert(id).second;
        m_loopLevels[varp] = level;
        if (dvsIsSlotArray(headerp->fromp()->dtypep())) m_slotLoopVars.insert(varp);
        dvs_builder_foreach_begin(m_builderp, id, level);
        addItems(nodep->bodyp(), guards);
        dvs_builder_foreach_end(m_builderp);
        m_loopLevels.erase(varp);
        m_slotLoopVars.erase(varp);
        if (outer) m_foreachArrays.erase(id);
        --m_levels;
    }
    // The enable of a constraint block: its constraint_mode() bit
    Value enable(const DvsSite::Block& block) {
        FileLine* const flp = block.itemsp->fileline();
        AstNodeModule* const modp = VN_AS(block.modeVarp->user2p(), NodeModule);
        AstCMethodHard* const atp
            = new AstCMethodHard{flp, new AstVarRef{flp, modp, block.modeVarp, VAccess::READ},
                                 VCMethod::ARRAY_AT, new AstConst{flp, block.modeIndex}};
        atp->dtypeSetUInt32();
        const Value value = stateValue(atp);
        VL_DO_DANGLING(atp->deleteTree(), atp);  // stateValue cloned it
        return value;
    }
    // Solve-before stages: each variable after the variables it is solved after, from stage 1
    void addSolveOrder(AstNode* nodep) {
        std::map<uint32_t, uint32_t> stages;
        for (const std::pair<uint32_t, uint32_t>& before : m_befores) {
            stages[before.first] = 1;
            stages[before.second] = 1;
        }
        // Each pass lengthens the longest chain found by one; a chain longer than the
        // number of variables is a cycle
        for (size_t pass = 0; pass <= stages.size(); ++pass) {
            bool changed = false;
            for (const std::pair<uint32_t, uint32_t>& before : m_befores) {
                if (stages[before.second] <= stages[before.first]) {
                    stages[before.second] = stages[before.first] + 1;
                    changed = true;
                }
            }
            if (!changed) {
                for (const std::pair<const uint32_t, uint32_t>& stage : stages) {
                    UASSERT_OBJ(stage.second <= DVS_MAX_STAGE, nodep, "Too many stages");
                    dvs_builder_set_var_order(m_builderp, stage.first, stage.second);
                }
                return;
            }
        }
        unsupported(nodep, "circular 'solve before' ordering");
    }
    // Reference to a constant-pool array of the values
    static AstVarRef* newPoolArrayp(FileLine* fl, AstNodeDType* elemDTypep,
                                    const std::vector<AstConst*>& values) {
        AstUnpackArrayDType* const dtypep = new AstUnpackArrayDType{
            fl, elemDTypep, new AstRange{fl, static_cast<int>(values.size()) - 1, 0}};
        v3Global.rootp()->typeTablep()->addTypesp(dtypep);
        AstConsArray* const consp = new AstConsArray{fl, dtypep};
        for (size_t i = 0; i < values.size(); ++i) consp->valuep(i, values[i]);
        AstVarRef* const refp = V3ConstPool::find(consp);
        VL_DO_DANGLING(consp->deleteTree(), consp);  // V3ConstPool::find clones it
        return refp;
    }
    template <typename T_Value>
    static AstVarRef* newPoolArrayp(FileLine* fl, int width, const std::vector<T_Value>& values) {
        std::vector<AstConst*> constps;
        for (const T_Value value : values) {
            constps.push_back(
                new AstConst{fl, AstConst::WidthedValue{}, width, static_cast<uint32_t>(value)});
        }
        return newPoolArrayp(fl, v3Global.rootp()->findBitDType(width, width, VSigning::UNSIGNED),
                             constps);
    }
    static AstVarRef* newPoolArrayp(FileLine* fl, const std::vector<std::string>& values) {
        std::vector<AstConst*> constps;
        for (const std::string& value : values) {
            constps.push_back(new AstConst{fl, AstConst::String{}, value});
        }
        return newPoolArrayp(fl, v3Global.rootp()->findStringDType(), constps);
    }

public:
    // CONSTRUCTORS
    DvsProblemBuilder(const DvsSite& site, AstNodeFTask* funcp, bool ownVars)
        : m_site{site}
        , m_funcp{funcp}
        , m_ownVars{ownVars}
        , m_builderp{dvs_builder_create(0, nullptr)} {
        UASSERT(m_builderp, "dv-solve builder out of memory");
        dvs_builder_set_explicit(m_builderp);
        m_constraintInfos.push_back(location(site.flp));
    }
    ~DvsProblemBuilder() { dvs_builder_destroy(m_builderp); }

    // METHODS
    // The image of the problem of the site; empty if there is nothing to solve, or (m_failed)
    // if it is not supported
    std::vector<uint8_t> newImage() {
        AstClass* const classp = m_site.classp;
        // Where to report the site as a whole: its class, or the first inline constraint of
        // a std::randomize() with {...}
        AstNode* const sitep = classp ? classp : m_site.blocks.front().itemsp;
        if (m_site.part && !m_site.inlinePart) {
            if (slotCount(classp) > DVS_MAX_SLOTS) {
                unsupported(classp, "more than " + std::to_string(DVS_MAX_SLOTS)
                                        + " rand class handles in a class");
            }
            dvs_builder_set_n_slots(m_builderp, slotCount(classp));
            // Every slot array, used or not: an import through a slot reads it
            for (AstVar* const slotp : slots(classp)) {
                if (dvsIsSlotArray(slotp->dtypep())) slotArrayId(slotp);
            }
        }
        for (const DvsSite::Block& block : m_site.blocks) {
            if (!block.itemsp) continue;
            std::vector<Value> guards;
            if (block.modeVarp) guards.push_back(enable(block));
            addItems(block.itemsp, guards);
        }
        // A site part: the object, then the mirrors
        if (m_site.inlinePart) dvs_builder_set_n_slots(m_builderp, 1 + m_mirrors.size());
        if (m_nSofts > DVS_MAX_SOFTS) {
            unsupported(sitep, "more than " + std::to_string(DVS_MAX_SOFTS)
                                   + " soft constraints in one randomize() call");
        }
        if (!m_befores.empty()) addSolveOrder(sitep);
        // A variable that the constraints of another class named (a derived class, or
        // the class of the site, randomized before) is owned by a solver, so
        // __VBasicRand skips it: it is solved here too, unconstrained if nothing here names
        // it. (A variable that cannot be solved was reported where it was named.) A site part
        // solves none of the object's variables.
        if (classp && !m_site.checkOnly && !m_site.inlinePart) {
            classp->foreachMember([&](AstClass*, AstVar* varp) {
                if (!varp->user3() || !dvsRandVarUnsupported(varp).empty()) return;
                if (isDynArray(varp->dtypep())) {
                    randArrayId(varp);
                } else {
                    randVarId(varp);
                }
            });
        }
        if (m_site.part && !m_site.inlinePart) {
            // The exports, in layout order; only the variables the constraints name are owned
            m_ownVars = false;
            int expected = 0;
            classp->foreachMember([&](AstClass*, AstVar* varp) {
                if (!isLayoutVar(varp)) return;
                const uint32_t id = randVarId(varp);
                for (uint32_t i = 0; i < elementCount(varp->dtypep()); ++i) {
                    const int index = dvs_builder_add_export(m_builderp, id + i);
                    UASSERT_OBJ(index == expected++, varp, "Export out of layout order");
                }
            });
        }
        // Random sizes, at most the bound of a bounded queue (IEEE 1800-2023 7.10)
        if (!m_site.checkOnly) {
            for (const auto& it : m_arrayIds) {
                if (!m_sizedArrays.count(it.second)) continue;
                dvs_builder_set_array_size_random(m_builderp, it.second);
                const AstQueueDType* const qdtypep
                    = VN_CAST(it.first->dtypep()->skipRefp(), QueueDType);
                if (!qdtypep || !qdtypep->boundp()) continue;
                const Value size{dvs_builder_expr_array_size(m_builderp, it.second), 32, true,
                                 false};
                addHard(
                    binary(DVS_BIN_LTE, size, constant(qdtypep->boundConst() + 1, 32, true), true)
                        .expr,
                    it.first->fileline());
            }
        }
        // The values of enum variables, and of the elements of arrays of enums
        for (const EnumVar& var : m_enumVars) {
            if (var.arrayId >= 0) dvs_builder_foreach_begin(m_builderp, var.arrayId, 0);
            addHard(enumMember(var.value, var.enump).expr, var.flp);
            if (var.arrayId >= 0) dvs_builder_foreach_end(m_builderp);
        }
        if (m_varInfos.empty() && m_arrayInfos.empty()) {
            if (m_site.hasItems()) {
                unsupported(sitep, "constraints without variables");
            } else if (!m_site.part) {
                return {};
            }
        }
        if (m_varInfos.empty() || m_args.empty()) {
            // Only arrays, or only imports: a STATE placeholder, as the call passes one
            // variable at least
            AstConst* const zerop = new AstConst{m_site.flp, AstConst::BitFalse{}};
            stateValue(zerop);
            VL_DO_DANGLING(zerop->deleteTree(), zerop);
        }
        if (m_failed) return {};

        size_t size = 0;
        dvs_problem_t* const problemp = dvs_builder_finalize(m_builderp, &size);
        UASSERT_OBJ(problemp, sitep, "dv-solve builder out of memory");
        char why[256];
        const bool valid = !dvs_problem_validate(problemp, why, sizeof(why));
        const uint8_t* const bytesp = reinterpret_cast<const uint8_t*>(problemp);
        const std::vector<uint8_t> image{bytesp, bytesp + size};
        dvs_builder_free_problem(m_builderp, problemp, size);
        if (!valid) unsupported(sitep, "constraints dv-solve cannot solve ("s + why + ")");
        return image;
    }
    // The solver call of the site, or nullptr if it is not supported
    AstNodeExpr* newSolveCallp() {
        const std::vector<uint8_t> image = newImage();
        if (m_failed) return nullptr;
        if (image.empty()) return new AstConst{m_site.flp, AstConst::WidthedValue{}, 32, 1};
        FileLine* const flp = m_site.flp;
        AstCFuncHard* callp;
        if (m_site.stdrandp) {
            // VL_DVS_SOLVE_STD draws its seed from the std::randomize() generator
            callp = new AstCFuncHard{flp, VCFunction::DVS_SOLVE_STD,
                                     new AstVarRef{flp, m_site.stdrandp, VAccess::READWRITE}};
        } else {
            // VL_DVS_SOLVE draws its seed from the object's RNG
            callp = new AstCFuncHard{flp, VCFunction::DVS_SOLVE};
            m_site.classp->baseMostClassp()->needRNG(true);
        }
        callp->addPinsp(newPoolArrayp(flp, 8, image));
        // Each variable's width and signedness
        callp->addPinsp(newPoolArrayp(flp, 32, m_varInfos));
        callp->addPinsp(newPoolArrayp(flp, m_constraintInfos));
        for (const Arg& arg : m_args) callp->addPinsp(newArgRefp(flp, arg, VAccess::READWRITE));
        callp->dtypeSetBit();
        return callp;
    }
    // The call registering the part of the site's class, or nullptr if it is not supported
    AstNodeExpr* newPartCallp() {
        const std::vector<uint8_t> image = newImage();
        if (m_failed) return nullptr;
        AstClass* const classp = m_site.classp;
        FileLine* const flp = m_site.flp;
        AstCFuncHard* const callp = new AstCFuncHard{
            flp, m_site.inlinePart ? VCFunction::DVS_SITE_PART : VCFunction::DVS_PART,
            newPoolArrayp(flp, 8, image)};
        callp->addPinsp(newPoolArrayp(flp, 32, m_varInfos));
        callp->addPinsp(newPoolArrayp(flp, m_constraintInfos));
        AstClassRefDType* const refDTypep = new AstClassRefDType{flp, classp, nullptr};
        v3Global.rootp()->typeTablep()->addTypesp(refDTypep);
        // This object: that of the part, or for a site part the object randomized
        callp->addPinsp(new AstThisRef{flp, refDTypep});
        if (m_site.inlinePart) {
            for (const Arg& arg : m_args) {
                callp->addPinsp(newArgRefp(flp, arg, VAccess::READWRITE));
            }
            for (AstVar* const mirrorp : m_mirrors) {
                callp->addPinsp(newArgRefp(flp, {mirrorp, false}, VAccess::READWRITE));
            }
            callp->dtypeSetVoid();
            return callp;
        }
        // Bit k set: slot k is inactive, its handle's rand_mode() off (an array's, for each
        // element)
        AstNodeExpr* inactivep = new AstConst{flp, AstConst::Unsized64{}, 0};
        for (AstVar* const slotp : slots(classp)) {
            const RandomizeMode mode = {.asUQuad = slotp->user1()};
            if (!mode.usesMode) continue;
            const uint64_t bits = ((2ULL << (elementCount(slotp->dtypep()) - 1)) - 1)
                                  << slotIndex(classp, slotp);
            AstVar* const modeVarp = RandModeVars::randModeVarp(classp);
            AstCMethodHard* const atp = new AstCMethodHard{
                flp,
                new AstVarRef{flp, VN_AS(modeVarp->user2p(), NodeModule), modeVarp, VAccess::READ},
                VCMethod::ARRAY_AT, new AstConst{flp, mode.index}};
            atp->dtypeSetUInt32();
            AstCond* const condp = new AstCond{
                flp, new AstEq{flp, atp, new AstConst{flp, AstConst::WidthedValue{}, 32, 0}},
                new AstConst{flp, AstConst::Unsized64{}, bits},
                new AstConst{flp, AstConst::Unsized64{}, 0}};
            condp->dtypeSetUInt64();
            inactivep = new AstOr{flp, inactivep, condp};
            inactivep->dtypeSetUInt64();
        }
        callp->addPinsp(inactivep);
        for (const Arg& arg : m_args) callp->addPinsp(newArgRefp(flp, arg, VAccess::READWRITE));
        for (AstVar* const slotp : slots(classp)) {
            callp->addPinsp(newArgRefp(flp, {slotp, false}, VAccess::READWRITE));
        }
        callp->dtypeSetBit();
        return callp;
    }
};

}  // namespace

//######################################################################
// Interface

AstConst* dvsNewConstp(AstNodeExpr* nodep) {
    AstNodeExpr* const foldedp = V3Const::constifyEdit(nodep->cloneTree(false));
    if (AstConst* const constp = VN_CAST(foldedp, Const)) return constp;
    VL_DO_DANGLING(foldedp->deleteTree(), foldedp);
    return nullptr;
}

AstNodeExpr* dvsNewSolveCallp(const DvsSite& site, AstNodeFTask* funcp, bool ownVars) {
    if (!dvsSiteSupported(site)) return nullptr;
    return DvsProblemBuilder{site, funcp, ownVars}.newSolveCallp();
}

AstNodeExpr* dvsNewPartCallp(const DvsSite& site, AstNodeFTask* funcp, bool ownVars) {
    if (!dvsSiteSupported(site)) return nullptr;
    return DvsProblemBuilder{site, funcp, ownVars}.newPartCallp();
}

AstClass* dvsHandleClassp(const AstNodeDType* dtypep) {
    dtypep = dtypep->skipRefp();
    if (isDynArray(dtypep)) dtypep = dtypep->subDTypep()->skipRefp();
    while (const AstUnpackArrayDType* const adtypep = VN_CAST(dtypep, UnpackArrayDType)) {
        dtypep = adtypep->subDTypep()->skipRefp();
    }
    const AstClassRefDType* const refp = VN_CAST(dtypep, ClassRefDType);
    return refp ? refp->classp() : nullptr;
}

bool dvsIsSlotArray(const AstNodeDType* dtypep) {
    return isDynArray(dtypep) && VN_IS(dtypep->skipRefp()->subDTypep()->skipRefp(), ClassRefDType);
}

AstCMethodHard* dvsSlotNullComparep(const AstNodeExpr* nodep) {
    const AstNodeBiop* const biopp = VN_CAST(nodep, NodeBiop);
    if (!VN_IS(nodep, Eq) && !VN_IS(nodep, Neq)) return nullptr;
    for (AstNodeExpr* const opp : {biopp->lhsp(), biopp->rhsp()}) {
        AstCMethodHard* const atp = VN_CAST(opp, CMethodHard);
        const AstConst* const otherp
            = VN_CAST(opp == biopp->lhsp() ? biopp->rhsp() : biopp->lhsp(), Const);
        if (atp && atp->method() == VCMethod::ARRAY_AT && dvsIsSlotArray(atp->fromp()->dtypep())
            && otherp && otherp->num().isNull()) {
            return atp;
        }
    }
    return nullptr;
}

std::vector<AstVar*> dvsSlots(const AstClass* classp) {
    std::vector<AstVar*> slots;
    const_cast<AstClass*>(classp)->foreachMember([&](AstClass*, AstVar* varp) {
        if (varp->rand().isRandomizable() && !varp->lifetime().isStatic()
            && dvsHandleClassp(varp->dtypep())) {
            slots.push_back(varp);
        }
    });
    return slots;
}

bool dvsIsSlotPath(const AstNodeExpr* nodep) {
    while (true) {
        const AstCMethodHard* const atp = VN_CAST(nodep, CMethodHard);
        if (const AstArraySel* const selp = VN_CAST(nodep, ArraySel)) {
            nodep = selp->fromp();
        } else if (atp && atp->method() == VCMethod::ARRAY_AT) {
            nodep = atp->fromp();
        } else {
            break;
        }
    }
    const AstNodeVarRef* const refp = VN_CAST(nodep, NodeVarRef);
    const AstMemberSel* const selp = VN_CAST(nodep, MemberSel);
    const AstVar* const varp = refp ? refp->varp() : selp ? selp->varp() : nullptr;
    if (!varp || !varp->rand().isRandomizable() || varp->lifetime().isStatic()
        || !dvsHandleClassp(varp->dtypep())) {
        return false;
    }
    return refp ? varp->isClassMember() : dvsIsSlotPath(selp->fromp());
}

std::string dvsRandVarUnsupported(const AstVar* varp) {
    const RandomizeMode mode = {.asUQuad = varp->user1()};
    // An unpacked array is solved element by element, a dynamic array or queue as an array
    const AstNodeDType* dtypep = varp->dtypep()->skipRefp();
    if (VN_IS(dtypep, DynArrayDType) || VN_IS(dtypep, QueueDType)) {
        dtypep = dtypep->subDTypep()->skipRefp();  // Of scalars only
        if (VN_IS(dtypep, ClassRefDType)) return "dynamic array or queue of class handles";
    } else {
        while (const AstUnpackArrayDType* const adtypep = VN_CAST(dtypep, UnpackArrayDType)) {
            dtypep = adtypep->subDTypep()->skipRefp();
        }
    }
    if (varp->isRandC()) return "randc variable in a constraint";
    if (mode.usesMode) return "rand_mode() or randomize() arguments for a constrained variable";
    if (!VN_IS(dtypep, BasicDType) || !dtypep->isIntegralOrPacked()) {
        return "random variable of type " + dtypep->prettyDTypeNameQ();
    }
    if (dtypep->width() > VL_QUADSIZE) return "random variable wider than 64 bits";
    return "";
}

bool dvsIsMappable(const AstNodeExpr* nodep) {
    if (const AstCMethodHard* const callp = VN_CAST(nodep, CMethodHard)) {
        const AstNodeDType* const fromDTypep = callp->fromp()->dtypep()->skipRefp();
        if (callp->method() == VCMethod::ARRAY_AT || callp->method() == VCMethod::DYN_SIZE) {
            return VN_IS(fromDTypep, DynArrayDType) || VN_IS(fromDTypep, QueueDType);
        }
        return callp->method() == VCMethod::ARRAY_INSIDE
               || callp->method() == VCMethod::ARRAY_R_AND
               || callp->method() == VCMethod::ARRAY_R_OR
               || callp->method() == VCMethod::ARRAY_R_PRODUCT
               || callp->method() == VCMethod::ARRAY_R_SUM
               || callp->method() == VCMethod::ARRAY_R_XOR;
    }
    switch (nodep->type()) {
    case VNType::Add:
    case VNType::And:
    case VNType::ArraySel:
    case VNType::Concat:
    case VNType::Cond:
    case VNType::Const:
    case VNType::Div:
    case VNType::DivS:
    case VNType::Eq:
    case VNType::EqCase:
    case VNType::EqWild:
    case VNType::Extend:
    case VNType::ExtendS:
    case VNType::Gt:
    case VNType::GtS:
    case VNType::Gte:
    case VNType::GteS:
    case VNType::LambdaArgRef:
    case VNType::LogAnd:
    case VNType::LogEq:
    case VNType::LogIf:
    case VNType::LogNot:
    case VNType::LogOr:
    case VNType::Lt:
    case VNType::LtS:
    case VNType::Lte:
    case VNType::LteS:
    case VNType::ModDiv:
    case VNType::ModDivS:
    case VNType::Mul:
    case VNType::MulS:
    case VNType::Negate:
    case VNType::Neq:
    case VNType::NeqCase:
    case VNType::NeqWild:
    case VNType::Not:
    case VNType::Or:
    case VNType::RedAnd:
    case VNType::RedOr:
    case VNType::Replicate:
    case VNType::Sel:
    case VNType::ShiftL:
    case VNType::ShiftR:
    case VNType::ShiftRS:
    case VNType::Sub:
    case VNType::VarRef:
    case VNType::Xor: return true;
    default: return false;
    }
}

#endif  // HAVE_DV_SOLVE
