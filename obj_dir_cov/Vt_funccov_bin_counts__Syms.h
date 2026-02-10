// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VT_FUNCCOV_BIN_COUNTS__SYMS_H_
#define VERILATED_VT_FUNCCOV_BIN_COUNTS__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vt_funccov_bin_counts.h"

// INCLUDE MODULE CLASSES
#include "Vt_funccov_bin_counts___024root.h"
#include "Vt_funccov_bin_counts_t.h"
#include "Vt_funccov_bin_counts_std.h"
#include "Vt_funccov_bin_counts_t__03a__03acg__Vclpkg.h"
#include "Vt_funccov_bin_counts_std__03a__03asemaphore__Vclpkg.h"
#include "Vt_funccov_bin_counts_std__03a__03aprocess__Vclpkg.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vt_funccov_bin_counts__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vt_funccov_bin_counts* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vt_funccov_bin_counts___024root TOP;
    Vt_funccov_bin_counts_std      TOP__std;
    Vt_funccov_bin_counts_t        TOP__t;
    Vt_funccov_bin_counts_std__03a__03aprocess__Vclpkg TOP__std__03a__03aprocess__Vclpkg;
    Vt_funccov_bin_counts_std__03a__03asemaphore__Vclpkg TOP__std__03a__03asemaphore__Vclpkg;
    Vt_funccov_bin_counts_t__03a__03acg__Vclpkg TOP__t__03a__03acg__Vclpkg;

    // COVERAGE
    uint32_t __Vcoverage[39];

    // CONSTRUCTORS
    Vt_funccov_bin_counts__Syms(VerilatedContext* contextp, const char* namep, Vt_funccov_bin_counts* modelp);
    ~Vt_funccov_bin_counts__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
