// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_cover_const_compare.h for the primary calling header

#include "Vt_cover_const_compare__pch.h"
#include "Vt_cover_const_compare___024root.h"

void Vt_cover_const_compare___024root___ico_sequent__TOP__0(Vt_cover_const_compare___024root* vlSelf);

void Vt_cover_const_compare___024root___eval_ico(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_ico\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vt_cover_const_compare___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vt_cover_const_compare___024root___eval_triggers__ico(Vt_cover_const_compare___024root* vlSelf);

bool Vt_cover_const_compare___024root___eval_phase__ico(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_phase__ico\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vt_cover_const_compare___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vt_cover_const_compare___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vt_cover_const_compare___024root___eval_act(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_act\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vt_cover_const_compare___024root___nba_sequent__TOP__0(Vt_cover_const_compare___024root* vlSelf);

void Vt_cover_const_compare___024root___eval_nba(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_nba\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vt_cover_const_compare___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vt_cover_const_compare___024root___eval_triggers__act(Vt_cover_const_compare___024root* vlSelf);

bool Vt_cover_const_compare___024root___eval_phase__act(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_phase__act\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vt_cover_const_compare___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vt_cover_const_compare___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vt_cover_const_compare___024root___eval_phase__nba(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_phase__nba\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vt_cover_const_compare___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__ico(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__nba(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__act(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG

void Vt_cover_const_compare___024root___eval(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vt_cover_const_compare___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("test_regress/t/t_cover_const_compare.v", 7, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vt_cover_const_compare___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vt_cover_const_compare___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("test_regress/t/t_cover_const_compare.v", 7, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vt_cover_const_compare___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("test_regress/t/t_cover_const_compare.v", 7, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vt_cover_const_compare___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vt_cover_const_compare___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vt_cover_const_compare___024root___eval_debug_assertions(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_debug_assertions\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
}
#endif  // VL_DEBUG
