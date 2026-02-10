// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_bin_counts.h for the primary calling header

#include "Vt_funccov_bin_counts__pch.h"

VL_ATTR_COLD void Vt_funccov_bin_counts_t___eval_initial__TOP__t(Vt_funccov_bin_counts_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_funccov_bin_counts_t___eval_initial__TOP__t\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlClassRef<Vt_funccov_bin_counts_t__03a__03acg> __PVT__cg_inst;
    double __PVT__check_coverage__Vstatic__cov;
    __PVT__check_coverage__Vstatic__cov = 0;
    double __Vtask_check_coverage__7__expected;
    __Vtask_check_coverage__7__expected = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout = 0;
    // Body
    __PVT__cg_inst = VL_NEW(Vt_funccov_bin_counts_t__03a__03acg, vlSymsp);
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__cg_inst, "test_regress/t/t_funccov_bin_counts.v", 28)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 1U;
    VL_NULL_CHECK(__PVT__cg_inst, "test_regress/t/t_funccov_bin_counts.v", 29)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 2U;
    VL_NULL_CHECK(__PVT__cg_inst, "test_regress/t/t_funccov_bin_counts.v", 30)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 2U;
    VL_NULL_CHECK(__PVT__cg_inst, "test_regress/t/t_funccov_bin_counts.v", 31)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 5U;
    VL_NULL_CHECK(__PVT__cg_inst, "test_regress/t/t_funccov_bin_counts.v", 32)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__data = 0x0aU;
    VL_NULL_CHECK(__PVT__cg_inst, "test_regress/t/t_funccov_bin_counts.v", 33)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__Vtask_check_coverage__7__label = "final"s;
    __Vtask_check_coverage__7__expected = 100.0;
    VL_NULL_CHECK(__PVT__cg_inst, "test_regress/t/t_funccov_bin_counts.v", 44)->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout);
    __PVT__check_coverage__Vstatic__cov = __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout;
    VL_WRITEF_NX("Coverage %@: %0.2f%% (expected ~%0.2f%%)\n",0,
                 -1,&(vlSelfRef.__Vtask_check_coverage__7__label),
                 64,__PVT__check_coverage__Vstatic__cov,
                 64,__Vtask_check_coverage__7__expected);
    if (VL_UNLIKELY((((__PVT__check_coverage__Vstatic__cov 
                       < (__Vtask_check_coverage__7__expected 
                          - 5.00000000000000000e-01)) 
                      | (__PVT__check_coverage__Vstatic__cov 
                         > (5.00000000000000000e-01 
                            + __Vtask_check_coverage__7__expected)))))) {
        VL_WRITEF_NX("[%0t] %%Error: t_funccov_bin_counts.v:47: Assertion failed in %Nt.check_coverage: Coverage mismatch: got %0.2f%%, expected ~%0.2f%%\n",0,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name(),
                     64,__PVT__check_coverage__Vstatic__cov,
                     64,__Vtask_check_coverage__7__expected);
        VL_STOP_MT("test_regress/t/t_funccov_bin_counts.v", 47, "");
        VL_STOP_MT("test_regress/t/t_funccov_bin_counts.v", 48, "");
    } else {
        ++(vlSymsp->__Vcoverage[9]);
    }
    if ((__PVT__check_coverage__Vstatic__cov > (5.00000000000000000e-01 
                                                + __Vtask_check_coverage__7__expected))) {
        ++(vlSymsp->__Vcoverage[10]);
    }
    if ((__PVT__check_coverage__Vstatic__cov < (__Vtask_check_coverage__7__expected 
                                                - 5.00000000000000000e-01))) {
        ++(vlSymsp->__Vcoverage[11]);
    }
    if ((1U & ((~ (__PVT__check_coverage__Vstatic__cov 
                   < (__Vtask_check_coverage__7__expected 
                      - 5.00000000000000000e-01))) 
               & (~ (__PVT__check_coverage__Vstatic__cov 
                     > (5.00000000000000000e-01 + __Vtask_check_coverage__7__expected)))))) {
        ++(vlSymsp->__Vcoverage[12]);
    }
    ++(vlSymsp->__Vcoverage[13]);
    VL_WRITEF_NX("*-* All Finished *-*\n",0);
    VL_FINISH_MT("test_regress/t/t_funccov_bin_counts.v", 39, "");
    ++(vlSymsp->__Vcoverage[8]);
}

VL_ATTR_COLD void Vt_funccov_bin_counts_t___stl_sequent__TOP__t__0(Vt_funccov_bin_counts_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_funccov_bin_counts_t___stl_sequent__TOP__t__0\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.__PVT__data) ^ (IData)(vlSelfRef.__Vtogcov__data))) {
        VL_COV_TOGGLE_CHG_ST_I(4, vlSymsp->__Vcoverage + 0, vlSelfRef.__PVT__data, vlSelfRef.__Vtogcov__data);
        vlSelfRef.__Vtogcov__data = vlSelfRef.__PVT__data;
    }
}

VL_ATTR_COLD void Vt_funccov_bin_counts_t___ctor_var_reset(Vt_funccov_bin_counts_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_funccov_bin_counts_t___ctor_var_reset\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__data = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10363016170300574568ull);
    vlSelf->__Vtogcov__data = 0;
}

VL_ATTR_COLD void Vt_funccov_bin_counts_t___configure_coverage(Vt_funccov_bin_counts_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_funccov_bin_counts_t___configure_coverage\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 3, 1, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_funccov_bin_counts.v", 11, 17, "", "v_toggle/t", "data");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_funccov_bin_counts.v", 24, 5, "", "v_line/t", "block", "24-25,28-33,36,38-39");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_funccov_bin_counts.v", 46, 10, "", "v_line/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_funccov_bin_counts.v", 46, 34, "", "v_expr/t", "((cov > (expected + 0.5))==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_funccov_bin_counts.v", 46, 34, "", "v_expr/t", "((cov < (expected - 0.5))==1) => 1", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_funccov_bin_counts.v", 46, 34, "", "v_expr/t", "((cov < (expected - 0.5))==0 && (cov > (expected + 0.5))==0) => 0", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "test_regress/t/t_funccov_bin_counts.v", 42, 10, "", "v_line/t", "block", "42,44-45");
}
