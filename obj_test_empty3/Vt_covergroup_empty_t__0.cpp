// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_empty.h for the primary calling header

#include "Vt_covergroup_empty__pch.h"

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

void Vt_covergroup_empty_t___nba_sequent__TOP__t__0(Vt_covergroup_empty_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_empty_t___nba_sequent__TOP__t__0\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout = 0;
    IData/*31:0*/ __Vdly__cyc;
    __Vdly__cyc = 0;
    // Body
    __Vdly__cyc = vlSelfRef.__PVT__cyc;
    vlSelfRef.__PVT__value = (0x000000ffU & ((IData)(1U) 
                                             + (IData)(vlSelfRef.__PVT__value)));
    __Vdly__cyc = ((IData)(1U) + vlSelfRef.__PVT__cyc);
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_empty.v", 29)->__VnoInFunc_sample(vlSymsp);
    if (VL_UNLIKELY(((5U == vlSelfRef.__PVT__cyc)))) {
        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_empty.v", 35)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout);
        vlSelfRef.__PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout;
        VL_WRITEF_NX("Empty covergroup coverage: %f%%\n",0,
                     64,vlSelfRef.__PVT__unnamedblk1__DOT__cov);
        if ((vlSelfRef.__PVT__unnamedblk1__DOT__cov 
             >= 9.99000000000000057e+01)) {
            VL_WRITEF_NX("*-* All Finished *-*\n",0);
            VL_FINISH_MT("test_regress/t/t_covergroup_empty.v", 41, "");
            ++(vlSymsp->__Vcoverage[20]);
        } else {
            VL_WRITEF_NX("ERROR: Expected 100%% coverage for empty covergroup, got %f%%\n",0,
                         64,vlSelfRef.__PVT__unnamedblk1__DOT__cov);
            VL_STOP_MT("test_regress/t/t_covergroup_empty.v", 44, "");
        }
        ++(vlSymsp->__Vcoverage[21]);
    } else {
        ++(vlSymsp->__Vcoverage[22]);
    }
    if (VL_UNLIKELY((VL_LTS_III(32, 0x0000000aU, vlSelfRef.__PVT__cyc)))) {
        VL_WRITEF_NX("ERROR: Test timed out\n",0);
        VL_STOP_MT("test_regress/t/t_covergroup_empty.v", 51, "");
    } else {
        ++(vlSymsp->__Vcoverage[23]);
    }
    ++(vlSymsp->__Vcoverage[24]);
    vlSelfRef.__PVT__cyc = __Vdly__cyc;
    if (((IData)(vlSelfRef.__PVT__value) ^ (IData)(vlSelfRef.__Vtogcov__value))) {
        VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 2, vlSelfRef.__PVT__value, vlSelfRef.__Vtogcov__value);
        vlSelfRef.__Vtogcov__value = vlSelfRef.__PVT__value;
    }
}
