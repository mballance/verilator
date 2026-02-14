// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_negative_ranges.h for the primary calling header

#include "Vt_covergroup_negative_ranges__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vt_covergroup_negative_ranges___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vt_covergroup_negative_ranges___024root___eval_triggers__act(Vt_covergroup_negative_ranges___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___eval_triggers__act\n"); );
    Vt_covergroup_negative_ranges__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vt_covergroup_negative_ranges___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vt_covergroup_negative_ranges___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___trigger_anySet__act\n"); );
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

void Vt_covergroup_negative_ranges_t___nba_sequent__TOP__t__0(Vt_covergroup_negative_ranges_t* vlSelf);

void Vt_covergroup_negative_ranges___024root___eval_nba(Vt_covergroup_negative_ranges___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___eval_nba\n"); );
    Vt_covergroup_negative_ranges__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vt_covergroup_negative_ranges_t___nba_sequent__TOP__t__0((&vlSymsp->TOP__t));
    }
}

void Vt_covergroup_negative_ranges___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vt_covergroup_negative_ranges___024root___eval_phase__act(Vt_covergroup_negative_ranges___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___eval_phase__act\n"); );
    Vt_covergroup_negative_ranges__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vt_covergroup_negative_ranges___024root___eval_triggers__act(vlSelf);
    Vt_covergroup_negative_ranges___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vt_covergroup_negative_ranges___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vt_covergroup_negative_ranges___024root___eval_phase__nba(Vt_covergroup_negative_ranges___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___eval_phase__nba\n"); );
    Vt_covergroup_negative_ranges__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vt_covergroup_negative_ranges___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vt_covergroup_negative_ranges___024root___eval_nba(vlSelf);
        Vt_covergroup_negative_ranges___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vt_covergroup_negative_ranges___024root___eval(Vt_covergroup_negative_ranges___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___eval\n"); );
    Vt_covergroup_negative_ranges__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vt_covergroup_negative_ranges___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("test_regress/t/t_covergroup_negative_ranges.v", 8, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vt_covergroup_negative_ranges___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("test_regress/t/t_covergroup_negative_ranges.v", 8, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vt_covergroup_negative_ranges___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vt_covergroup_negative_ranges___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vt_covergroup_negative_ranges___024root___eval_debug_assertions(Vt_covergroup_negative_ranges___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vt_covergroup_negative_ranges___024root___eval_debug_assertions\n"); );
    Vt_covergroup_negative_ranges__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
}
#endif  // VL_DEBUG
