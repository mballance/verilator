// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_trans_simple.h for the primary calling header

#include "Vt_covergroup_trans_simple__pch.h"

VL_ATTR_COLD void Vt_covergroup_trans_simple_t___eval_static__TOP__t(Vt_covergroup_trans_simple_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_simple_t___eval_static__TOP__t\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__cg_inst = VL_NEW(Vt_covergroup_trans_simple_t__03a__03acg, vlSymsp);
    ++(vlSymsp->__Vcoverage[8]);
    vlSelfRef.__PVT__cyc = 0U;
    ++(vlSymsp->__Vcoverage[9]);
}

VL_ATTR_COLD void Vt_covergroup_trans_simple_t___stl_sequent__TOP__t__0(Vt_covergroup_trans_simple_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_simple_t___stl_sequent__TOP__t__0\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSymsp->TOP.clk) ^ (IData)(vlSelfRef.__Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSymsp->TOP.clk, vlSelfRef.__Vtogcov__clk);
        vlSelfRef.__Vtogcov__clk = vlSymsp->TOP.clk;
    }
    if (((IData)(vlSelfRef.__PVT__state) ^ (IData)(vlSelfRef.__Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 2, vlSelfRef.__PVT__state, vlSelfRef.__Vtogcov__state);
        vlSelfRef.__Vtogcov__state = vlSelfRef.__PVT__state;
    }
}

VL_ATTR_COLD void Vt_covergroup_trans_simple_t___ctor_var_reset(Vt_covergroup_trans_simple_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_simple_t___ctor_var_reset\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->__PVT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9404372463396948974ull);
    vlSelf->__PVT__cyc = 0;
    vlSelf->__Vtogcov__clk = 0;
    vlSelf->__Vtogcov__state = 0;
}

VL_ATTR_COLD void Vt_covergroup_trans_simple_t___configure_coverage(Vt_covergroup_trans_simple_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_simple_t___configure_coverage\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_trans_simple.v", 9, 10, "", "v_toggle/t", "clk");
    vlSelf->__vlCoverToggleInsert(0, 2, 1, &(vlSymsp->__Vcoverage[2]), first, "test_regress/t/t_covergroup_trans_simple.v", 11, 16, "", "v_toggle/t", "state");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_covergroup_trans_simple.v", 21, 17, "", "v_line/t", "block", "21");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_covergroup_trans_simple.v", 23, 14, "", "v_line/t", "block", "23");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_covergroup_trans_simple.v", 29, 10, "", "v_line/t", "case", "29");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_covergroup_trans_simple.v", 30, 10, "", "v_line/t", "case", "30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_covergroup_trans_simple.v", 31, 10, "", "v_line/t", "case", "31");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "test_regress/t/t_covergroup_trans_simple.v", 32, 10, "", "v_line/t", "case", "32");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "test_regress/t/t_covergroup_trans_simple.v", 35, 12, "", "v_line/t", "if", "35-37");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "test_regress/t/t_covergroup_trans_simple.v", 33, 10, "", "v_line/t", "case", "33-34");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "test_regress/t/t_covergroup_trans_simple.v", 49, 8, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "test_regress/t/t_covergroup_trans_simple.v", 25, 4, "", "v_line/t", "block", "25-26,28,46");
}
