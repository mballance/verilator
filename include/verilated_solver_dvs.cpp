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
/// A problem image is opened as a dv-solve handle on its first solve. The
/// handles are kept for the life of the process, keyed by the address of the
/// image: each image is a constant of the generated model, so its address
/// identifies its randomize site, without any per-site object in the model.
///
/// A solve across objects collects the part of each object in a VlDvsParts
/// context of the thread, and solves them with dvs_randomize_parts().
///
//*************************************************************************

#include "verilated_solver_dvs.h"

#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <deque>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <dv_solve/dv_solve.h>

//======================================================================
// VlDvsHandles

// Handles of the problem images solved so far, and the solver log
class VlDvsHandles final {
public:
    // TYPES
    struct Handle final {
        VerilatedMutex m_mutex;  // Serializes solves: a dv-solve handle is not reentrant
        dvs_handle_t* const m_handlep;  // The dv-solve handle
        bool m_nullWarned = false;  // Warned of a read through a null handle, as a root part
        explicit Handle(dvs_handle_t* handlep)
            : m_handlep{handlep} {}
        ~Handle() { dvs_handle_free(m_handlep); }
    };

private:
    // MEMBERS
    VerilatedMutex m_mutex;  // Protects m_handles
    std::unordered_map<const CData*, std::unique_ptr<Handle>> m_handles VL_GUARDED_BY(m_mutex);
    // Serializes solves across objects, whose parts' handles are used together
    VerilatedMutex m_partsMutex;
    VerilatedMutex m_logMutex;  // Protects m_logfp; taken after a Handle::m_mutex
    FILE* m_logfp VL_GUARDED_BY(m_logMutex) = nullptr;  // +verilator+solver+file+ log

    // METHODS
    // The value of a problem variable
    static uint64_t value(const void* varp, uint32_t width) {
        if (width <= 8) return *static_cast<const CData*>(varp);
        if (width <= 16) return *static_cast<const SData*>(varp);
        if (width <= 32) return *static_cast<const IData*>(varp);
        return *static_cast<const QData*>(varp);
    }

public:
    // Log one solve as SMT-LIB2, with the seed, result and values after it; a solve of
    // nParts parts as its seed and result only
    void log(const CData* imagep, size_t size, const dvs_ref_t* refs, uint32_t nVars,
             uint32_t nArrays, uint64_t seed, int result, size_t nParts = 0)
        VL_MT_SAFE_EXCLUDES(m_logMutex) {
        const std::string filename = Verilated::threadContextp()->solverLogFilename();
        if (VL_LIKELY(filename.empty())) return;
        const VerilatedLockGuard lock{m_logMutex};
        if (!m_logfp) {
            m_logfp = std::fopen(filename.c_str(), "w");
            if (!m_logfp) {
                const std::string msg = "%Error: Can't write '" + filename + "'";
                VL_FATAL_MT("", 0, "", msg.c_str());
                return;
            }
            std::fputs("# Verilator solver log\n", m_logfp);
        }
        const std::string timeStr = Verilated::threadContextp()->timeWithUnitString();
        std::fprintf(m_logfp, "# [%s]\n", timeStr.c_str());
        if (nParts) {
            std::fprintf(m_logfp, "; a problem of %zu objects\n; seed %" PRIu64 ", result %d\n",
                         nParts, static_cast<uint64_t>(seed), result);
            std::fflush(m_logfp);
            return;
        }
        // The image of the model need not be aligned as the problem is
        std::vector<uint64_t> problem((size + sizeof(uint64_t) - 1) / sizeof(uint64_t));
        std::memcpy(problem.data(), imagep, size);
        if (nArrays) {
            // SMT-LIB2 has no arrays of a size given per call
            std::fprintf(m_logfp, "; a problem with %u arrays\n", nArrays);
        } else {
            dvs_problem_write_smt2(reinterpret_cast<const dvs_problem_t*>(problem.data()),
                                   m_logfp);
        }
        std::fprintf(m_logfp, "; seed %" PRIu64 ", result %d\n", static_cast<uint64_t>(seed),
                     result);
        for (uint32_t i = 0; i < nVars; ++i) {
            std::fprintf(m_logfp, "; v%u = 0x%" PRIx64 "\n", i,
                         static_cast<uint64_t>(value(refs[i].addr, refs[i].width)));
        }
        std::fflush(m_logfp);
    }

    ~VlDvsHandles() {
        if (m_logfp) std::fclose(m_logfp);
    }
    static VlDvsHandles& instance() VL_MT_SAFE {
        static VlDvsHandles s_handles;
        return s_handles;
    }
    // The handle of image, opened on first use
    Handle& handle(const CData* imagep, size_t size) VL_MT_SAFE_EXCLUDES(m_mutex) {
        const VerilatedLockGuard lock{m_mutex};
        std::unique_ptr<Handle>& handlepr = m_handles[imagep];
        if (VL_UNLIKELY(!handlepr)) {
            dvs_handle_t* const handlep = dvs_handle_new(imagep, size);
            // dv-solve checks the image, including its format version
            if (VL_UNLIKELY(!handlep)) {
                VL_FATAL_MT("", 0, "",
                            "dv-solve cannot open the problem of a randomize site; re-verilate"
                            " the model with the dv-solve it links");
            }
            handlepr.reset(new Handle{handlep});
        }
        return *handlepr;
    }
    bool solve(VlRNG& rng, const CData* imagep, size_t size, const IData* infos,
               const std::string* constraints, size_t nConstraints, void* const* varps,
               const VlDvsArray* arrays, size_t nArrays) {
        Handle& handle = this->handle(imagep, size);
        const VerilatedLockGuard lock{handle.m_mutex};
        const uint32_t nVars = dvs_handle_n_vars(handle.m_handlep);
        if (VL_UNLIKELY(dvs_handle_n_arrays(handle.m_handlep) != nArrays)) {
            VL_FATAL_MT("", 0, "",
                        "dv-solve cannot open the problem of a randomize site; re-verilate"
                        " the model with the dv-solve it links");
        }
        std::vector<dvs_ref_t> refs(nVars);
        for (uint32_t i = 0; i < nVars; ++i) {
            refs[i].addr = varps[i];
            refs[i].width = infos[i] & ~(1U << 31);
            refs[i].is_signed = infos[i] >> 31;
            refs[i].layout = DVS_REF_SCALAR;
        }
        // dv-solve takes a seed of 0 as deterministic, without diversity sampling
        uint64_t seed = rng.rand64();
        if (VL_UNLIKELY(!seed)) seed = 1;
        int result;
        if (!nArrays) {
            result = dvs_randomize(handle.m_handlep, refs.data(), nullptr, seed);
        } else {
            // The sizes first (IEEE 1800-2023 18.5.8.1): a random one is solved, any other
            // kept. Then each array is solved at its size, in a packed copy of its elements,
            // and written back, resized, only if both succeed
            std::vector<uint32_t> sizes(nArrays);
            for (size_t i = 0; i < nArrays; ++i) {
                sizes[i] = static_cast<uint32_t>(arrays[i].size(arrays[i].queuep));
            }
            result = dvs_randomize_sizes(handle.m_handlep, refs.data(), sizes.data(), seed);
            std::vector<std::vector<uint8_t>> datas(nArrays);
            std::vector<dvs_array_ref_t> arrayRefs(nArrays);
            for (size_t i = 0; i < nArrays && result == DVS_RANDOMIZE_OK; ++i) {
                datas[i].resize(sizes[i] * arrays[i].elemBytes + 1);
                arrays[i].read(arrays[i].queuep, datas[i].data(), sizes[i]);
                arrayRefs[i].data = datas[i].data();
                arrayRefs[i].n_elems = sizes[i];
            }
            if (result == DVS_RANDOMIZE_OK) {
                result = dvs_randomize_arrays(handle.m_handlep, refs.data(), arrayRefs.data(),
                                              nullptr, seed);
            }
            if (result == DVS_RANDOMIZE_OK) {
                for (size_t i = 0; i < nArrays; ++i) {
                    arrays[i].write(arrays[i].queuep, datas[i].data(), sizes[i]);
                }
            }
        }
        log(imagep, size, refs.data(), nVars, static_cast<uint32_t>(nArrays), seed, result);
        return report(result, constraints, nConstraints, nullptr);
    }
    // Warn of a failed solve of a site; return if it succeeded. For a solve across objects,
    // 'parts' gives the constraints of each part, the first that of the site
    static bool report(int result, const std::string* constraints, size_t nConstraints,
                       const std::vector<std::pair<const std::string*, size_t>>* partsp) {
        if (VL_LIKELY(result == DVS_RANDOMIZE_OK)) return true;
        if (result == DVS_RANDOMIZE_TOO_LARGE) {
            const std::string msg = "dv-solve could not solve the constraints of the"
                                    " randomize() call at "
                                    + constraints[0]
                                    + ": an array size over 65535, arrays too large to"
                                      " solve together, or more than 4096 objects";
            VL_WARN_MT("", 0, "", msg.c_str());
            return false;
        }
        if (result != DVS_RANDOMIZE_UNSAT) {
            const std::string msg = "dv-solve could not solve the constraints of the"
                                    " randomize() call at "
                                    + constraints[0];
            VL_WARN_MT("", 0, "", msg.c_str());
            return false;
        }
        // There is no unsat core yet: list all the hard constraints of the site
        std::string msg
            = "UNSATCONSTR: " + constraints[0] + ": Unsatisfied constraints in randomize() call";
        VL_WARN_MT("", 0, "", msg.c_str());
        const std::vector<std::pair<const std::string*, size_t>> site{{constraints, nConstraints}};
        for (const auto& part : partsp ? *partsp : site) {
            for (size_t i = 1; i + 1 < part.second; i += 2) {
                msg = "UNSATCONSTR: " + part.first[i] + ": Unsatisfied constraint";
                if (!part.first[i + 1].empty()) msg += ": '" + part.first[i + 1] + "'";
                VL_WARN_MT("", 0, "", msg.c_str());
            }
        }
        return false;
    }
    VerilatedMutex& partsMutex() VL_RETURN_CAPABILITY(m_partsMutex) { return m_partsMutex; }
};

//======================================================================
// VlDvsSite

bool VlDvsSite::solve(VlRNG& rng, const CData* imagep, size_t size, const IData* infos,
                      const std::string* constraints, size_t nConstraints, void* const* varps,
                      const VlDvsArray* arrays, size_t nArrays) {
    return VlDvsHandles::instance().solve(rng, imagep, size, infos, constraints, nConstraints,
                                          varps, arrays, nArrays);
}

//======================================================================
// VlDvsParts

namespace {

// Information of a problem variable: an import, passed no argument
constexpr IData VL_DVS_INFO_IMPORT = 1U << 30;
constexpr IData VL_DVS_INFO_WIDTH = VL_DVS_INFO_IMPORT - 1;

// The part of one object
struct VlDvsPart final {
    VlDvsHandles::Handle* handlep;  // Of its problem
    const std::string* constraints;  // Its location, then that and source of each constraint
    size_t nConstraints;
    QData inactive;  // Bit k: slot k is inactive
    std::vector<dvs_ref_t> refs;  // Of each problem variable
    std::vector<VlDvsArray> arrays;  // Of each problem array but the slot arrays
    std::vector<VlDvsSlot> slots;
};

// The parts of one solve across objects, the first the object randomized
struct VlDvsPartsContext final {
    std::vector<VlDvsPart> parts;
    std::unordered_map<const void*, size_t> index;  // Part of each object
};

// Solves of this thread begun and not yet solved, innermost last
thread_local std::vector<VlDvsPartsContext> t_dvsPartsStack;

}  // namespace

void VlDvsParts::begin() { t_dvsPartsStack.emplace_back(); }

bool VlDvsParts::add(const void* objp, const CData* imagep, size_t size, const IData* infos,
                     const std::string* constraints, size_t nConstraints, QData inactive,
                     void* const* varps, size_t nVarps, const VlDvsArray* arrays, size_t nArrays,
                     const VlDvsSlot* slots, size_t nSlots) {
    VlDvsPartsContext& context = t_dvsPartsStack.back();
    if (!context.index.emplace(objp, context.parts.size()).second) return false;
    VlDvsHandles::Handle& handle = VlDvsHandles::instance().handle(imagep, size);
    const uint32_t nVars = dvs_handle_n_vars(handle.m_handlep);
    VlDvsPart part{&handle,
                   constraints,
                   nConstraints,
                   inactive,
                   std::vector<dvs_ref_t>(nVars),
                   std::vector<VlDvsArray>(arrays, arrays + nArrays),
                   std::vector<VlDvsSlot>(slots, slots + nSlots)};
    size_t nPassed = 0;
    for (uint32_t i = 0; i < nVars; ++i) {
        dvs_ref_t& ref = part.refs[i];
        ref.width = infos[i] & VL_DVS_INFO_WIDTH;
        ref.is_signed = infos[i] >> 31;
        ref.layout = DVS_REF_SCALAR;
        if (!(infos[i] & VL_DVS_INFO_IMPORT) && nPassed < nVarps) ref.addr = varps[nPassed++];
    }
    size_t nSlotArrays = 0;
    for (uint32_t i = 0; i < dvs_handle_n_arrays(handle.m_handlep); ++i) {
        nSlotArrays += dvs_handle_array_slot(handle.m_handlep, i) != DVS_NO_SLOT;
    }
    if (VL_UNLIKELY(nPassed != nVarps
                    || dvs_handle_n_arrays(handle.m_handlep) != nArrays + nSlotArrays
                    || dvs_handle_n_slots(handle.m_handlep) != nSlots)) {
        VL_FATAL_MT("", 0, "",
                    "dv-solve cannot open the problem of a randomize site; re-verilate"
                    " the model with the dv-solve it links");
    }
    context.parts.push_back(std::move(part));
    return true;
}

bool VlDvsParts::solve(VlRNG& rng) {
    const VlDvsPartsContext context = std::move(t_dvsPartsStack.back());
    t_dvsPartsStack.pop_back();
    VlDvsHandles& handles = VlDvsHandles::instance();
    const VerilatedLockGuard lock{handles.partsMutex()};
    const size_t nParts = context.parts.size();
    std::vector<dvs_part_t> parts(nParts);
    std::vector<std::vector<dvs_slot_t>> slots(nParts);
    std::deque<std::vector<dvs_slot_t>> elems;  // Of each slot array
    std::vector<std::vector<dvs_array_ref_t>> arrayRefs(nParts);
    // Of each problem array: its argument, or for a slot array nullptr and its slot
    std::vector<std::vector<std::pair<const VlDvsArray*, const VlDvsSlot*>>> arrayArgs(nParts);
    std::vector<std::pair<const std::string*, size_t>> constraints;
    bool hasArrays = false;
    for (size_t i = 0; i < nParts; ++i) {
        const VlDvsPart& part = context.parts[i];
        for (size_t k = 0; k < part.slots.size(); ++k) {
            const VlDvsSlot& vslot = part.slots[k];
            // The object of a non-null handle added its part after this one
            const auto slotOf = [&](const void* objp) {
                dvs_slot_t slot{};
                if (objp) {
                    slot.state = (part.inactive >> k) & 1 ? DVS_SLOT_INACTIVE : DVS_SLOT_ACTIVE;
                    slot.child = &parts[context.index.at(objp)];
                }
                return slot;
            };
            if (!vslot.queuep) {
                slots[i].push_back(slotOf(vslot.objp));
                continue;
            }
            elems.emplace_back();
            for (size_t e = 0; e < vslot.size(vslot.queuep); ++e) {
                elems.back().push_back(slotOf(vslot.elem(vslot.queuep, e)));
            }
            slots[i].push_back(dvs_slot_t{0, static_cast<uint32_t>(elems.back().size()), nullptr,
                                          elems.back().data()});
        }
        dvs_handle_t* const handlep = part.handlep->m_handlep;
        auto argIt = part.arrays.begin();
        for (uint32_t a = 0; a < dvs_handle_n_arrays(handlep); ++a) {
            const uint32_t k = dvs_handle_array_slot(handlep, a);
            const VlDvsArray* const arrayp = k == DVS_NO_SLOT ? &*argIt++ : nullptr;
            const VlDvsSlot* const slotp = arrayp ? nullptr : &part.slots[k];
            arrayRefs[i].push_back({nullptr,
                                    static_cast<uint32_t>(arrayp ? arrayp->size(arrayp->queuep)
                                                                 : slotp->size(slotp->queuep)),
                                    0});
            arrayArgs[i].emplace_back(arrayp, slotp);
            hasArrays = true;
        }
        parts[i].handle = part.handlep->m_handlep;
        parts[i].refs = part.refs.data();
        parts[i].arrays = arrayRefs[i].data();
        parts[i].slots = slots[i].data();
        constraints.emplace_back(part.constraints, part.nConstraints);
    }
    // dv-solve takes a seed of 0 as deterministic, without diversity sampling
    uint64_t seed = rng.rand64();
    if (VL_UNLIKELY(!seed)) seed = 1;
    // As VlDvsSite::solve: the sizes first, then the elements, written back on success only
    int result = hasArrays ? dvs_randomize_parts_sizes(&parts[0], seed) : DVS_RANDOMIZE_OK;
    // A slot array's new size is that of each slot array of the same queue: a site part's
    // mirror of the object's
    std::map<const void*, uint32_t> newSizes;
    for (int pass = 0; pass < 2; ++pass) {
        for (size_t i = 0; i < nParts; ++i) {
            for (size_t j = 0; j < arrayArgs[i].size(); ++j) {
                const VlDvsSlot* const slotp = arrayArgs[i][j].second;
                if (!slotp) continue;
                uint32_t& n = arrayRefs[i][j].n_elems;
                if (pass && newSizes.count(slotp->queuep)) {
                    n = newSizes[slotp->queuep];
                } else if (!pass && n != slotp->size(slotp->queuep)) {
                    newSizes[slotp->queuep] = n;
                }
            }
        }
    }
    std::vector<std::vector<std::vector<uint8_t>>> datas(nParts);
    for (size_t i = 0; i < nParts && result == DVS_RANDOMIZE_OK; ++i) {
        for (size_t j = 0; j < arrayArgs[i].size(); ++j) {
            const VlDvsArray* const arrayp = arrayArgs[i][j].first;
            datas[i].emplace_back(arrayp ? arrayRefs[i][j].n_elems * arrayp->elemBytes + 1 : 0);
            if (!arrayp) continue;
            arrayp->read(arrayp->queuep, datas[i][j].data(), arrayRefs[i][j].n_elems);
            arrayRefs[i][j].data = datas[i][j].data();
        }
    }
    if (result == DVS_RANDOMIZE_OK) result = dvs_randomize_parts(&parts[0], seed);
    if (result == DVS_RANDOMIZE_OK) {
        for (size_t i = 0; i < nParts; ++i) {
            for (size_t j = 0; j < arrayArgs[i].size(); ++j) {
                const VlDvsArray* const arrayp = arrayArgs[i][j].first;
                const VlDvsSlot* const slotp = arrayArgs[i][j].second;
                if (arrayp) {
                    arrayp->write(arrayp->queuep, datas[i][j].data(), arrayRefs[i][j].n_elems);
                } else if (arrayRefs[i][j].n_elems != slotp->size(slotp->queuep)) {
                    // Resized at the back, new handles null (IEEE 1800-2023 7.5.1, 7.10)
                    slotp->resize(slotp->queuep, arrayRefs[i][j].n_elems);
                }
            }
        }
    }
    VlDvsHandles::Handle& root = *context.parts[0].handlep;
    handles.log(nullptr, 0, nullptr, 0, 0, seed, result, nParts);
    if (result == DVS_RANDOMIZE_NULL) {
        // Warned once per site: the call fails each time
        const VerilatedLockGuard rootLock{root.m_mutex};
        if (!root.m_nullWarned) {
            root.m_nullWarned = true;
            const std::string msg = "dv-solve could not solve the constraints of the randomize()"
                                    " call at "
                                    + context.parts[0].constraints[0]
                                    + ": a constraint reads a variable through a null handle";
            VL_WARN_MT("", 0, "", msg.c_str());
        }
        return false;
    }
    return VlDvsHandles::report(result, context.parts[0].constraints,
                                context.parts[0].nConstraints, &constraints);
}
