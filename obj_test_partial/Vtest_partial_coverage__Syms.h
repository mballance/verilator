// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTEST_PARTIAL_COVERAGE__SYMS_H_
#define VERILATED_VTEST_PARTIAL_COVERAGE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtest_partial_coverage.h"

// INCLUDE MODULE CLASSES
#include "Vtest_partial_coverage___024root.h"
#include "Vtest_partial_coverage_cg.h"
#include "Vtest_partial_coverage_t.h"
#include "Vtest_partial_coverage_std.h"
#include "Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg.h"
#include "Vtest_partial_coverage_std__03a__03aprocess__Vclpkg.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtest_partial_coverage__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtest_partial_coverage* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtest_partial_coverage___024root TOP;
    Vtest_partial_coverage_std     TOP__std;
    Vtest_partial_coverage_t       TOP__t;
    Vtest_partial_coverage_std__03a__03aprocess__Vclpkg TOP__std__03a__03aprocess__Vclpkg;
    Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg TOP__std__03a__03asemaphore__Vclpkg;

    // COVERAGE
    uint32_t __Vcoverage[25];

    // CONSTRUCTORS
    Vtest_partial_coverage__Syms(VerilatedContext* contextp, const char* namep, Vtest_partial_coverage* modelp);
    ~Vtest_partial_coverage__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
