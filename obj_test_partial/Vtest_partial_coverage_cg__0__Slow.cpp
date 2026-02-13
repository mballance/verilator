// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest_partial_coverage.h for the primary calling header

#include "Vtest_partial_coverage__pch.h"

VL_ATTR_COLD void Vtest_partial_coverage_cg___ctor_var_reset(Vtest_partial_coverage_cg* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg___ctor_var_reset\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT__option.__PVT__weight = 0;
    vlSelf->__PVT__option.__PVT__goal = 0;
    vlSelf->__PVT__option.__PVT__at_least = 0;
    vlSelf->__PVT__option.__PVT__auto_bin_max = 0;
    vlSelf->__PVT__option.__PVT__cross_num_print_missing = 0;
    vlSelf->__PVT__option.__PVT__cross_retain_auto_bins = 0;
    vlSelf->__PVT__option.__PVT__detect_overlap = 0;
    vlSelf->__PVT__option.__PVT__per_instance = 0;
    vlSelf->__PVT__option.__PVT__get_inst_coverage = 0;
    vlSelf->__PVT__type_option.__PVT__weight = 0;
    vlSelf->__PVT__type_option.__PVT__goal = 0;
    vlSelf->__PVT__type_option.__PVT__strobe = 0;
    vlSelf->__PVT__type_option.__PVT__merge_instances = 0;
    vlSelf->__PVT__type_option.__PVT__distribute_first = 0;
    vlSelf->__PVT__type_option.__PVT__real_interval = 0;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->__PVT____Vcov_cp_addr_low = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5089053638012428342ull);
    vlSelf->__PVT____Vcov_cp_addr_high = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9085254158901929104ull);
}

VL_ATTR_COLD void Vtest_partial_coverage_cg___configure_coverage(Vtest_partial_coverage_cg* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg___configure_coverage\n"); );
    Vtest_partial_coverage__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[0]), first, "/tmp/test_partial_coverage.v", 4, 4, "", "v_line/cg", "block", "4-7");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[1]), first, "/tmp/test_partial_coverage.v", 4, 15, "", "v_line/cg", "block", "4");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "/tmp/test_partial_coverage.v", 4, 15, "", "v_line/cg", "block", "4");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[3]), first, "/tmp/test_partial_coverage.v", 4, 15, "", "v_line/cg", "block", "4");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "/tmp/test_partial_coverage.v", 4, 15, "", "v_line/cg", "block", "4");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "/tmp/test_partial_coverage.v", 4, 15, "", "v_line/cg", "block", "4");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "/tmp/test_partial_coverage.v", 4, 15, "", "v_line/cg", "block", "4");
}
