// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#include "Vt_covergroup_bins_default_illegal__pch.h"

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg___ctor_var_reset(Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg___configure_coverage(Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 4, "", "v_line/cg_default", "block", "15-18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[23]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 15, "", "v_line/cg_default", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[24]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 15, "", "v_line/cg_default", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[25]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 15, "", "v_line/cg_default", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[26]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 15, "", "v_line/cg_default", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[27]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 15, "", "v_line/cg_default", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[28]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 15, "", "v_line/cg_default", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[29]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 15, 15, "", "v_line/cg_default", "block", "15");
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t__03a__03acg_default___configure_coverage(Vt_covergroup_bins_default_illegal_t__03a__03acg_default* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
