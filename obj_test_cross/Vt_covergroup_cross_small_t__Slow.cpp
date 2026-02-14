// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_cross_small.h for the primary calling header

#include "Vt_covergroup_cross_small__pch.h"

void Vt_covergroup_cross_small_t___ctor_var_reset(Vt_covergroup_cross_small_t* vlSelf);

Vt_covergroup_cross_small_t::Vt_covergroup_cross_small_t() = default;
Vt_covergroup_cross_small_t::~Vt_covergroup_cross_small_t() = default;

void Vt_covergroup_cross_small_t::ctor(Vt_covergroup_cross_small__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vt_covergroup_cross_small_t___ctor_var_reset(this);
}

void Vt_covergroup_cross_small_t::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vt_covergroup_cross_small_t::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
