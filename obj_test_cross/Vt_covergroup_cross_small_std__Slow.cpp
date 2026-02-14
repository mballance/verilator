// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_cross_small.h for the primary calling header

#include "Vt_covergroup_cross_small__pch.h"

void Vt_covergroup_cross_small_std___ctor_var_reset(Vt_covergroup_cross_small_std* vlSelf);

Vt_covergroup_cross_small_std::Vt_covergroup_cross_small_std() = default;
Vt_covergroup_cross_small_std::~Vt_covergroup_cross_small_std() = default;

void Vt_covergroup_cross_small_std::ctor(Vt_covergroup_cross_small__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vt_covergroup_cross_small_std___ctor_var_reset(this);
}

void Vt_covergroup_cross_small_std::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vt_covergroup_cross_small_std::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
