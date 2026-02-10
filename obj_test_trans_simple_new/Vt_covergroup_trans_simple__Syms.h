// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VT_COVERGROUP_TRANS_SIMPLE__SYMS_H_
#define VERILATED_VT_COVERGROUP_TRANS_SIMPLE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vt_covergroup_trans_simple.h"

// INCLUDE MODULE CLASSES
#include "Vt_covergroup_trans_simple___024root.h"
#include "Vt_covergroup_trans_simple_t.h"
#include "Vt_covergroup_trans_simple_std.h"
#include "Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg.h"
#include "Vt_covergroup_trans_simple_std__03a__03asemaphore__Vclpkg.h"
#include "Vt_covergroup_trans_simple_std__03a__03aprocess__Vclpkg.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_trans_simple__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vt_covergroup_trans_simple* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vt_covergroup_trans_simple___024root TOP;
    Vt_covergroup_trans_simple_std TOP__std;
    Vt_covergroup_trans_simple_t   TOP__t;
    Vt_covergroup_trans_simple_std__03a__03aprocess__Vclpkg TOP__std__03a__03aprocess__Vclpkg;
    Vt_covergroup_trans_simple_std__03a__03asemaphore__Vclpkg TOP__std__03a__03asemaphore__Vclpkg;
    Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg TOP__t__03a__03acg__Vclpkg;

    // COVERAGE
    uint32_t __Vcoverage[43];

    // CONSTRUCTORS
    Vt_covergroup_trans_simple__Syms(VerilatedContext* contextp, const char* namep, Vt_covergroup_trans_simple* modelp);
    ~Vt_covergroup_trans_simple__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
