// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_cross_small.h for the primary calling header

#include "Vt_covergroup_cross_small__pch.h"

void Vt_covergroup_cross_small___024root___ctor_var_reset(Vt_covergroup_cross_small___024root* vlSelf);

Vt_covergroup_cross_small___024root::Vt_covergroup_cross_small___024root(Vt_covergroup_cross_small__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vt_covergroup_cross_small___024root___ctor_var_reset(this);
}

void Vt_covergroup_cross_small___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vt_covergroup_cross_small___024root::~Vt_covergroup_cross_small___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
