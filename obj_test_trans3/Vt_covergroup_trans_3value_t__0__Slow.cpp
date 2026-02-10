// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_trans_3value.h for the primary calling header

#include "Vt_covergroup_trans_3value__pch.h"

VL_ATTR_COLD void Vt_covergroup_trans_3value_t___eval_static__TOP__t(Vt_covergroup_trans_3value_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_3value_t___eval_static__TOP__t\n"); );
    Vt_covergroup_trans_3value__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__errors = 0U;
    ++(vlSymsp->__Vcoverage[6]);
    vlSelfRef.__PVT__cg_inst = VL_NEW(Vt_covergroup_trans_3value_t__03a__03acg, vlSymsp);
    ++(vlSymsp->__Vcoverage[7]);
}

VL_ATTR_COLD void Vt_covergroup_trans_3value_t___eval_initial__TOP__t(Vt_covergroup_trans_3value_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_3value_t___eval_initial__TOP__t\n"); );
    Vt_covergroup_trans_3value__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout = 0;
    double __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout;
    __Vtask_get_inst_coverage__Vtcwrap_1_2__8__Vfuncout = 0;
    // Body
    vlSelfRef.__PVT__state = 0U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 21)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__state = 1U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 24)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__state = 2U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 27)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__state = 3U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 31)->__VnoInFunc_sample(vlSymsp);
    vlSelfRef.__PVT__state = 4U;
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 34)->__VnoInFunc_sample(vlSymsp);
    VL_WRITEF_NX("Coverage: %f%%\n",0,64,([&]() {
                    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 37)
                                          ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout);
                }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__6__Vfuncout));
    if (VL_UNLIKELY(((([&]() {
                            VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 38)
                       ->__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(vlSymsp, __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout);
                        }(), __Vtask_get_inst_coverage__Vtcwrap_1_2__7__Vfuncout) 
                      < 99.0)))) {
        VL_WRITEF_NX("ERROR: Expected 100%% coverage, got %f%%\n",0,
                     64,([&]() {
                        VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "test_regress/t/t_covergroup_trans_3value.v", 39)
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
    VL_FINISH_MT("test_regress/t/t_covergroup_trans_3value.v", 48, "");
    ++(vlSymsp->__Vcoverage[12]);
}

VL_ATTR_COLD void Vt_covergroup_trans_3value_t___stl_sequent__TOP__t__0(Vt_covergroup_trans_3value_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_3value_t___stl_sequent__TOP__t__0\n"); );
    Vt_covergroup_trans_3value__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.__PVT__state) ^ (IData)(vlSelfRef.__Vtogcov__state))) {
        VL_COV_TOGGLE_CHG_ST_I(3, vlSymsp->__Vcoverage + 0, vlSelfRef.__PVT__state, vlSelfRef.__Vtogcov__state);
        vlSelfRef.__Vtogcov__state = vlSelfRef.__PVT__state;
    }
}

VL_ATTR_COLD void Vt_covergroup_trans_3value_t___ctor_var_reset(Vt_covergroup_trans_3value_t* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_3value_t___ctor_var_reset\n"); );
    Vt_covergroup_trans_3value__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9404372463396948974ull);
    vlSelf->__PVT__errors = 0;
    vlSelf->__Vtogcov__state = 0;
}

VL_ATTR_COLD void Vt_covergroup_trans_3value_t___configure_coverage(Vt_covergroup_trans_3value_t* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vt_covergroup_trans_3value_t___configure_coverage\n"); );
    Vt_covergroup_trans_3value__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 2, 1, &(vlSymsp->__Vcoverage[0]), first, "test_regress/t/t_covergroup_trans_3value.v", 6, 16, "", "v_toggle/t", "state");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "test_regress/t/t_covergroup_trans_3value.v", 7, 17, "", "v_line/t", "block", "7");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "test_regress/t/t_covergroup_trans_3value.v", 16, 17, "", "v_line/t", "block", "16");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "test_regress/t/t_covergroup_trans_3value.v", 38, 7, "", "v_branch/t", "if", "38-40");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "test_regress/t/t_covergroup_trans_3value.v", 38, 8, "", "v_branch/t", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "test_regress/t/t_covergroup_trans_3value.v", 43, 7, "", "v_branch/t", "if", "43-44");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "test_regress/t/t_covergroup_trans_3value.v", 43, 8, "", "v_branch/t", "else", "45-46");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "test_regress/t/t_covergroup_trans_3value.v", 18, 4, "", "v_line/t", "block", "18,20-21,23-24,26-27,30-31,33-34,37,48");
}
