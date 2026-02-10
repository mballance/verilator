// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_dynamic.h for the primary calling header

#include "Vt_covergroup_dynamic__pch.h"

VL_ATTR_COLD void Vt_covergroup_dynamic_t___eval_initial__TOP__t(Vt_covergroup_dynamic_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_dynamic_t___eval_initial__TOP__t\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlClassRef<Vt_covergroup_dynamic_t__03a__03acg> __PVT__unnamedblk1__DOT__cg_inst;
    double __PVT__unnamedblk1__DOT__cov;
    __PVT__unnamedblk1__DOT__cov = 0;
    VlClassRef<Vt_covergroup_dynamic_t__03a__03acg> __PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg1;
    VlClassRef<Vt_covergroup_dynamic_t__03a__03acg> __PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg2;
    VlClassRef<Vt_covergroup_dynamic_t__03a__03acg> __PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg3;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout = 0;
    // Body
    VL_WRITEF_NX("Test 1: Single dynamic instance\n",0);
    __PVT__unnamedblk1__DOT__cg_inst = VL_NEW(Vt_covergroup_dynamic_t__03a__03acg, vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_covergroup_dynamic.v", 29)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
    VL_WRITEF_NX("  Initial coverage: %f\n",0,64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY(((0.0 != __PVT__unnamedblk1__DOT__cov)))) {
        VL_STOP_MT("test_regress/t/t_covergroup_dynamic.v", 31, "");
    } else {
        ++(vlSymsp->__Vcoverage[0]);
    }
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_covergroup_dynamic.v", 35)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_covergroup_dynamic.v", 36)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout;
    VL_WRITEF_NX("  After sampling low: %f\n",0,64,
                 __PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 49.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 51.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_dynamic.v", 38, "");
    } else {
        ++(vlSymsp->__Vcoverage[1]);
    }
    vlSelfRef.__PVT__data = 2U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_covergroup_dynamic.v", 42)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_covergroup_dynamic.v", 43)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout;
    VL_WRITEF_NX("  After sampling high: %f\n",0,64,
                 __PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 99.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 101.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_dynamic.v", 45, "");
    } else {
        ++(vlSymsp->__Vcoverage[5]);
    }
    VL_WRITEF_NX("Test 2: Multiple dynamic instances\n",0);
    __PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg1 
        = VL_NEW(Vt_covergroup_dynamic_t__03a__03acg, vlSymsp);
    __PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg2 
        = VL_NEW(Vt_covergroup_dynamic_t__03a__03acg, vlSymsp);
    __PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg3 
        = VL_NEW(Vt_covergroup_dynamic_t__03a__03acg, vlSymsp);
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg1, "test_regress/t/t_covergroup_dynamic.v", 58)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 2U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg2, "test_regress/t/t_covergroup_dynamic.v", 61)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 1U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg3, "test_regress/t/t_covergroup_dynamic.v", 64)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg1, "test_regress/t/t_covergroup_dynamic.v", 67)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout;
    VL_WRITEF_NX("  cg1 coverage: %f\n",0,64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 49.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 51.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_dynamic.v", 69, "");
    } else {
        ++(vlSymsp->__Vcoverage[9]);
    }
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg2, "test_regress/t/t_covergroup_dynamic.v", 71)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout;
    VL_WRITEF_NX("  cg2 coverage: %f\n",0,64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 49.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 51.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_dynamic.v", 73, "");
    } else {
        ++(vlSymsp->__Vcoverage[13]);
    }
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__unnamedblk2__DOT__cg3, "test_regress/t/t_covergroup_dynamic.v", 75)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout;
    VL_WRITEF_NX("  cg3 coverage: %f\n",0,64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 49.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 51.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_dynamic.v", 77, "");
    } else {
        ++(vlSymsp->__Vcoverage[17]);
    }
    VL_WRITEF_NX("Test 3: Instance reassignment\n",0);
    __PVT__unnamedblk1__DOT__cg_inst = VL_NEW(Vt_covergroup_dynamic_t__03a__03acg, vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_covergroup_dynamic.v", 85)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout;
    VL_WRITEF_NX("  New instance coverage: %f\n",0,
                 64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY(((0.0 != __PVT__unnamedblk1__DOT__cov)))) {
        VL_STOP_MT("test_regress/t/t_covergroup_dynamic.v", 87, "");
    } else {
        ++(vlSymsp->__Vcoverage[21]);
    }
    VL_WRITEF_NX("*-* All Finished *-*\n",0);
    VL_FINISH_MT("test_regress/t/t_covergroup_dynamic.v", 90, "");
    if ((__PVT__unnamedblk1__DOT__cov > 51.0)) {
        ++(vlSymsp->__Vcoverage[2]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 49.0)) {
        ++(vlSymsp->__Vcoverage[3]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 49.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 51.0))))) {
        ++(vlSymsp->__Vcoverage[4]);
    }
    if ((__PVT__unnamedblk1__DOT__cov > 101.0)) {
        ++(vlSymsp->__Vcoverage[6]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 99.0)) {
        ++(vlSymsp->__Vcoverage[7]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 99.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 101.0))))) {
        ++(vlSymsp->__Vcoverage[8]);
    }
    if ((__PVT__unnamedblk1__DOT__cov > 51.0)) {
        ++(vlSymsp->__Vcoverage[10]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 49.0)) {
        ++(vlSymsp->__Vcoverage[11]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 49.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 51.0))))) {
        ++(vlSymsp->__Vcoverage[12]);
    }
    if ((__PVT__unnamedblk1__DOT__cov > 51.0)) {
        ++(vlSymsp->__Vcoverage[14]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 49.0)) {
        ++(vlSymsp->__Vcoverage[15]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 49.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 51.0))))) {
        ++(vlSymsp->__Vcoverage[16]);
    }
    if ((__PVT__unnamedblk1__DOT__cov > 51.0)) {
        ++(vlSymsp->__Vcoverage[18]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 49.0)) {
        ++(vlSymsp->__Vcoverage[19]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 49.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 51.0))))) {
        ++(vlSymsp->__Vcoverage[20]);
    }
    ++(vlSymsp->__Vcoverage[22]);
}

VL_ATTR_COLD void Vt_covergroup_dynamic_t___ctor_var_reset(Vt_covergroup_dynamic_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_dynamic_t___ctor_var_reset\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT__data = 0;
}

VL_ATTR_COLD void Vt_covergroup_dynamic_t___configure_coverage(Vt_covergroup_dynamic_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_dynamic_t___configure_coverage\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_dynamic.v", 31, 8, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[1]), first, "test_regress/t/t_covergroup_dynamic.v", 38, 8, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "test_regress/t/t_covergroup_dynamic.v", 38, 22, "", "v_expr/t", "((cov > 51.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[3]), first, "test_regress/t/t_covergroup_dynamic.v", 38, 22, "", "v_expr/t", "((cov < 49.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "test_regress/t/t_covergroup_dynamic.v", 38, 22, "", "v_expr/t", "((cov < 49.0)==0 && (cov > 51.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "test_regress/t/t_covergroup_dynamic.v", 45, 8, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "test_regress/t/t_covergroup_dynamic.v", 45, 22, "", "v_expr/t", "((cov > 101.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "test_regress/t/t_covergroup_dynamic.v", 45, 22, "", "v_expr/t", "((cov < 99.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_covergroup_dynamic.v", 45, 22, "", "v_expr/t", "((cov < 99.0)==0 && (cov > 101.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_covergroup_dynamic.v", 69, 11, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_covergroup_dynamic.v", 69, 25, "", "v_expr/t", "((cov > 51.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_covergroup_dynamic.v", 69, 25, "", "v_expr/t", "((cov < 49.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_covergroup_dynamic.v", 69, 25, "", "v_expr/t", "((cov < 49.0)==0 && (cov > 51.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "test_regress/t/t_covergroup_dynamic.v", 73, 11, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "test_regress/t/t_covergroup_dynamic.v", 73, 25, "", "v_expr/t", "((cov > 51.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "test_regress/t/t_covergroup_dynamic.v", 73, 25, "", "v_expr/t", "((cov < 49.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "test_regress/t/t_covergroup_dynamic.v", 73, 25, "", "v_expr/t", "((cov < 49.0)==0 && (cov > 51.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "test_regress/t/t_covergroup_dynamic.v", 77, 11, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "test_regress/t/t_covergroup_dynamic.v", 77, 25, "", "v_expr/t", "((cov > 51.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "test_regress/t/t_covergroup_dynamic.v", 77, 25, "", "v_expr/t", "((cov < 49.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "test_regress/t/t_covergroup_dynamic.v", 77, 25, "", "v_expr/t", "((cov < 49.0)==0 && (cov > 51.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "test_regress/t/t_covergroup_dynamic.v", 87, 8, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "test_regress/t/t_covergroup_dynamic.v", 20, 4, "", "v_line/t", "block", "20,25-26,29-30,34-37,41-44,48-49,52-54,57-58,60-61,63-64,67-68,71-72,75-76,81-82,85-86,89-90");
}
