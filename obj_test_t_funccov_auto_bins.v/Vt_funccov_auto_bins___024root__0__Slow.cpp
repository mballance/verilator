// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_auto_bins.h for the primary calling header

#include "Vt_funccov_auto_bins__pch.h"

VL_ATTR_COLD void Vt_funccov_auto_bins___024root___eval_static(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_static\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_funccov_auto_bins_t___eval_initial__TOP__t(Vt_funccov_auto_bins_t* vlSelf);

VL_ATTR_COLD void Vt_funccov_auto_bins___024root___eval_initial(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_initial\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vt_funccov_auto_bins_t___eval_initial__TOP__t((&vlSymsp->TOP__t));
}

VL_ATTR_COLD void Vt_funccov_auto_bins___024root___eval_final(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_final\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_funccov_auto_bins___024root___eval_settle(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_settle\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vt_funccov_auto_bins___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_funccov_auto_bins___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vt_funccov_auto_bins___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @([true] __VdynSched.evaluate())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vt_funccov_auto_bins___024root___ctor_var_reset(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___ctor_var_reset\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}

VL_ATTR_COLD void Vt_funccov_auto_bins___024root___configure_coverage(Vt_funccov_auto_bins___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___configure_coverage\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
