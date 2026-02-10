// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_empty.h for the primary calling header

#include "Vt_covergroup_empty__pch.h"

VlCoroutine Vt_covergroup_empty_t___eval_initial__TOP__t__Vtiming__0(Vt_covergroup_empty_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___eval_initial__TOP__t__Vtiming__0\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ unnamedblk1_1__DOT____Vrepeat0;
    unnamedblk1_1__DOT____Vrepeat0 = 0;
    double __PVT__unnamedblk1__DOT__cov;
    __PVT__unnamedblk1__DOT__cov = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout = 0;
    // Body
    vlSelfRef.__PVT__value = 0U;
    unnamedblk1_1__DOT____Vrepeat0 = 5U;
    while (VL_LTS_III(32, 0U, unnamedblk1_1__DOT____Vrepeat0)) {
        co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                                nullptr, 
                                                                "@(posedge clk)", 
                                                                "test_regress/t/t_covergroup_empty.v", 
                                                                28);
        vlSelfRef.__PVT__value = (0x000000ffU & ((IData)(1U) 
                                                 + (IData)(vlSelfRef.__PVT__value)));
        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_empty.v", 30)->__VnoInFunc_sample(vlSymsp);
        unnamedblk1_1__DOT____Vrepeat0 = (unnamedblk1_1__DOT____Vrepeat0 
                                          - (IData)(1U));
        ++(vlSymsp->__Vcoverage[19]);
    }
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_empty.v", 36)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout;
    VL_WRITEF_NX("Empty covergroup coverage: %f%%\n",0,
                 64,__PVT__unnamedblk1__DOT__cov);
    if ((__PVT__unnamedblk1__DOT__cov >= 9.99000000000000057e+01)) {
        VL_WRITEF_NX("*-* All Finished *-*\n",0);
        VL_FINISH_MT("test_regress/t/t_covergroup_empty.v", 42, "");
        ++(vlSymsp->__Vcoverage[20]);
    } else {
        VL_WRITEF_NX("ERROR: Expected 100%% coverage for empty covergroup, got %f%%\n",0,
                     64,__PVT__unnamedblk1__DOT__cov);
        VL_STOP_MT("test_regress/t/t_covergroup_empty.v", 45, "");
    }
    ++(vlSymsp->__Vcoverage[21]);
    co_return;
}

void Vt_covergroup_empty_t___ico_sequent__TOP__t__0(Vt_covergroup_empty_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___ico_sequent__TOP__t__0\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSymsp->TOP.clk) ^ (IData)(vlSelfRef.__Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSymsp->TOP.clk, vlSelfRef.__Vtogcov__clk);
        vlSelfRef.__Vtogcov__clk = vlSymsp->TOP.clk;
    }
}

void Vt_covergroup_empty_t___act_sequent__TOP__t__0(Vt_covergroup_empty_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___act_sequent__TOP__t__0\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.__PVT__value) ^ (IData)(vlSelfRef.__Vtogcov__value))) {
        VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 2, vlSelfRef.__PVT__value, vlSelfRef.__Vtogcov__value);
        vlSelfRef.__Vtogcov__value = vlSelfRef.__PVT__value;
    }
}
