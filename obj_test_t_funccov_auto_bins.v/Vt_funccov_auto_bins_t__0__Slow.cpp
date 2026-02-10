// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_auto_bins.h for the primary calling header

#include "Vt_funccov_auto_bins__pch.h"

VL_ATTR_COLD void Vt_funccov_auto_bins_t___eval_initial__TOP__t(Vt_funccov_auto_bins_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_funccov_auto_bins_t___eval_initial__TOP__t\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlClassRef<Vt_funccov_auto_bins_t__03a__03acg> __PVT__unnamedblk1__DOT__cg_inst;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout = 0;
    // Body
    __PVT__unnamedblk1__DOT__cg_inst = VL_NEW(Vt_funccov_auto_bins_t__03a__03acg, vlSymsp);
    VL_WRITEF_NX("Coverage initial: %f%% (expected ~0.00%%)\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 21)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__1__Vfuncout));
    vlSelfRef.__PVT__data = 0U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 25)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("Coverage after 0: %f%% (expected ~25.00%%)\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 26)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__3__Vfuncout));
    vlSelfRef.__PVT__data = 2U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 30)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("Coverage after 2: %f%% (expected ~50.00%%)\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 31)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout));
    vlSelfRef.__PVT__data = 5U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 35)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("Coverage after 5: %f%% (expected ~75.00%%)\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 36)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout));
    vlSelfRef.__PVT__data = 7U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 40)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("Coverage complete: %f%% (expected ~100.00%%)\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "test_regress/t/t_funccov_auto_bins.v", 41)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout));
    VL_WRITEF_NX("*-* All Finished *-*\n",0);
    VL_FINISH_MT("test_regress/t/t_funccov_auto_bins.v", 44, "");
}

VL_ATTR_COLD void Vt_funccov_auto_bins_t___ctor_var_reset(Vt_funccov_auto_bins_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_funccov_auto_bins_t___ctor_var_reset\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__data = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10363016170300574568ull);
}

VL_ATTR_COLD void Vt_funccov_auto_bins_t___configure_coverage(Vt_funccov_auto_bins_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_funccov_auto_bins_t___configure_coverage\n"); );
    Vt_funccov_auto_bins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
