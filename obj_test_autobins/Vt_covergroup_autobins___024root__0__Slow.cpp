// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_autobins.h for the primary calling header

#include "Vt_covergroup_autobins__pch.h"

VL_ATTR_COLD void Vt_covergroup_autobins___024root___eval_static(Vt_covergroup_autobins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___eval_static\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_autobins_t___eval_initial__TOP__t(Vt_covergroup_autobins_t* vlSelf);

VL_ATTR_COLD void Vt_covergroup_autobins___024root___eval_initial(Vt_covergroup_autobins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___eval_initial\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vt_covergroup_autobins_t___eval_initial__TOP__t((&vlSymsp->TOP__t));
}

VL_ATTR_COLD void Vt_covergroup_autobins___024root___eval_final(Vt_covergroup_autobins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___eval_final\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_autobins___024root___eval_settle(Vt_covergroup_autobins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___eval_settle\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_autobins___024root___ctor_var_reset(Vt_covergroup_autobins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___ctor_var_reset\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
}

VL_ATTR_COLD void Vt_covergroup_autobins___024root___configure_coverage(Vt_covergroup_autobins___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_autobins___024root___configure_coverage\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
