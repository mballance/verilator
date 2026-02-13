// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest_partial_coverage.h for the primary calling header

#include "Vtest_partial_coverage__pch.h"

VL_ATTR_COLD void Vtest_partial_coverage_std___ctor_var_reset(Vtest_partial_coverage_std* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_std___ctor_var_reset\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtest_partial_coverage_std___configure_coverage(Vtest_partial_coverage_std* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_std___configure_coverage\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 243, 16, "", "v_line/std", "block", "243-244");
}
