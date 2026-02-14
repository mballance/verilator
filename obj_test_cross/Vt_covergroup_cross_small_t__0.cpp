// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_cross_small.h for the primary calling header

#include "Vt_covergroup_cross_small__pch.h"

void Vt_covergroup_cross_small_t___nba_sequent__TOP__t__0(Vt_covergroup_cross_small_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_cross_small_t___nba_sequent__TOP__t__0\n"); );
    Vt_covergroup_cross_small__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout = 0;
    IData/*31:0*/ __Vdly__cyc;
    __Vdly__cyc = 0;
    // Body
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_cross_small.v", 41)->__VnoInFunc_sample(vlSymsp);
    __Vdly__cyc = vlSelfRef.__PVT__cyc;
    __Vdly__cyc = ((IData)(1U) + vlSelfRef.__PVT__cyc);
    vlSelfRef.__PVT__a = (0x0000000fU & vlSelfRef.__PVT__cyc);
    vlSelfRef.__PVT__b = (0x0000000fU & (vlSelfRef.__PVT__cyc 
                                         >> 4U));
    if (VL_UNLIKELY(((0x00000014U == vlSelfRef.__PVT__cyc)))) {
        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_cross_small.v", 51)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout);
        vlSelfRef.__PVT__unnamedblk1__DOT__inst_cov 
            = __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
        VL_WRITEF_NX("Coverage: %0.1f%%\n*-* All Finished *-*\n",0,
                     64,vlSelfRef.__PVT__unnamedblk1__DOT__inst_cov);
        VL_FINISH_MT("test_regress/t/t_covergroup_cross_small.v", 56, "");
    }
    vlSelfRef.__PVT__cyc = __Vdly__cyc;
}
