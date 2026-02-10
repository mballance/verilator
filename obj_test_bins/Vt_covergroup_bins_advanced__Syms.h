// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VT_COVERGROUP_BINS_ADVANCED__SYMS_H_
#define VERILATED_VT_COVERGROUP_BINS_ADVANCED__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vt_covergroup_bins_advanced.h"

// INCLUDE MODULE CLASSES
#include "Vt_covergroup_bins_advanced___024root.h"
#include "Vt_covergroup_bins_advanced_t.h"
#include "Vt_covergroup_bins_advanced_std.h"
#include "Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg.h"
#include "Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg.h"
#include "Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg.h"
#include "Vt_covergroup_bins_advanced_std__03a__03asemaphore__Vclpkg.h"
#include "Vt_covergroup_bins_advanced_std__03a__03aprocess__Vclpkg.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_bins_advanced__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vt_covergroup_bins_advanced* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vt_covergroup_bins_advanced___024root TOP;
    Vt_covergroup_bins_advanced_std TOP__std;
    Vt_covergroup_bins_advanced_t  TOP__t;
    Vt_covergroup_bins_advanced_std__03a__03aprocess__Vclpkg TOP__std__03a__03aprocess__Vclpkg;
    Vt_covergroup_bins_advanced_std__03a__03asemaphore__Vclpkg TOP__std__03a__03asemaphore__Vclpkg;
    Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg TOP__t__03a__03acg_array__Vclpkg;
    Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg TOP__t__03a__03acg_ignore__Vclpkg;
    Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg TOP__t__03a__03acg_wildcard__Vclpkg;

    // COVERAGE
    uint32_t __Vcoverage[67];

    // CONSTRUCTORS
    Vt_covergroup_bins_advanced__Syms(VerilatedContext* contextp, const char* namep, Vt_covergroup_bins_advanced* modelp);
    ~Vt_covergroup_bins_advanced__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
