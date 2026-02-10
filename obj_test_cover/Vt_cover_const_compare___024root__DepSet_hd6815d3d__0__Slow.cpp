// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_cover_const_compare.h for the primary calling header

#include "Vt_cover_const_compare__pch.h"
#include "Vt_cover_const_compare__Syms.h"
#include "Vt_cover_const_compare___024root.h"

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_initial__TOP(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_initial__TOP\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.t__DOT__cyc = 1U;
    ++(vlSymsp->__Vcoverage[2]);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__stl(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_triggers__stl(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_triggers__stl\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vt_cover_const_compare___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vt_cover_const_compare___024root___stl_sequent__TOP__0(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___stl_sequent__TOP__0\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.clk) ^ (IData)(vlSelfRef.t__DOT____Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.clk, vlSelfRef.t__DOT____Vtogcov__clk);
        vlSelfRef.t__DOT____Vtogcov__clk = vlSelfRef.clk;
    }
    if ((1U & (vlSelfRef.t__DOT__cyc ^ (IData)(vlSelfRef.t__DOT____Vtogcov__a)))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 3, vlSelfRef.t__DOT__cyc, vlSelfRef.t__DOT____Vtogcov__a);
        vlSelfRef.t__DOT____Vtogcov__a = (1U & vlSelfRef.t__DOT__cyc);
    }
    vlSelfRef.t__DOT__a = (1U & vlSelfRef.t__DOT__cyc);
}

VL_ATTR_COLD void Vt_cover_const_compare___024root___configure_coverage(Vt_cover_const_compare___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___configure_coverage\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_cover_const_compare.v", 12, 10, ".t", "v_toggle/t", "clk");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "test_regress/t/t_cover_const_compare.v", 14, 17, ".t", "v_line/t", "block", "14");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[3]), first, "test_regress/t/t_cover_const_compare.v", 16, 9, ".t", "v_toggle/t", "a");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[3]), first, "test_regress/t/t_cover_const_compare.v", 17, 9, ".t", "v_toggle/t", "b");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "test_regress/t/t_cover_const_compare.v", 24, 8, ".t", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "test_regress/t/t_cover_const_compare.v", 25, 8, ".t", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "test_regress/t/t_cover_const_compare.v", 26, 7, ".t", "v_branch/t", "if", "26-28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_cover_const_compare.v", 26, 8, ".t", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_cover_const_compare.v", 19, 4, ".t", "v_line/t", "block", "19-20");
}
