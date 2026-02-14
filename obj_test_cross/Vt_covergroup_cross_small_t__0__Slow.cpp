// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_cross_small.h for the primary calling header

#include "Vt_covergroup_cross_small__pch.h"

VL_ATTR_COLD void Vt_covergroup_cross_small_t___eval_static__TOP__t(Vt_covergroup_cross_small_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_cross_small_t___eval_static__TOP__t\n"); );
    Vt_covergroup_cross_small__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__cyc = 0U;
    vlSelfRef.__PVT__cg_inst = VL_NEW(Vt_covergroup_cross_small_t__03a__03acg, vlSymsp);
}

VL_ATTR_COLD void Vt_covergroup_cross_small_t___ctor_var_reset(Vt_covergroup_cross_small_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_cross_small_t___ctor_var_reset\n"); );
    Vt_covergroup_cross_small__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->__PVT__cyc = 0;
    vlSelf->__PVT__a = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 510903276987443985ull);
    vlSelf->__PVT__b = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16900879642891266615ull);
    vlSelf->__PVT__unnamedblk1__DOT__inst_cov = 0;
}
