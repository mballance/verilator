// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_empty.h for the primary calling header

#include "Vt_covergroup_empty__pch.h"

VL_ATTR_COLD void Vt_covergroup_empty_t___eval_static__TOP__t(Vt_covergroup_empty_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___eval_static__TOP__t\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__cg_inst = VL_NEW(Vt_covergroup_empty_t__03a__03acg_empty, vlSymsp);
    ++(vlSymsp->__Vcoverage[18]);
}

VL_ATTR_COLD void Vt_covergroup_empty_t___stl_sequent__TOP__t__0(Vt_covergroup_empty_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___stl_sequent__TOP__t__0\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSymsp->TOP.clk) ^ (IData)(vlSelfRef.__Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSymsp->TOP.clk, vlSelfRef.__Vtogcov__clk);
        vlSelfRef.__Vtogcov__clk = vlSymsp->TOP.clk;
    }
    if (((IData)(vlSelfRef.__PVT__value) ^ (IData)(vlSelfRef.__Vtogcov__value))) {
        VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 2, vlSelfRef.__PVT__value, vlSelfRef.__Vtogcov__value);
        vlSelfRef.__Vtogcov__value = vlSelfRef.__PVT__value;
    }
}

VL_ATTR_COLD void Vt_covergroup_empty_t___ctor_var_reset(Vt_covergroup_empty_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___ctor_var_reset\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->__PVT__value = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10523578686933994953ull);
    vlSelf->__Vtogcov__clk = 0;
    vlSelf->__Vtogcov__value = 0;
}

VL_ATTR_COLD void Vt_covergroup_empty_t___configure_coverage(Vt_covergroup_empty_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___configure_coverage\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_empty.v", 12, 10, "", "v_toggle/t", "clk");
    vlSelf->__vlCoverToggleInsert(0, 7, 1, &(vlSymsp->__Vcoverage[2]), first, "test_regress/t/t_covergroup_empty.v", 14, 16, "", "v_toggle/t", "value");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "test_regress/t/t_covergroup_empty.v", 21, 23, "", "v_line/t", "block", "21");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "test_regress/t/t_covergroup_empty.v", 27, 7, "", "v_line/t", "block", "27-30");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "test_regress/t/t_covergroup_empty.v", 40, 10, "", "v_line/t", "if", "40-42");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "test_regress/t/t_covergroup_empty.v", 23, 4, "", "v_line/t", "block", "23-24,27,34,36-37");
}
