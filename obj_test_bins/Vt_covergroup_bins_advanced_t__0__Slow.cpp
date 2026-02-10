// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_advanced.h for the primary calling header

#include "Vt_covergroup_bins_advanced__pch.h"

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t___eval_static__TOP__t(Vt_covergroup_bins_advanced_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_advanced_t___eval_static__TOP__t\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__error_count = 0U;
    ++(vlSymsp->__Vcoverage[8]);
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t___eval_initial__TOP__t(Vt_covergroup_bins_advanced_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_advanced_t___eval_initial__TOP__t\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlClassRef<Vt_covergroup_bins_advanced_t__03a__03acg_ignore> __PVT__unnamedblk1__DOT__cg1;
    VlClassRef<Vt_covergroup_bins_advanced_t__03a__03acg_array> __PVT__unnamedblk1__DOT__cg2;
    VlClassRef<Vt_covergroup_bins_advanced_t__03a__03acg_wildcard> __PVT__unnamedblk1__DOT__cg3;
    double __PVT__unnamedblk1__DOT__cov;
    __PVT__unnamedblk1__DOT__cov = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout = 0;
    // Body
    __PVT__unnamedblk1__DOT__cg1 = VL_NEW(Vt_covergroup_bins_advanced_t__03a__03acg_ignore, vlSymsp);
    __PVT__unnamedblk1__DOT__cg2 = VL_NEW(Vt_covergroup_bins_advanced_t__03a__03acg_array, vlSymsp);
    __PVT__unnamedblk1__DOT__cg3 = VL_NEW(Vt_covergroup_bins_advanced_t__03a__03acg_wildcard, vlSymsp);
    VL_WRITEF_NX("Test 1: ignore_bins\n",0);
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_advanced.v", 56)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 5U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_advanced.v", 57)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 9U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_advanced.v", 58)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 0x0cU;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_advanced.v", 59)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 0x0dU;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_advanced.v", 60)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg1, "test_regress/t/t_covergroup_bins_advanced.v", 62)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout;
    VL_WRITEF_NX("  Coverage with ignore_bins: %0.1f%% (expect 100%%)\n",0,
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
    VL_WRITEF_NX("Test 2: Array bins (explicit values)\n",0);
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_advanced.v", 72)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 1U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_advanced.v", 73)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 2U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_advanced.v", 74)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg2, "test_regress/t/t_covergroup_bins_advanced.v", 77)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout;
    VL_WRITEF_NX("  Coverage with array bins: %0.1f%% (expect 75%%)\n",0,
                 64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 74.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 76.0))))) {
        vlSelfRef.__PVT__error_count = ((IData)(1U) 
                                        + vlSelfRef.__PVT__error_count);
        VL_WRITEF_NX("%%Error: Expected 75%%, got %0.1f%%\n",0,
                     64,__PVT__unnamedblk1__DOT__cov);
        ++(vlSymsp->__Vcoverage[14]);
    } else {
        ++(vlSymsp->__Vcoverage[15]);
    }
    VL_WRITEF_NX("Test 3: Wildcard bins\n",0);
    vlSelfRef.__PVT__data = 2U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg3, "test_regress/t/t_covergroup_bins_advanced.v", 87)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 5U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg3, "test_regress/t/t_covergroup_bins_advanced.v", 88)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 0x0aU;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg3, "test_regress/t/t_covergroup_bins_advanced.v", 89)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg3, "test_regress/t/t_covergroup_bins_advanced.v", 92)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout);
    __PVT__unnamedblk1__DOT__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout;
    VL_WRITEF_NX("  Coverage with wildcard bins: %0.1f%% (expect 75%%)\n",0,
                 64,__PVT__unnamedblk1__DOT__cov);
    if (VL_UNLIKELY((((__PVT__unnamedblk1__DOT__cov 
                       < 74.0) | (__PVT__unnamedblk1__DOT__cov 
                                  > 76.0))))) {
        vlSelfRef.__PVT__error_count = ((IData)(1U) 
                                        + vlSelfRef.__PVT__error_count);
        VL_WRITEF_NX("%%Error: Expected 75%%, got %0.1f%%\n",0,
                     64,__PVT__unnamedblk1__DOT__cov);
        ++(vlSymsp->__Vcoverage[19]);
    } else {
        ++(vlSymsp->__Vcoverage[20]);
    }
    if (VL_LIKELY(((0U == vlSelfRef.__PVT__error_count)))) {
        VL_WRITEF_NX("*-* All Finished *-*\n",0);
        ++(vlSymsp->__Vcoverage[24]);
    } else {
        VL_WRITEF_NX("%%Error: %0d test(s) failed\n",0,
                     32,vlSelfRef.__PVT__error_count);
        VL_STOP_MT("test_regress/t/t_covergroup_bins_advanced.v", 104, "");
    }
    VL_FINISH_MT("test_regress/t/t_covergroup_bins_advanced.v", 107, "");
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
    if ((__PVT__unnamedblk1__DOT__cov > 76.0)) {
        ++(vlSymsp->__Vcoverage[16]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 74.0)) {
        ++(vlSymsp->__Vcoverage[17]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 74.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 76.0))))) {
        ++(vlSymsp->__Vcoverage[18]);
    }
    if ((__PVT__unnamedblk1__DOT__cov > 76.0)) {
        ++(vlSymsp->__Vcoverage[21]);
    }
    if ((__PVT__unnamedblk1__DOT__cov < 74.0)) {
        ++(vlSymsp->__Vcoverage[22]);
    }
    if ((1U & ((~ (__PVT__unnamedblk1__DOT__cov < 74.0)) 
               & (~ (__PVT__unnamedblk1__DOT__cov > 76.0))))) {
        ++(vlSymsp->__Vcoverage[23]);
    }
    ++(vlSymsp->__Vcoverage[25]);
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t___stl_sequent__TOP__t__0(Vt_covergroup_bins_advanced_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_advanced_t___stl_sequent__TOP__t__0\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.__PVT__data) ^ (IData)(vlSelfRef.__Vtogcov__data))) {
        VL_COV_TOGGLE_CHG_ST_I(4, vlSymsp->__Vcoverage + 0, vlSelfRef.__PVT__data, vlSelfRef.__Vtogcov__data);
        vlSelfRef.__Vtogcov__data = vlSelfRef.__PVT__data;
    }
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t___ctor_var_reset(Vt_covergroup_bins_advanced_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_advanced_t___ctor_var_reset\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__data = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10363016170300574568ull);
    vlSelf->__PVT__error_count = 0;
    vlSelf->__Vtogcov__data = 0;
}

VL_ATTR_COLD void Vt_covergroup_bins_advanced_t___configure_coverage(Vt_covergroup_bins_advanced_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_bins_advanced_t___configure_coverage\n"); );
    Vt_covergroup_bins_advanced__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 3, 1, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_bins_advanced.v", 14, 16, "", "v_toggle/t", "data");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_covergroup_bins_advanced.v", 15, 22, "", "v_line/t", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_covergroup_bins_advanced.v", 65, 7, "", "v_branch/t", "if", "65-67");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_covergroup_bins_advanced.v", 65, 8, "", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_covergroup_bins_advanced.v", 65, 22, "", "v_expr/t", "((cov > 101.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_covergroup_bins_advanced.v", 65, 22, "", "v_expr/t", "((cov < 99.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "test_regress/t/t_covergroup_bins_advanced.v", 65, 22, "", "v_expr/t", "((cov < 99.0)==0 && (cov > 101.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "test_regress/t/t_covergroup_bins_advanced.v", 80, 7, "", "v_branch/t", "if", "80-82");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "test_regress/t/t_covergroup_bins_advanced.v", 80, 8, "", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "test_regress/t/t_covergroup_bins_advanced.v", 80, 22, "", "v_expr/t", "((cov > 76.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "test_regress/t/t_covergroup_bins_advanced.v", 80, 22, "", "v_expr/t", "((cov < 74.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "test_regress/t/t_covergroup_bins_advanced.v", 80, 22, "", "v_expr/t", "((cov < 74.0)==0 && (cov > 76.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[19]), first, "test_regress/t/t_covergroup_bins_advanced.v", 95, 7, "", "v_branch/t", "if", "95-97");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[20]), first, "test_regress/t/t_covergroup_bins_advanced.v", 95, 8, "", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[21]), first, "test_regress/t/t_covergroup_bins_advanced.v", 95, 22, "", "v_expr/t", "((cov > 76.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[22]), first, "test_regress/t/t_covergroup_bins_advanced.v", 95, 22, "", "v_expr/t", "((cov < 74.0)==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[23]), first, "test_regress/t/t_covergroup_bins_advanced.v", 95, 22, "", "v_expr/t", "((cov < 74.0)==0 && (cov > 76.0)==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[24]), first, "test_regress/t/t_covergroup_bins_advanced.v", 100, 7, "", "v_line/t", "if", "100-101");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[25]), first, "test_regress/t/t_covergroup_bins_advanced.v", 44, 4, "", "v_line/t", "block", "44,50-52,55-60,62-63,71-74,77-78,86-89,92-93,107");
}
