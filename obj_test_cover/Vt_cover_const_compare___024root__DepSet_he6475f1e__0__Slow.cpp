// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_cover_const_compare.h for the primary calling header

#include "Vt_cover_const_compare__pch.h"
#include "Vt_cover_const_compare___024root.h"

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_static(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_static\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_initial__TOP(Vt_cover_const_compare___024root* vlSelf);

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_initial(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_initial\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vt_cover_const_compare___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_final(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_final\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__stl(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vt_cover_const_compare___024root___eval_phase__stl(Vt_cover_const_compare___024root* vlSelf);

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_settle(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_settle\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vt_cover_const_compare___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("test_regress/t/t_cover_const_compare.v", 7, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vt_cover_const_compare___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__stl(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___dump_triggers__stl\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vt_cover_const_compare___024root___stl_sequent__TOP__0(Vt_cover_const_compare___024root* vlSelf);

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_stl(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_stl\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vt_cover_const_compare___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vt_cover_const_compare___024root___eval_triggers__stl(Vt_cover_const_compare___024root* vlSelf);

VL_ATTR_COLD bool Vt_cover_const_compare___024root___eval_phase__stl(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___eval_phase__stl\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vt_cover_const_compare___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vt_cover_const_compare___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__ico(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___dump_triggers__ico\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__act(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___dump_triggers__act\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_cover_const_compare___024root___dump_triggers__nba(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___dump_triggers__nba\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vt_cover_const_compare___024root___ctor_var_reset(Vt_cover_const_compare___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_cover_const_compare___024root___ctor_var_reset\n"); );
    Vt_cover_const_compare__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->t__DOT__cyc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15508623621340971111ull);
    vlSelf->t__DOT__a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 568261790826559771ull);
    vlSelf->t__DOT____Vtogcov__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3594496819688659016ull);
    vlSelf->t__DOT____Vtogcov__a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7450174196643077209ull);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9526919608049418986ull);
}
