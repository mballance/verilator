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
    ++(vlSymsp->__Vcoverage[6]);
    vlSelfRef.__PVT__cyc = 0U;
    ++(vlSymsp->__Vcoverage[7]);
}

VL_ATTR_COLD void Vt_covergroup_auto_sample_t___stl_sequent__TOP__t__0(Vt_covergroup_auto_sample_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_auto_sample_t___stl_sequent__TOP__t__0\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSymsp->TOP.clk) ^ (IData)(vlSelfRef.__Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSymsp->TOP.clk, vlSelfRef.__Vtogcov__clk);
        vlSelfRef.__Vtogcov__clk = vlSymsp->TOP.clk;
    }
    if (((IData)(vlSelfRef.__PVT__data) ^ (IData)(vlSelfRef.__Vtogcov__data))) {
        VL_COV_TOGGLE_CHG_ST_I(2, vlSymsp->__Vcoverage + 2, vlSelfRef.__PVT__data, vlSelfRef.__Vtogcov__data);
        vlSelfRef.__Vtogcov__data = vlSelfRef.__PVT__data;
    }
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
    vlSelf->__Vtogcov__clk = 0;
    vlSelf->__Vtogcov__data = 0;
}

VL_ATTR_COLD void Vt_covergroup_auto_sample_t___configure_coverage(Vt_covergroup_auto_sample_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_auto_sample_t___configure_coverage\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_auto_sample.v", 9, 10, "", "v_toggle/t", "clk");
    vlSelf->__vlCoverToggleInsert(0, 1, 1, &(vlSymsp->__Vcoverage[2]), first, "test_regress/t/t_covergroup_auto_sample.v", 11, 16, "", "v_toggle/t", "data");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "test_regress/t/t_covergroup_auto_sample.v", 23, 17, "", "v_line/t", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "test_regress/t/t_covergroup_auto_sample.v", 25, 14, "", "v_line/t", "block", "25");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_covergroup_auto_sample.v", 31, 10, "", "v_line/t", "case", "31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_covergroup_auto_sample.v", 32, 10, "", "v_line/t", "case", "32");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_covergroup_auto_sample.v", 33, 10, "", "v_line/t", "case", "33");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_covergroup_auto_sample.v", 34, 10, "", "v_line/t", "case", "34");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_covergroup_auto_sample.v", 37, 12, "", "v_line/t", "if", "37-39");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "test_regress/t/t_covergroup_auto_sample.v", 35, 10, "", "v_line/t", "case", "35-36");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "test_regress/t/t_covergroup_auto_sample.v", 50, 8, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "test_regress/t/t_covergroup_auto_sample.v", 27, 4, "", "v_line/t", "block", "27-28,30");
}
