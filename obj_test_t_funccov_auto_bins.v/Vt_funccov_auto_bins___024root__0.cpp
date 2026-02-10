// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_auto_bins.h for the primary calling header

#include "Vt_funccov_auto_bins__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_funccov_auto_bins___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vt_funccov_auto_bins___024root___eval_triggers__act(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_triggers__act\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = VL_EXTEND_QI(64,1, vlSelfRef.__VdynSched.evaluate());
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vt_funccov_auto_bins___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    vlSelfRef.__VdynSched.doPostUpdates();
}

bool Vt_funccov_auto_bins___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vt_funccov_auto_bins___024root___timing_resume(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___timing_resume\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdynSched.resume();
    }
}

void Vt_funccov_auto_bins___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vt_funccov_auto_bins___024root___eval_phase__act(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_phase__act\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vt_funccov_auto_bins___024root___eval_triggers__act(vlSelf);
    Vt_funccov_auto_bins___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vt_funccov_auto_bins___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        Vt_funccov_auto_bins___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

void Vt_funccov_auto_bins___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vt_funccov_auto_bins___024root___eval_phase__nba(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_phase__nba\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vt_funccov_auto_bins___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vt_funccov_auto_bins___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vt_funccov_auto_bins___024root___eval(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vt_funccov_auto_bins___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("test_regress/t/t_funccov_auto_bins.v", 5, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vt_funccov_auto_bins___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("test_regress/t/t_funccov_auto_bins.v", 5, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vt_funccov_auto_bins___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vt_funccov_auto_bins___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vt_funccov_auto_bins___024root___eval_debug_assertions(Vt_funccov_auto_bins___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_funccov_auto_bins___024root___eval_debug_assertions\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
