// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_empty.h for the primary calling header

#include "Vt_covergroup_empty__pch.h"

VL_ATTR_COLD void Vt_covergroup_empty_std__03a__03aprocess__Vclpkg___ctor_var_reset(Vt_covergroup_empty_std__03a__03aprocess__Vclpkg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_empty_std__03a__03aprocess__Vclpkg___ctor_var_reset\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vt_covergroup_empty_std__03a__03aprocess__Vclpkg___configure_coverage(Vt_covergroup_empty_std__03a__03aprocess__Vclpkg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_empty_std__03a__03aprocess__Vclpkg___configure_coverage\n"); );
    Vt_covergroup_empty__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[40]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 142, 29, "", "v_line/process", "block", "142-143,147");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[41]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 150, 29, "", "v_line/process", "block", "150");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[42]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 156, 20, "", "v_line/process", "block", "156,160");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[43]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 164, 19, "", "v_line/process", "block", "164-165");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[44]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 172, 19, "", "v_line/process", "block", "172-173");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[45]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 176, 10, "", "v_line/process", "block", "176");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[46]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 182, 17, "", "v_line/process", "block", "182");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[47]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 229, 21, "", "v_line/process", "block", "229,231,233-234");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[48]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 237, 19, "", "v_line/process", "block", "237-238");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[49]), first, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 130, 3, "", "v_line/process", "block", "130");
}

VL_ATTR_COLD void Vt_covergroup_empty_std__03a__03aprocess___configure_coverage(Vt_covergroup_empty_std__03a__03aprocess* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess___configure_coverage\n"); );
    (void)vlSelf;  // Prevent unused variable warning
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
}
