// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_autobins.h for the primary calling header

#include "Vt_covergroup_autobins__pch.h"

VlCoroutine Vt_covergroup_autobins_t___eval_initial__TOP__t__Vtiming__0(Vt_covergroup_autobins_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_autobins_t___eval_initial__TOP__t__Vtiming__0\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__10__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__10__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__15__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__15__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__17__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__17__Vfuncout = 0;
    // Body
    vlSelfRef.__PVT__unnamedblk1__DOT__cg1_inst = VL_NEW(Vt_covergroup_autobins_t__03a__03acg1, vlSymsp);
    vlSelfRef.__PVT__unnamedblk1__DOT__cg2_inst = VL_NEW(Vt_covergroup_autobins_t__03a__03acg2, vlSymsp);
    vlSelfRef.__PVT__unnamedblk1__DOT__cg3_inst = VL_NEW(Vt_covergroup_autobins_t__03a__03acg3, vlSymsp);
    vlSelfRef.__PVT__unnamedblk1__DOT__cg4_inst = VL_NEW(Vt_covergroup_autobins_t__03a__03acg4, vlSymsp);
    vlSelfRef.__PVT__unnamedblk1__DOT__cg5_inst = VL_NEW(Vt_covergroup_autobins_t__03a__03acg5, vlSymsp);
    vlSelfRef.__PVT__data3 = 0U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            66);
    vlSelfRef.__PVT__data3 = 1U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            67);
    vlSelfRef.__PVT__data3 = 2U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            68);
    vlSelfRef.__PVT__data2 = 0U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            75);
    vlSelfRef.__PVT__data2 = 1U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            76);
    vlSelfRef.__PVT__data2 = 2U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            77);
    vlSelfRef.__PVT__data2 = 3U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            78);
    vlSelfRef.__PVT__data2 = 0U;
    vlSelfRef.__PVT__data3 = 0U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            81);
    vlSelfRef.__PVT__data2 = 3U;
    vlSelfRef.__PVT__data3 = 4U;
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            82);
    co_await vlSymsp->TOP.__VtrigSched_hc5d4c2fc__0.trigger(0U, 
                                                            nullptr, 
                                                            "@(posedge clk)", 
                                                            "test_regress/t/t_covergroup_autobins.v", 
                                                            84);
    VL_WRITEF_NX("CG1 (8 autobins): %0.1f%%\n",0,64,
                 ([&]() {
                    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg1_inst, "test_regress/t/t_covergroup_autobins.v", 86)
                  ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__5__Vfuncout));
    VL_WRITEF_NX("CG2 (4 autobins w/ option): %0.1f%%\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg2_inst, "test_regress/t/t_covergroup_autobins.v", 87)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout));
    VL_WRITEF_NX("CG3 (7 autobins w/ ignore): %0.1f%%\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg3_inst, "test_regress/t/t_covergroup_autobins.v", 88)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout));
    VL_WRITEF_NX("CG4 (4 autobins): %0.1f%%\n",0,64,
                 ([&]() {
                    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg4_inst, "test_regress/t/t_covergroup_autobins.v", 89)
                  ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout));
    VL_WRITEF_NX("CG5 (2 autobins w/ option): %0.1f%%\n",0,
                 64,([&]() {
                    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg5_inst, "test_regress/t/t_covergroup_autobins.v", 90)
                     ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__9__Vfuncout));
    if (VL_UNLIKELY((((([&]() {
                                VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg1_inst, "test_regress/t/t_covergroup_autobins.v", 93)
                        ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__10__Vfuncout);
                            }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__10__Vfuncout) 
                       < 30.0) || (([&]() {
                                VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg1_inst, "test_regress/t/t_covergroup_autobins.v", 93)
                                    ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout);
                            }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__11__Vfuncout) 
                                   > 45.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_autobins.v", 94, "");
    }
    if (VL_UNLIKELY((((([&]() {
                                VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg2_inst, "test_regress/t/t_covergroup_autobins.v", 95)
                        ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout);
                            }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__12__Vfuncout) 
                       < 40.0) || (([&]() {
                                VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg2_inst, "test_regress/t/t_covergroup_autobins.v", 95)
                                    ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout);
                            }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__13__Vfuncout) 
                                   > 60.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_autobins.v", 96, "");
    }
    if (VL_UNLIKELY((((([&]() {
                                VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg3_inst, "test_regress/t/t_covergroup_autobins.v", 97)
                        ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout);
                            }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__14__Vfuncout) 
                       < 20.0) || (([&]() {
                                VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg3_inst, "test_regress/t/t_covergroup_autobins.v", 97)
                                    ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__15__Vfuncout);
                            }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__15__Vfuncout) 
                                   > 35.0))))) {
        VL_STOP_MT("test_regress/t/t_covergroup_autobins.v", 98, "");
    }
    if (VL_UNLIKELY(((([&]() {
                            VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg4_inst, "test_regress/t/t_covergroup_autobins.v", 99)
                       ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout);
                        }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__16__Vfuncout) 
                      < 95.0)))) {
        VL_STOP_MT("test_regress/t/t_covergroup_autobins.v", 100, "");
    }
    if (VL_UNLIKELY(((([&]() {
                            VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg5_inst, "test_regress/t/t_covergroup_autobins.v", 101)
                       ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__17__Vfuncout);
                        }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__17__Vfuncout) 
                      < 95.0)))) {
        VL_STOP_MT("test_regress/t/t_covergroup_autobins.v", 102, "");
    }
    VL_WRITEF_NX("*-* All Finished *-*\n",0);
    VL_FINISH_MT("test_regress/t/t_covergroup_autobins.v", 105, "");
    co_return;
}

void Vt_covergroup_autobins_t___nba_sequent__TOP__t__0(Vt_covergroup_autobins_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_autobins_t___nba_sequent__TOP__t__0\n"); );
    Vt_covergroup_autobins__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg1_inst, "test_regress/t/t_covergroup_autobins.v", 53)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg2_inst, "test_regress/t/t_covergroup_autobins.v", 54)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg3_inst, "test_regress/t/t_covergroup_autobins.v", 55)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg4_inst, "test_regress/t/t_covergroup_autobins.v", 56)->__VnoInFunc_sample(vlSymsp);
    VL_NULL_CHECK(vlSelfRef.__PVT__unnamedblk1__DOT__cg5_inst, "test_regress/t/t_covergroup_autobins.v", 57)->__VnoInFunc_sample(vlSymsp);
}
