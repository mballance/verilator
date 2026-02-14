// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_negative_ranges.h for the primary calling header

#include "Vt_covergroup_negative_ranges__pch.h"

void Vt_covergroup_negative_ranges_t___nba_sequent__TOP__t__0(Vt_covergroup_negative_ranges_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_negative_ranges_t___nba_sequent__TOP__t__0\n"); );
    Vt_covergroup_negative_ranges__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout = 0;
    IData/*31:0*/ __Vdly__cyc;
    __Vdly__cyc = 0;
    // Body
    __Vdly__cyc = vlSelfRef.__PVT__cyc;
    __Vdly__cyc = ((IData)(1U) + vlSelfRef.__PVT__cyc);
    if ((0U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__value = 0xffffffceU;
    } else if ((1U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__value = 0U;
    } else if ((2U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__value = 0x00000032U;
    } else if ((3U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__value = 0xfffffffbU;
    } else if ((4U == vlSelfRef.__PVT__cyc)) {
        vlSelfRef.__PVT__value = 5U;
    } else if (VL_UNLIKELY(((5U == vlSelfRef.__PVT__cyc)))) {
        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_negative_ranges.v", 43)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout);
        vlSelfRef.__PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
        VL_WRITEF_NX("Coverage with negative ranges: %f%%\n",0,
                     64,vlSelfRef.__PVT__unnamedblk1__DOT__cov);
        if ((vlSelfRef.__PVT__unnamedblk1__DOT__cov 
             >= 99.0)) {
            VL_WRITEF_NX("*-* All Finished *-*\n",0);
            VL_FINISH_MT("test_regress/t/t_covergroup_negative_ranges.v", 49, "");
        } else {
            VL_WRITEF_NX("ERROR: Expected 100%% coverage, got %f%%\n",0,
                         64,vlSelfRef.__PVT__unnamedblk1__DOT__cov);
            VL_STOP_MT("test_regress/t/t_covergroup_negative_ranges.v", 52, "");
        }
    }
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_negative_ranges.v", 58)->__VnoInFunc_sample(vlSymsp);
    if (VL_UNLIKELY((VL_LTS_III(32, 0x0000000aU, vlSelfRef.__PVT__cyc)))) {
        VL_WRITEF_NX("ERROR: Test timed out\n",0);
        VL_STOP_MT("test_regress/t/t_covergroup_negative_ranges.v", 62, "");
    }
    vlSelfRef.__PVT__cyc = __Vdly__cyc;
}
