// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_bin_counts.h for the primary calling header

#include "Vt_funccov_bin_counts__pch.h"

VL_ATTR_COLD void Vt_funccov_bin_counts_std___ctor_var_reset(Vt_funccov_bin_counts_std* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_std___ctor_var_reset\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_funccov_bin_counts_std___configure_coverage(Vt_funccov_bin_counts_std* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_std___configure_coverage\n"); );
    Vt_funccov_bin_counts__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 243, 16, "", "v_line/std", "block", "243-244");
}
