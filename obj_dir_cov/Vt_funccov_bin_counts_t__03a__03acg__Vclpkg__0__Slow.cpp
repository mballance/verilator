// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_bin_counts.h for the primary calling header

#include "Vt_funccov_bin_counts__pch.h"

VL_ATTR_COLD void Vt_funccov_bin_counts_t__03a__03acg__Vclpkg___ctor_var_reset(Vt_funccov_bin_counts_t__03a__03acg__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_funccov_bin_counts_t__03a__03acg__Vclpkg___ctor_var_reset\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_funccov_bin_counts_t__03a__03acg__Vclpkg___configure_coverage(Vt_funccov_bin_counts_t__03a__03acg__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_funccov_bin_counts_t__03a__03acg__Vclpkg___configure_coverage\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 5, "", "v_line/cg", "block", "13-18");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 16, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 16, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 16, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 16, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 16, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 16, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "test_regress/t/t_funccov_bin_counts.v", 13, 16, "", "v_line/cg", "block", "13");
}

VL_ATTR_COLD void Vt_funccov_bin_counts_t__03a__03acg___configure_coverage(Vt_funccov_bin_counts_t__03a__03acg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
