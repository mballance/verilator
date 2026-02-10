// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_dynamic.h for the primary calling header

#include "Vt_covergroup_dynamic__pch.h"

VL_ATTR_COLD void Vt_covergroup_dynamic_std__03a__03asemaphore__Vclpkg___ctor_var_reset(Vt_covergroup_dynamic_std__03a__03asemaphore__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_dynamic_std__03a__03asemaphore__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_dynamic_std__03a__03asemaphore__Vclpkg___configure_coverage(Vt_covergroup_dynamic_std__03a__03asemaphore__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_dynamic_std__03a__03asemaphore__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_dynamic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[32]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 103, 14, "", "v_line/semaphore", "block", "103-104");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[33]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 107, 19, "", "v_line/semaphore", "block", "107-108");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[34]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 111, 10, "", "v_line/semaphore", "block", "111");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[35]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 121, 7, "", "v_branch/semaphore", "if", "121-123");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[36]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 121, 8, "", "v_branch/semaphore", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[37]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 120, 18, "", "v_line/semaphore", "block", "120,125");
}

VL_ATTR_COLD void Vt_covergroup_dynamic_std__03a__03asemaphore___configure_coverage(Vt_covergroup_dynamic_std__03a__03asemaphore* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_dynamic_std__03a__03asemaphore___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
