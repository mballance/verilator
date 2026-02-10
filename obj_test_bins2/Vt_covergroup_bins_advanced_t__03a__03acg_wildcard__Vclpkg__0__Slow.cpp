// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_advanced.h for the primary calling header

#include "Vt_covergroup_bins_advanced__pch.h"

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg___ctor_var_reset(Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg___configure_coverage(Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[43]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 4, "", "v_line/cg_wildcard", "block", "35-40");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[44]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 15, "", "v_line/cg_wildcard", "block", "35");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[45]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 15, "", "v_line/cg_wildcard", "block", "35");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[46]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 15, "", "v_line/cg_wildcard", "block", "35");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[47]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 15, "", "v_line/cg_wildcard", "block", "35");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[48]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 15, "", "v_line/cg_wildcard", "block", "35");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[49]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 15, "", "v_line/cg_wildcard", "block", "35");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[50]), first, "test_regress/t/t_covergroup_bins_advanced.v", 35, 15, "", "v_line/cg_wildcard", "block", "35");
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard___configure_coverage(Vt_covergroup_bins_advanced_t__03a__03acg_wildcard* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
