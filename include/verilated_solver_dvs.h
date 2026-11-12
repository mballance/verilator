// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************
///
/// \file
/// \brief Verilated randomization with the dv-solve library (--solver-dvs)
///
/// This file is included automatically by Verilator in some of the C++ files
/// it generates if randomization features are used with --solver-dvs.
///
/// This file is not part of the Verilated public-facing API.
/// It is only for internal use.
///
//*************************************************************************
#ifndef VERILATOR_VERILATED_SOLVER_DVS_H_
#define VERILATOR_VERILATED_SOLVER_DVS_H_

// The front end of randomization (VlStdRandomizer, __VBasicRand) is solver-neutral
#include "verilated_random.h"

//=============================================================================
// VlDvsArray

/// A dynamic array or queue argument of VL_DVS_SOLVE: a problem array, whose elements
/// dv-solve reads and writes as a packed buffer of elemBytes each
struct VlDvsArray final {
    void* queuep;  // The VlQueue
    std::size_t elemBytes;  // sizeof its element
    std::size_t (*size)(const void* queuep);
    // Copy the first n elements into a packed buffer, as many as there are
    void (*read)(void* queuep, void* datap, std::size_t n);
    // Resize to n elements (at the back, IEEE 1800-2023 18.4) and copy them from a buffer
    void (*write)(void* queuep, const void* datap, std::size_t n);
};

//=============================================================================
// VlDvsSlot

/// A slot argument of VL_DVS_PART: a class handle, or a dynamic array or queue of them (a slot
/// array)
struct VlDvsSlot final {
    const void* objp;  // A handle: its object, or nullptr
    void* queuep = nullptr;  // A slot array: the VlQueue; else nullptr
    std::size_t (*size)(const void* queuep) = nullptr;
    const void* (*elem)(const void* queuep, std::size_t i) = nullptr;  // Object, or nullptr
    void (*resize)(void* queuep, std::size_t n) = nullptr;  // New handles are null
};

//=============================================================================
// VlDvsSite

/// Solving of the dv-solve problems of a model. Each randomize site is a problem
/// image, a constant of the generated model, and it is opened on its first solve.
class VlDvsSite final {
public:
    /// Solve the problem 'imagep' of 'size' bytes once, seeded from 'rng'. Variable i of
    /// the problem is at varps[i]; infos[i] holds its width in bits 30:0, and bit 31 is set
    /// if it is signed. 'constraints' holds the location of the site, then the location and
    /// source text of each hard constraint, 'nConstraints' strings in all. Array i of the
    /// problem is arrays[i], of nArrays. On success write the random variables and return
    /// true; otherwise write nothing, warn, and return false.
    static bool solve(VlRNG& rng, const CData* imagep, size_t size, const IData* infos,
                      const std::string* constraints, size_t nConstraints, void* const* varps,
                      const VlDvsArray* arrays, size_t nArrays);
};

//=============================================================================
// VlDvsParts

/// Solving of the parts of the objects reached from one object (IEEE 1800-2023 18.5.8):
/// begin(), then VL_DVS_PART for each object, then solve().
class VlDvsParts final {
public:
    /// Start a solve of this thread: the parts added until the next solve() belong to it.
    /// Solves nest, a solve of another object may start before this one is solved.
    static void begin();
    /// Add the part of the object at objp, unless it is added already; return if it was
    /// added. The arguments are as for VlDvsSite::solve, except that variable i of the
    /// problem is not passed if bit 30 of infos[i] is set (an import), the arrays are those
    /// that are not slot arrays, and slot k of the part is slots[k], inactive (each element
    /// of a slot array) if bit k of 'inactive' is set.
    static bool add(const void* objp, const CData* imagep, size_t size, const IData* infos,
                    const std::string* constraints, size_t nConstraints, QData inactive,
                    void* const* varps, size_t nVarps, const VlDvsArray* arrays, size_t nArrays,
                    const VlDvsSlot* slots, size_t nSlots);
    /// Solve the parts added since begin(), the first the object randomized, seeded from
    /// 'rng'; as VlDvsSite::solve.
    static bool solve(VlRNG& rng);
};

/// The problem variables, arrays and slots of an argument of VL_DVS_SOLVE or VL_DVS_PART:
/// a scalar is one variable
template <typename T_Var>
struct VlDvsVars final {
    static constexpr std::size_t count = 1;
    static constexpr std::size_t arrays = 0;
    static constexpr std::size_t slots = 0;
    static void addrs(T_Var& var, void**& varpr, VlDvsArray*&, VlDvsSlot*&) { *varpr++ = &var; }
};
/// A class handle is a slot, identified by the address of its object
template <typename T_Class>
struct VlDvsVars<VlClassRef<T_Class>> final {
    static constexpr std::size_t count = 0;
    static constexpr std::size_t arrays = 0;
    static constexpr std::size_t slots = 1;
    static const void* objp(const VlClassRef<T_Class>& var) {
        return var ? dynamic_cast<const void*>(var.operator->()) : nullptr;
    }
    static void addrs(VlClassRef<T_Class>& var, void**&, VlDvsArray*&, VlDvsSlot*& slotr) {
        *slotr++ = VlDvsSlot{objp(var)};
    }
};
/// A dynamic array or queue of class handles is a slot array
template <typename T_Class, std::size_t N_MaxSize>
struct VlDvsVars<VlQueue<VlClassRef<T_Class>, N_MaxSize>> final {
    using Queue = VlQueue<VlClassRef<T_Class>, N_MaxSize>;
    static constexpr std::size_t count = 0;
    static constexpr std::size_t arrays = 0;
    static constexpr std::size_t slots = 1;
    static std::size_t size(const void* queuep) {
        return static_cast<const Queue*>(queuep)->size();
    }
    static const void* elem(const void* queuep, std::size_t i) {
        return VlDvsVars<VlClassRef<T_Class>>::objp(
            static_cast<const Queue*>(queuep)->at(static_cast<int32_t>(i)));
    }
    static void resize(void* queuep, std::size_t n) { static_cast<Queue*>(queuep)->resize(n); }
    static void addrs(Queue& var, void**&, VlDvsArray*&, VlDvsSlot*& slotr) {
        *slotr++ = VlDvsSlot{nullptr, &var, size, elem, resize};
    }
};
/// An unpacked array is one variable (or slot) per element, in storage order
template <typename T_Elem, std::size_t N_Depth>
struct VlDvsVars<VlUnpacked<T_Elem, N_Depth>> final {
    static constexpr std::size_t count = N_Depth * VlDvsVars<T_Elem>::count;
    static constexpr std::size_t arrays = 0;
    static constexpr std::size_t slots = N_Depth * VlDvsVars<T_Elem>::slots;
    static void addrs(VlUnpacked<T_Elem, N_Depth>& var, void**& varpr, VlDvsArray*& arrayr,
                      VlDvsSlot*& slotr) {
        for (std::size_t i = 0; i < N_Depth; ++i) {
            VlDvsVars<T_Elem>::addrs(var[i], varpr, arrayr, slotr);
        }
    }
};
/// A dynamic array or queue is one problem array
template <typename T_Elem, std::size_t N_MaxSize>
struct VlDvsVars<VlQueue<T_Elem, N_MaxSize>> final {
    using Queue = VlQueue<T_Elem, N_MaxSize>;
    static constexpr std::size_t count = 0;
    static constexpr std::size_t arrays = 1;
    static constexpr std::size_t slots = 0;
    static std::size_t size(const void* queuep) {
        return static_cast<const Queue*>(queuep)->size();
    }
    static void read(void* queuep, void* datap, std::size_t n) {
        Queue& queue = *static_cast<Queue*>(queuep);
        for (std::size_t i = 0; i < n && i < static_cast<std::size_t>(queue.size()); ++i) {
            static_cast<T_Elem*>(datap)[i] = queue.atWrite(i);
        }
    }
    static void write(void* queuep, const void* datap, std::size_t n) {
        Queue& queue = *static_cast<Queue*>(queuep);
        if (n != static_cast<std::size_t>(queue.size())) queue.resize(n);
        for (std::size_t i = 0; i < n; ++i) {
            queue.atWrite(i) = static_cast<const T_Elem*>(datap)[i];
        }
    }
    static void addrs(Queue& var, void**&, VlDvsArray*& arrayr, VlDvsSlot*&) {
        *arrayr++ = VlDvsArray{&var, sizeof(T_Elem), size, read, write};
    }
};
template <typename... T_Vars>
constexpr std::size_t vlDvsCount() {
    const std::size_t counts[] = {0, VlDvsVars<T_Vars>::count...};
    std::size_t total = 0;
    for (const std::size_t count : counts) total += count;
    return total;
}
template <typename... T_Vars>
constexpr std::size_t vlDvsArrays() {
    const std::size_t counts[] = {0, VlDvsVars<T_Vars>::arrays...};
    std::size_t total = 0;
    for (const std::size_t count : counts) total += count;
    return total;
}
template <typename... T_Vars>
constexpr std::size_t vlDvsSlots() {
    const std::size_t counts[] = {0, VlDvsVars<T_Vars>::slots...};
    std::size_t total = 0;
    for (const std::size_t count : counts) total += count;
    return total;
}

/// Solve the problem of a randomize site, see VlDvsSite::solve
template <std::size_t N_Image, std::size_t N_Infos, std::size_t N_Constraints, typename... T_Vars>
bool VL_DVS_SOLVE_RNG(VlRNG& rng, const VlUnpacked<CData, N_Image>& image,
                      const VlUnpacked<IData, N_Infos>& infos,
                      const VlUnpacked<std::string, N_Constraints>& constraints, T_Vars&... vars) {
    static_assert(vlDvsCount<T_Vars...>() == N_Infos, "One entry per variable");
    static_assert(vlDvsSlots<T_Vars...>() == 0, "No slots");
    constexpr std::size_t nArrays = vlDvsArrays<T_Vars...>();
    void* varps[N_Infos + 1];  // + 1: no zero-length arrays
    void** varpr = varps;
    VlDvsArray arrays[nArrays + 1];
    VlDvsArray* arrayr = arrays;
    VlDvsSlot* slotr = nullptr;
    // Braced initializers are evaluated in order, so arguments fill varps and arrays in order
    (void)std::initializer_list<int>{(VlDvsVars<T_Vars>::addrs(vars, varpr, arrayr, slotr), 0)...};
    return VlDvsSite::solve(rng, image.data(), N_Image, infos.data(), constraints.data(),
                            N_Constraints, varps, arrays, nArrays);
}

/// Solve the problem of a randomize site of a class, using the RNG of the object
#define VL_DVS_SOLVE(...) VL_DVS_SOLVE_RNG(__Vm_rng, __VA_ARGS__)

/// Solve the problem of a std::randomize() with {...} site, seeded from the generator of
/// std::randomize() 'stdrand'
template <std::size_t N_Image, std::size_t N_Infos, std::size_t N_Constraints, typename... T_Vars>
bool VL_DVS_SOLVE_STD(VlStdRandomizer& stdrand, const VlUnpacked<CData, N_Image>& image,
                      const VlUnpacked<IData, N_Infos>& infos,
                      const VlUnpacked<std::string, N_Constraints>& constraints, T_Vars&... vars) {
    QData seed;
    stdrand.basicStdRandomization(seed, VL_QUADSIZE);
    VlRNG rng{seed};
    return VL_DVS_SOLVE_RNG(rng, image, infos, constraints, vars...);
}

/// Add the part of the object at objp, see VlDvsParts::add; the arguments are its variables
/// (but its imports), arrays and slots
template <std::size_t N_Image, std::size_t N_Infos, std::size_t N_Constraints, typename... T_Vars>
bool vlDvsAddPart(const void* objp, const VlUnpacked<CData, N_Image>& image,
                  const VlUnpacked<IData, N_Infos>& infos,
                  const VlUnpacked<std::string, N_Constraints>& constraints, QData inactive,
                  T_Vars&... vars) {
    constexpr std::size_t nVars = vlDvsCount<T_Vars...>();
    constexpr std::size_t nArrays = vlDvsArrays<T_Vars...>();
    constexpr std::size_t nSlots = vlDvsSlots<T_Vars...>();
    void* varps[nVars + 1];  // + 1: no zero-length arrays
    void** varpr = varps;
    VlDvsArray arrays[nArrays + 1];
    VlDvsArray* arrayr = arrays;
    VlDvsSlot slots[nSlots + 1];
    VlDvsSlot* slotr = slots;
    (void)std::initializer_list<int>{(VlDvsVars<T_Vars>::addrs(vars, varpr, arrayr, slotr), 0)...};
    return VlDvsParts::add(objp, image.data(), N_Image, infos.data(), constraints.data(),
                           N_Constraints, inactive, varps, nVars, arrays, nArrays, slots, nSlots);
}

/// Add the part of the object 'self', see vlDvsAddPart
template <std::size_t N_Image, std::size_t N_Infos, std::size_t N_Constraints, typename T_Class,
          typename... T_Vars>
bool VL_DVS_PART(const VlUnpacked<CData, N_Image>& image, const VlUnpacked<IData, N_Infos>& infos,
                 const VlUnpacked<std::string, N_Constraints>& constraints,
                 const VlClassRef<T_Class>& self, QData inactive, T_Vars&... vars) {
    return vlDvsAddPart(dynamic_cast<const void*>(self.operator->()), image, infos, constraints,
                        inactive, vars...);
}

/// Add the site part of a randomize() with {...} on the object 'target', its slot 0, see
/// vlDvsAddPart. Its site is its identity, as it is no object. Its other slots are the slot
/// arrays of the object it iterates, inactive: the object's own reach their objects.
template <std::size_t N_Image, std::size_t N_Infos, std::size_t N_Constraints, typename T_Class,
          typename... T_Vars>
void VL_DVS_SITE_PART(const VlUnpacked<CData, N_Image>& image,
                      const VlUnpacked<IData, N_Infos>& infos,
                      const VlUnpacked<std::string, N_Constraints>& constraints,
                      const VlClassRef<T_Class>& target, T_Vars&... vars) {
    VlClassRef<T_Class> slot = target;
    vlDvsAddPart(image.data(), image, infos, constraints, ~QData{1}, slot, vars...);
}

/// Start a solve of the parts of objects, see VlDvsParts::begin
#define VL_DVS_PARTS_BEGIN() VlDvsParts::begin()
/// Solve the parts added since VL_DVS_PARTS_BEGIN, using the RNG of the object
#define VL_DVS_SOLVE_PARTS() VlDvsParts::solve(__Vm_rng)

#endif  // Guard
