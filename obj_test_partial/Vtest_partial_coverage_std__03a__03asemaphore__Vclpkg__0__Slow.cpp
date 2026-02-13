// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest_partial_coverage.h for the primary calling header

#include "Vtest_partial_coverage__pch.h"

VL_ATTR_COLD void Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg___ctor_var_reset(Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg___ctor_var_reset\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg___configure_coverage(Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg___configure_coverage\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 103, 14, "", "v_line/semaphore", "block", "103-104");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 107, 19, "", "v_line/semaphore", "block", "107-108");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 111, 10, "", "v_line/semaphore", "block", "111");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 121, 7, "", "v_branch/semaphore", "if", "121-123");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 121, 8, "", "v_branch/semaphore", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 120, 18, "", "v_line/semaphore", "block", "120,125");
}

VL_ATTR_COLD void Vtest_partial_coverage_std__03a__03asemaphore___configure_coverage(Vtest_partial_coverage_std__03a__03asemaphore* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03asemaphore___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
