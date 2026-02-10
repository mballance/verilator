// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_advanced.h for the primary calling header

#include "Vt_covergroup_bins_advanced__pch.h"

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg___ctor_var_reset(Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg___configure_coverage(Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_advanced_t__03a__03acg_ignore__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[27]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 4, "", "v_line/cg_ignore", "block", "18-23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[28]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 15, "", "v_line/cg_ignore", "block", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[29]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 15, "", "v_line/cg_ignore", "block", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[30]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 15, "", "v_line/cg_ignore", "block", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[31]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 15, "", "v_line/cg_ignore", "block", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[32]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 15, "", "v_line/cg_ignore", "block", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[33]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 15, "", "v_line/cg_ignore", "block", "18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[34]), first, "test_regress/t/t_covergroup_bins_advanced.v", 18, 15, "", "v_line/cg_ignore", "block", "18");
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_ignore___configure_coverage(Vt_covergroup_bins_advanced_t__03a__03acg_ignore* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_ignore___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
