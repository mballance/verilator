// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#include "Vt_covergroup_bins_default_illegal__pch.h"

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg___ctor_var_reset(Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg___configure_coverage(Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[30]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 4, "", "v_line/cg_valid", "block", "23-26");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[31]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 15, "", "v_line/cg_valid", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[32]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 15, "", "v_line/cg_valid", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[33]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 15, "", "v_line/cg_valid", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[34]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 15, "", "v_line/cg_valid", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[35]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 15, "", "v_line/cg_valid", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[36]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 15, "", "v_line/cg_valid", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[37]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 23, 15, "", "v_line/cg_valid", "block", "23");
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid___configure_coverage(Vt_covergroup_bins_default_illegal_t__03a__03acg_valid* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
