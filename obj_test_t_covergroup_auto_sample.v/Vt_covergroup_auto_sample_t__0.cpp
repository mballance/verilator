// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_auto_sample.h for the primary calling header

#include "Vt_covergroup_auto_sample__pch.h"

void Vt_covergroup_auto_sample_t___nba_sequent__TOP__t__0(Vt_covergroup_auto_sample_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_auto_sample_t___nba_sequent__TOP__t__0\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_auto_sample.v", 23)->__VnoInFunc_sample(vlSymsp);
    __Vdly__cyc = vlSelfRef.__PVT__cyc;
    __Vdly__cyc = ((IData)(1U) + vlSelfRef.__PVT__cyc);
    if ((0U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__data = 0U;
    } else if ((1U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__data = 1U;
    } else if ((2U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__data = 2U;
    } else if ((3U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__data = 3U;
    } else if (VL_UNLIKELY(((4U == vlSelfRef.__PVT__cyc)))) {
        VL_WRITEF_NX("Coverage: %f%%\n",0,64,([&]() {
                        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_auto_sample.v", 36)
                                              ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout);
                    }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout));
        if ((([&]() {
                        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_auto_sample.v", 37)
              ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout);
                    }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__2__Vfuncout) 
             >= 99.0)) {
            VL_WRITEF_NX("*-* All Finished *-*\n",0);
            VL_FINISH_MT("test_regress/t/t_covergroup_auto_sample.v", 39, "");
        } else {
            VL_WRITEF_NX("ERROR: Expected 100%% coverage, got %f%%\n",0,
                         64,([&]() {
                            VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_auto_sample.v", 41)
                             ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout);
                        }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout));
            VL_STOP_MT("test_regress/t/t_covergroup_auto_sample.v", 42, "");
        }
    }
    if (VL_UNLIKELY((VL_LTS_III(32, 0x0000000aU, vlSelfRef.__PVT__cyc)))) {
        VL_WRITEF_NX("ERROR: Test timed out\n",0);
        VL_STOP_MT("test_regress/t/t_covergroup_auto_sample.v", 52, "");
    }
    vlSelfRef.__PVT__cyc = __Vdly__cyc;
}
