// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_trans_simple.h for the primary calling header

#include "Vt_covergroup_trans_simple__pch.h"

void Vt_covergroup_trans_simple_t___ico_sequent__TOP__t__0(Vt_covergroup_trans_simple_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_simple_t___ico_sequent__TOP__t__0\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSymsp->TOP.clk) ^ (IData)(vlSelfRef.__Vtogcov__clk))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSymsp->TOP.clk, vlSelfRef.__Vtogcov__clk);
        vlSelfRef.__Vtogcov__clk = vlSymsp->TOP.clk;
    }
}

void Vt_covergroup_trans_simple_t___nba_sequent__TOP__t__0(Vt_covergroup_trans_simple_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_simple_t___nba_sequent__TOP__t__0\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout = 0;
    IData/*31:0*/ __Vdly__cyc;
    __Vdly__cyc = 0;
    // Body
    __Vdly__cyc = vlSelfRef.__PVT__cyc;
    __Vdly__cyc = ((IData)(1U) + vlSelfRef.__PVT__cyc);
    if ((0U == vlSelfRef.__PVT__cyc)) {
        ++(vlSymsp->__Vcoverage[10]);
        vlSelfRef.__PVT__state = 0U;
    } else if ((1U == vlSelfRef.__PVT__cyc)) {
        ++(vlSymsp->__Vcoverage[11]);
        vlSelfRef.__PVT__state = 1U;
    } else if ((2U == vlSelfRef.__PVT__cyc)) {
        ++(vlSymsp->__Vcoverage[12]);
        vlSelfRef.__PVT__state = 2U;
    } else if ((3U == vlSelfRef.__PVT__cyc)) {
        ++(vlSymsp->__Vcoverage[13]);
        vlSelfRef.__PVT__state = 3U;
    } else if (VL_UNLIKELY(((4U == vlSelfRef.__PVT__cyc)))) {
        VL_WRITEF_NX("Coverage: %f%%\n",0,64,([&]() {
                        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_simple.v", 34)
                                              ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout);
                    }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout));
        if ((([&]() {
                        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_simple.v", 35)
              ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout);
                    }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout) 
             >= 99.0)) {
            VL_WRITEF_NX("*-* All Finished *-*\n",0);
            VL_FINISH_MT("test_regress/t/t_covergroup_trans_simple.v", 37, "");
            ++(vlSymsp->__Vcoverage[14]);
        } else {
            VL_WRITEF_NX("ERROR: Expected 100%% coverage, got %f%%\n",0,
                         64,([&]() {
                            VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_simple.v", 39)
                             ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout);
                        }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout));
            VL_STOP_MT("test_regress/t/t_covergroup_trans_simple.v", 40, "");
        }
        ++(vlSymsp->__Vcoverage[15]);
    }
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_simple.v", 46)->__VnoInFunc_sample(vlSymsp);
    if (VL_UNLIKELY((VL_LTS_III(32, 0x0000000aU, vlSelfRef.__PVT__cyc)))) {
        VL_WRITEF_NX("ERROR: Test timed out\n",0);
        VL_STOP_MT("test_regress/t/t_covergroup_trans_simple.v", 51, "");
    } else {
        ++(vlSymsp->__Vcoverage[16]);
    }
    ++(vlSymsp->__Vcoverage[17]);
    vlSelfRef.__PVT__cyc = __Vdly__cyc;
    if (((IData)(vlSelfRef.__PVT__state) ^ (IData)(vlSelfRef.__Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 2, vlSelfRef.__PVT__state, vlSelfRef.__Vtogcov__state);
        vlSelfRef.__Vtogcov__state = vlSelfRef.__PVT__state;
    }
}
