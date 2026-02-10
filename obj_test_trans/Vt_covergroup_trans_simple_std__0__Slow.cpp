// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_trans_simple.h for the primary calling header

#include "Vt_covergroup_trans_simple__pch.h"

VL_ATTR_COLD void Vt_covergroup_trans_simple_std___ctor_var_reset(Vt_covergroup_trans_simple_std* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_std___ctor_var_reset\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_trans_simple_std___configure_coverage(Vt_covergroup_trans_simple_std* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_std___configure_coverage\n"); );
    Vt_covergroup_trans_simple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[18]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 243, 16, "", "v_line/std", "block", "243-244");
}
