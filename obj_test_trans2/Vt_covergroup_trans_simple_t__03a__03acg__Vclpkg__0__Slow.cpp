// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_trans_simple.h for the primary calling header

#include "Vt_covergroup_trans_simple__pch.h"

VL_ATTR_COLD void Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg___ctor_var_reset(Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg___configure_coverage(Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 4, "", "v_line/cg", "block", "13-17");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 15, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 15, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 15, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[23]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 15, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[24]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 15, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[25]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 15, "", "v_line/cg", "block", "13");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[26]), first, "test_regress/t/t_covergroup_trans_simple.v", 13, 15, "", "v_line/cg", "block", "13");
}

VL_ATTR_COLD void Vt_covergroup_trans_simple_t__03a__03acg___configure_coverage(Vt_covergroup_trans_simple_t__03a__03acg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
