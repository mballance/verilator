// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest_partial_coverage.h for the primary calling header

#include "Vtest_partial_coverage__pch.h"

VL_ATTR_COLD void Vtest_partial_coverage___024root___eval_static(Vtest_partial_coverage___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest_partial_coverage___024root___eval_static\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtest_partial_coverage_t___eval_initial__TOP__t(Vtest_partial_coverage_t* vlSelf);

VL_ATTR_COLD void Vtest_partial_coverage___024root___eval_initial(Vtest_partial_coverage___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest_partial_coverage___024root___eval_initial\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtest_partial_coverage_t___eval_initial__TOP__t((&vlSymsp->TOP__t));
}

VL_ATTR_COLD void Vtest_partial_coverage___024root___eval_final(Vtest_partial_coverage___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest_partial_coverage___024root___eval_final\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtest_partial_coverage___024root___eval_settle(Vtest_partial_coverage___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest_partial_coverage___024root___eval_settle\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtest_partial_coverage___024root___ctor_var_reset(Vtest_partial_coverage___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest_partial_coverage___024root___ctor_var_reset\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtest_partial_coverage___024root___configure_coverage(Vtest_partial_coverage___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtest_partial_coverage___024root___configure_coverage\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
