// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_auto_sample.h for the primary calling header

#include "Vt_covergroup_auto_sample__pch.h"

VL_ATTR_COLD void Vt_covergroup_auto_sample_t___eval_static__TOP__t(Vt_covergroup_auto_sample_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_auto_sample_t___eval_static__TOP__t\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__cg_inst = VL_NEW(Vt_covergroup_auto_sample_t__03a__03acg, vlSymsp);
    vlSelfRef.__PVT__cyc = 0U;
}

VL_ATTR_COLD void Vt_covergroup_auto_sample_t___ctor_var_reset(Vt_covergroup_auto_sample_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_auto_sample_t___ctor_var_reset\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->__PVT__data = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10363016170300574568ull);
    vlSelf->__PVT__cyc = 0;
}

VL_ATTR_COLD void Vt_covergroup_auto_sample_t___configure_coverage(Vt_covergroup_auto_sample_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_auto_sample_t___configure_coverage\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
