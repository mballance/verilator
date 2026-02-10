// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#include "Vt_covergroup_bins_default_illegal__pch.h"

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t___eval_static__TOP__t(Vt_covergroup_bins_default_illegal_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_default_illegal_t___eval_static__TOP__t\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__error_count = 0U;
    ++(vlSymsp->__Vcoverage[8]);
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t___eval_initial__TOP__t(Vt_covergroup_bins_default_illegal_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_default_illegal_t___eval_initial__TOP__t\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlClassRef<Vt_covergroup_bins_default_illegal_t__03a__03acg_default> __PVT__unnamedblk1__DOT__cg1;
    VlClassRef<Vt_covergroup_bins_default_illegal_t__03a__03acg_valid> __PVT__unnamedblk1__DOT__cg2;
    double __PVT__unnamedblk1__DOT__cov;
    __PVT__unnamedblk1__DOT__cov = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout = 0;
    // Body
    __PVT__unnamedblk1__DOT__cg1 = VL_NEW(Vt_covergroup_bins_default_illegal_t__03a__03acg_default, vlSymsp);
    __PVT__unnamedblk1__DOT__cg2 = VL_NEW(Vt_covergroup_bins_default_illegal_t__03a__03acg_valid, vlSymsp);
    VL_WRITEF_NX("Test 1: default bins\n",0);
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_default_illegal.v", 40)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 1U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_default_illegal.v", 41)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 5U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_default_illegal.v", 42)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 7U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_default_illegal.v", 43)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 0x0aU;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_default_illegal.v", 44)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_default_illegal.v", 46)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout;
    VL_WRITEF_NX("  Coverage with default bins: %0.1f%%\n",0,
                 64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 99.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 101.0))))) {
        VL_WRITEF_NX("%%Error: Expected 100%%, got %0.1f%%\n",0,
                     64,__PVT__unnamedblk1__DOT__cov);
        vlSelfRef.__PVT__error_count = ((IData)(1U) 
                                        + vlSelfRef.__PVT__error_count);
        ++(vlSymsp->__Vcoverage[9]);
    } else {
        ++(vlSymsp->__Vcoverage[10]);
    }
    VL_WRITEF_NX("Test 2: illegal_bins (sampling valid values)\n",0);
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_default_illegal.v", 57)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 5U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_default_illegal.v", 58)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 0x0aU;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_default_illegal.v", 59)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_default_illegal.v", 61)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout;
    VL_WRITEF_NX("  Coverage with illegal_bins: %0.1f%%\n",0,
                 64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 99.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 101.0))))) {
        vlSelfRef.__PVT__error_count = ((IData)(1U) 
                                        + vlSelfRef.__PVT__error_count);
        VL_WRITEF_NX("%%Error: Expected 100%%, got %0.1f%%\n",0,
                     64,__PVT__unnamedblk1__DOT__cov);
        ++(vlSymsp->__Vcoverage[14]);
    } else {
        ++(vlSymsp->__Vcoverage[15]);
    }
    if (VL_LIKELY(((0U == vlSelfRef.__PVT__error_count)))) {
        VL_WRITEF_NX("*-* All Finished *-*\n",0);
        ++(vlSymsp->__Vcoverage[19]);
    } else {
        VL_WRITEF_NX("%%Error: %0d test(s) failed\n",0,
                     32,vlSelfRef.__PVT__error_count);
        VL_STOP_MT("test_regress/t/t_covergroup_bins_default_illegal.v", 74, "");
    }
    VL_FINISH_MT("test_regress/t/t_covergroup_bins_default_illegal.v", 77, "");
    if ((__PVT__unnamedblk1__DOT__cov > 101.0)) {
        ++(vlSymsp->__Vcoverage[11]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 99.0)) {
        ++(vlSymsp->__Vcoverage[12]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 99.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 101.0))))) {
        ++(vlSymsp->__Vcoverage[13]);
    }
    if ((__PVT__unnamedblk1__DOT__cov > 101.0)) {
        ++(vlSymsp->__Vcoverage[16]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 99.0)) {
        ++(vlSymsp->__Vcoverage[17]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 99.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 101.0))))) {
        ++(vlSymsp->__Vcoverage[18]);
    }
    ++(vlSymsp->__Vcoverage[20]);
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t___stl_sequent__TOP__t__0(Vt_covergroup_bins_default_illegal_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_default_illegal_t___stl_sequent__TOP__t__0\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.__PVT__data) ^ (IData)(vlSelfRef.__Vtogcov__data))) {
        VL_COV_TOGGLE_CHG_ST_I(4, vlSymsp->__Vcoverage + 0, vlSelfRef.__PVT__data, vlSelfRef.__Vtogcov__data);
        vlSelfRef.__Vtogcov__data = vlSelfRef.__PVT__data;
    }
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t___ctor_var_reset(Vt_covergroup_bins_default_illegal_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_default_illegal_t___ctor_var_reset\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__data = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10363016170300574568ull);
    vlSelf->__PVT__error_count = 0;
    vlSelf->__Vtogcov__data = 0;
}

VL_ATTR_COLD void Vt_covergroup_bins_default_illegal_t___configure_coverage(Vt_covergroup_bins_default_illegal_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_default_illegal_t___configure_coverage\n"); );
    Vt_covergroup_bins_default_illegal__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 3, 1, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 11, 16, "", "v_toggle/t", "data");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 12, 22, "", "v_line/t", "block", "12");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 50, 7, "", "v_branch/t", "if", "50-52");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 50, 8, "", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 50, 22, "", "v_expr/t", "((cov > 101.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 50, 22, "", "v_expr/t", "((cov < 99.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 50, 22, "", "v_expr/t", "((cov < 99.0)==0 && (cov > 101.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 65, 7, "", "v_branch/t", "if", "65-67");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 65, 8, "", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 65, 22, "", "v_expr/t", "((cov > 101.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 65, 22, "", "v_expr/t", "((cov < 99.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 65, 22, "", "v_expr/t", "((cov < 99.0)==0 && (cov > 101.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 70, 7, "", "v_line/t", "if", "70-71");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "test_regress/t/t_covergroup_bins_default_illegal.v", 30, 4, "", "v_line/t", "block", "30,35-36,39-44,46-47,56-59,61-62,77");
}
