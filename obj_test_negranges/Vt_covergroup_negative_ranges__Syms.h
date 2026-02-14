// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VT_COVERGROUP_NEGATIVE_RANGES__SYMS_H_
#define VERILATED_VT_COVERGROUP_NEGATIVE_RANGES__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vt_covergroup_negative_ranges.h"

// INCLUDE MODULE CLASSES
#include "Vt_covergroup_negative_ranges___024root.h"
#include "Vt_covergroup_negative_ranges_t.h"
#include "Vt_covergroup_negative_ranges_std.h"
#include "Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg.h"
#include "Vt_covergroup_negative_ranges_std__03a__03asemaphore__Vclpkg.h"
#include "Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_negative_ranges__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vt_covergroup_negative_ranges* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vt_covergroup_negative_ranges___024root TOP;
    Vt_covergroup_negative_ranges_std TOP__std;
    Vt_covergroup_negative_ranges_t TOP__t;
    Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg TOP__std__03a__03aprocess__Vclpkg;
    Vt_covergroup_negative_ranges_std__03a__03asemaphore__Vclpkg TOP__std__03a__03asemaphore__Vclpkg;
    Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg TOP__t__03a__03acg__Vclpkg;

    // CONSTRUCTORS
    Vt_covergroup_negative_ranges__Syms(VerilatedContext* contextp, const char* namep, Vt_covergroup_negative_ranges* modelp);
    ~Vt_covergroup_negative_ranges__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
