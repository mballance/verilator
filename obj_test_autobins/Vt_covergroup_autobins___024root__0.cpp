// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_autobins.h for the primary calling header

#include "Vt_covergroup_autobins__pch.h"

void Vt_covergroup_autobins___024root___eval(Vt_covergroup_autobins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___eval\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
void Vt_covergroup_autobins___024root___eval_debug_assertions(Vt_covergroup_autobins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___eval_debug_assertions\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
}
#endif  // VL_DEBUG
