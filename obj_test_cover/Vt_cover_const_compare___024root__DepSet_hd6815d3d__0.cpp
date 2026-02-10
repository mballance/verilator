// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_cover_const_compare.h for the primary calling header

#include "Vt_cover_const_compare__pch.h"
#include "Vt_cover_const_compare__Syms.h"
#include "Vt_cover_const_compare___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__ico(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG

void Vt_cover_const_compare___024root___eval_triggers__ico(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_triggers__ico\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vt_cover_const_compare___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

void Vt_cover_const_compare___024root___ico_sequent__TOP__0(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___ico_sequent__TOP__0\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.clk) ^ (IData)(vlSelfRef.t__DOT____Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.clk, vlSelfRef.t__DOT____Vtogcov__clk);
        vlSelfRef.t__DOT____Vtogcov__clk = vlSelfRef.clk;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__act(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG

void Vt_cover_const_compare___024root___eval_triggers__act(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_triggers__act\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clk) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vt_cover_const_compare___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void Vt_cover_const_compare___024root___nba_sequent__TOP__0(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___nba_sequent__TOP__0\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vdly__t__DOT__cyc;
    __Vdly__t__DOT__cyc = 0;
    // Body
    __Vdly__t__DOT__cyc = vlSelfRef.t__DOT__cyc;
    __Vdly__t__DOT__cyc = ((IData)(1U) + vlSelfRef.t__DOT__cyc);
    if (VL_UNLIKELY((((IData)(vlSelfRef.t__DOT__a) 
                      != (1U & vlSelfRef.t__DOT__cyc))))) {
        VL_STOP_MT("test_regress/t/t_cover_const_compare.v", 24, "");
    } else {
        ++(vlSymsp->__Vcoverage[5]);
    }
    if (VL_UNLIKELY((((IData)(vlSelfRef.t__DOT__a) 
                      != (1U & vlSelfRef.t__DOT__cyc))))) {
        VL_STOP_MT("test_regress/t/t_cover_const_compare.v", 25, "");
    } else {
        ++(vlSymsp->__Vcoverage[6]);
    }
    if (VL_UNLIKELY(((0x0000000aU == vlSelfRef.t__DOT__cyc)))) {
        VL_WRITEF_NX("*-* All Finished *-*\n",0);
        VL_FINISH_MT("test_regress/t/t_cover_const_compare.v", 28, "");
        ++(vlSymsp->__Vcoverage[7]);
    } else {
        ++(vlSymsp->__Vcoverage[8]);
    }
    ++(vlSymsp->__Vcoverage[9]);
    vlSelfRef.t__DOT__cyc = __Vdly__t__DOT__cyc;
    if ((1U & (vlSelfRef.t__DOT__cyc ^ (IData)(vlSelfRef.t__DOT____Vtogcov__a)))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 3, vlSelfRef.t__DOT__cyc, vlSelfRef.t__DOT____Vtogcov__a);
        vlSelfRef.t__DOT____Vtogcov__a = (1U & vlSelfRef.t__DOT__cyc);
    }
    vlSelfRef.t__DOT__a = (1U & vlSelfRef.t__DOT__cyc);
}
