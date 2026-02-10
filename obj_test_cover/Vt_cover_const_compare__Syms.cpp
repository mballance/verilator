// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vt_cover_const_compare__pch.h"
#include "Vt_cover_const_compare.h"
#include "Vt_cover_const_compare___024root.h"

// FUNCTIONS
Vt_cover_const_compare__Syms::~Vt_cover_const_compare__Syms()
{
}

Vt_cover_const_compare__Syms::Vt_cover_const_compare__Syms(VerilatedContext* contextp, const char* namep, Vt_cover_const_compare* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(33);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
