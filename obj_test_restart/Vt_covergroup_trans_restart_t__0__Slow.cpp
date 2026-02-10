// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_trans_restart.h for the primary calling header

#include "Vt_covergroup_trans_restart__pch.h"

VL_ATTR_COLD void Vt_covergroup_trans_restart_t___eval_static__TOP__t(Vt_covergroup_trans_restart_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_restart_t___eval_static__TOP__t\n"); );
    Vt_covergroup_trans_restart__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__errors = 0U;
    ++(vlSymsp->__Vcoverage[6]);
    vlSelfRef.__PVT__cg_inst = VL_NEW(Vt_covergroup_trans_restart_t__03a__03acg, vlSymsp);
    ++(vlSymsp->__Vcoverage[7]);
}

VL_ATTR_COLD void Vt_covergroup_trans_restart_t___eval_initial__TOP__t(Vt_covergroup_trans_restart_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_restart_t___eval_initial__TOP__t\n"); );
    Vt_covergroup_trans_restart__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout = 0;
    // Body
    vlSelfRef.__PVT__state = 1U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 23)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("After state=1: seqpos should be 1\n",0);
    vlSelfRef.__PVT__state = 2U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 27)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("After state=2: seqpos should be 2\n",0);
    vlSelfRef.__PVT__state = 1U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 31)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("After state=1 (restart): seqpos should be 1\n",0);
    vlSelfRef.__PVT__state = 2U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 35)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("After state=2: seqpos should be 2\n",0);
    vlSelfRef.__PVT__state = 3U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 39)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("After state=3: bin should have incremented, seqpos reset to 0\n",0);
    VL_WRITEF_NX("Coverage: %f%%\n",0,64,([&]() {
                    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 43)
                                          ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout));
    if (VL_UNLIKELY(((([&]() {
                            VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 44)
                       ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout);
                        }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout) 
                      < 99.0)))) {
        VL_WRITEF_NX("ERROR: Expected 100%% coverage, got %f%%\n",0,
                     64,([&]() {
                        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_restart.v", 45)
                         ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout);
                    }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout));
        vlSelfRef.__PVT__errors = ((IData)(1U) + vlSelfRef.__PVT__errors);
        ++(vlSymsp->__Vcoverage[8]);
    } else {
        ++(vlSymsp->__Vcoverage[9]);
    }
    if ((0U == vlSelfRef.__PVT__errors)) {
        VL_WRITEF_NX("*-* All Finished *-*\n",0);
        ++(vlSymsp->__Vcoverage[10]);
    } else {
        VL_WRITEF_NX("*-* FAILED with %0d errors *-*\n",0,
                     32,vlSelfRef.__PVT__errors);
        ++(vlSymsp->__Vcoverage[11]);
    }
    VL_FINISH_MT("test_regress/t/t_covergroup_trans_restart.v", 54, "");
    ++(vlSymsp->__Vcoverage[12]);
}

VL_ATTR_COLD void Vt_covergroup_trans_restart_t___stl_sequent__TOP__t__0(Vt_covergroup_trans_restart_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_restart_t___stl_sequent__TOP__t__0\n"); );
    Vt_covergroup_trans_restart__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.__PVT__state) ^ (IData)(vlSelfRef.__Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 0, vlSelfRef.__PVT__state, vlSelfRef.__Vtogcov__state);
        vlSelfRef.__Vtogcov__state = vlSelfRef.__PVT__state;
    }
}

VL_ATTR_COLD void Vt_covergroup_trans_restart_t___ctor_var_reset(Vt_covergroup_trans_restart_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_restart_t___ctor_var_reset\n"); );
    Vt_covergroup_trans_restart__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9404372463396948974ull);
    vlSelf->__PVT__errors = 0;
    vlSelf->__Vtogcov__state = 0;
}

VL_ATTR_COLD void Vt_covergroup_trans_restart_t___configure_coverage(Vt_covergroup_trans_restart_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_restart_t___configure_coverage\n"); );
    Vt_covergroup_trans_restart__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 2, 1, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_trans_restart.v", 6, 16, "", "v_toggle/t", "state");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "test_regress/t/t_covergroup_trans_restart.v", 7, 17, "", "v_line/t", "block", "7");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "test_regress/t/t_covergroup_trans_restart.v", 15, 17, "", "v_line/t", "block", "15");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_covergroup_trans_restart.v", 44, 7, "", "v_branch/t", "if", "44-46");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_covergroup_trans_restart.v", 44, 8, "", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_covergroup_trans_restart.v", 49, 7, "", "v_branch/t", "if", "49-50");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_covergroup_trans_restart.v", 49, 8, "", "v_branch/t", "else", "51-52");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_covergroup_trans_restart.v", 17, 4, "", "v_line/t", "block", "17,22-24,26-28,30-32,34-36,38-40,43,54");
}
