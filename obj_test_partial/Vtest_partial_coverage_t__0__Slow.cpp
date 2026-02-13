// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest_partial_coverage.h for the primary calling header

#include "Vtest_partial_coverage__pch.h"

VL_ATTR_COLD void Vtest_partial_coverage_t___eval_initial__TOP__t(Vtest_partial_coverage_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vtest_partial_coverage_t___eval_initial__TOP__t\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlClassRef<Vtest_partial_coverage_cg> __PVT__unnamedblk1__DOT__cg_inst;
    double __Vtask_get_coverage__2__Vfuncout;
    __Vtask_get_coverage__2__Vfuncout = 0;
    double __Vtask_get_coverage__4__Vfuncout;
    __Vtask_get_coverage__4__Vfuncout = 0;
    // Body
    __PVT__unnamedblk1__DOT__cg_inst = VL_NEW(Vtest_partial_coverage_cg, vlSymsp);
    vlSelfRef.__PVT__addr = 0x0000000aU;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "/tmp/test_partial_coverage.v", 17)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("Coverage (only low): %0.1f%%\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "/tmp/test_partial_coverage.v", 19)
                     ->__VnoInFunc_get_coverage(vlSymsp, __Vtask_get_coverage__2__Vfuncout);
                }(), __Vtask_get_coverage__2__Vfuncout));
    vlSelfRef.__PVT__addr = 0x000000c8U;
    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "/tmp/test_partial_coverage.v", 23)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("Coverage (both): %0.1f%%\n",0,64,
                 ([&]() {
                    VL_NULL_CHECK(__PVT__unnamedblk1__DOT__cg_inst, "/tmp/test_partial_coverage.v", 25)
                  ->__VnoInFunc_get_coverage(vlSymsp, __Vtask_get_coverage__4__Vfuncout);
                }(), __Vtask_get_coverage__4__Vfuncout));
    VL_WRITEF_NX("*-* All Finished *-*\n",0);
    VL_FINISH_MT("/tmp/test_partial_coverage.v", 28, "");
    ++(vlSymsp->__Vcoverage[7]);
}

VL_ATTR_COLD void Vtest_partial_coverage_t___ctor_var_reset(Vtest_partial_coverage_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vtest_partial_coverage_t___ctor_var_reset\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT__addr = 0;
}

VL_ATTR_COLD void Vtest_partial_coverage_t___configure_coverage(Vtest_partial_coverage_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vtest_partial_coverage_t___configure_coverage\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "/tmp/test_partial_coverage.v", 11, 4, "", "v_line/t", "block", "11,13,16-17,19,22-23,25,27-28");
}
