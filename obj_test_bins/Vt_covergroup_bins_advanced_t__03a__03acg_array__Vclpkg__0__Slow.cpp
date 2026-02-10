// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_advanced.h for the primary calling header

#include "Vt_covergroup_bins_advanced__pch.h"

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg___ctor_var_reset(Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg___configure_coverage(Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_advanced_t__03a__03acg_array__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[35]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 4, "", "v_line/cg_array", "block", "28-30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[36]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 15, "", "v_line/cg_array", "block", "28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[37]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 15, "", "v_line/cg_array", "block", "28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[38]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 15, "", "v_line/cg_array", "block", "28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[39]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 15, "", "v_line/cg_array", "block", "28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[40]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 15, "", "v_line/cg_array", "block", "28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[41]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 15, "", "v_line/cg_array", "block", "28");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[42]), first, "test_regress/t/t_covergroup_bins_advanced.v", 28, 15, "", "v_line/cg_array", "block", "28");
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_array___configure_coverage(Vt_covergroup_bins_advanced_t__03a__03acg_array* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_array___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
