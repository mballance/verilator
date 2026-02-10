// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_dynamic.h for the primary calling header

#include "Vt_covergroup_dynamic__pch.h"

VL_ATTR_COLD void Vt_covergroup_dynamic___024root___eval_static(Vt_covergroup_dynamic___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_dynamic___024root___eval_static\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_dynamic_t___eval_initial__TOP__t(Vt_covergroup_dynamic_t* vlSelf);

VL_ATTR_COLD void Vt_covergroup_dynamic___024root___eval_initial(Vt_covergroup_dynamic___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_dynamic___024root___eval_initial\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vt_covergroup_dynamic_t___eval_initial__TOP__t((&vlSymsp->TOP__t));
}

VL_ATTR_COLD void Vt_covergroup_dynamic___024root___eval_final(Vt_covergroup_dynamic___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_dynamic___024root___eval_final\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_dynamic___024root___eval_settle(Vt_covergroup_dynamic___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_dynamic___024root___eval_settle\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_dynamic___024root___ctor_var_reset(Vt_covergroup_dynamic___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_dynamic___024root___ctor_var_reset\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_dynamic___024root___configure_coverage(Vt_covergroup_dynamic___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_dynamic___024root___configure_coverage\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
