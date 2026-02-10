// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VT_COVER_CONST_COMPARE__SYMS_H_
#define VERILATED_VT_COVER_CONST_COMPARE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vt_cover_const_compare.h"

// INCLUDE MODULE CLASSES
#include "Vt_cover_const_compare___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vt_cover_const_compare__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vt_cover_const_compare* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vt_cover_const_compare___024root TOP;

    // COVERAGE
    uint32_t __Vcoverage[10];

    // CONSTRUCTORS
    Vt_cover_const_compare__Syms(VerilatedContext* contextp, const char* namep, Vt_cover_const_compare* modelp);
    ~Vt_cover_const_compare__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
