// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_auto_sample.h for the primary calling header

#include "Vt_covergroup_auto_sample__pch.h"

VL_ATTR_COLD void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___ctor_var_reset(Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT____Vint = 0;
}

VL_ATTR_COLD void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___configure_coverage(Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_auto_sample__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}

VL_ATTR_COLD void Vt_covergroup_auto_sample_t__03a__03acg___configure_coverage(Vt_covergroup_auto_sample_t__03a__03acg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_auto_sample_t__03a__03acg___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
