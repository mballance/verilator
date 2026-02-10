// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_empty.h for the primary calling header

#include "Vt_covergroup_empty__pch.h"

void Vt_covergroup_empty_t__03a__03acg_empty__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_empty__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_empty_t__03a__03acg_empty__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    get_coverage__Vfuncrtn = 0;
    ++(vlSymsp->__Vcoverage[30]);
}

Vt_covergroup_empty_t__03a__03acg_empty::Vt_covergroup_empty_t__03a__03acg_empty(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[26]);
}

void Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_sample(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_sample\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[27]);
}

void Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_start(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_start\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[28]);
}

void Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_stop(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_stop\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[29]);
}

void Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_get_inst_coverage(Vt_covergroup_empty__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    get_inst_coverage__Vfuncrtn = 0;
    ++(vlSymsp->__Vcoverage[31]);
}

void Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_empty__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
    // Locals
    double __Vfunc_get_inst_coverage__0__Vfuncout;
    __Vfunc_get_inst_coverage__0__Vfuncout = 0;
    // Body
    std::string covered_bins;
    covered_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_empty__Vclpkg.__PVT____Vint);
    std::string total_bins;
    total_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_empty__Vclpkg.__PVT____Vint);
    this->__VnoInFunc_get_inst_coverage(vlSymsp, covered_bins, total_bins, __Vfunc_get_inst_coverage__0__Vfuncout);
    get_inst_coverage__Vtcwrap_1_2__Vfuncrtn = __Vfunc_get_inst_coverage__0__Vfuncout;
    ++(vlSymsp->__Vcoverage[32]);
}

void Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_set_inst_name(Vt_covergroup_empty__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::__VnoInFunc_set_inst_name\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[33]);
}

void Vt_covergroup_empty_t__03a__03acg_empty::_ctor_var_reset(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    __PVT__option.__PVT__weight = 0;
    __PVT__option.__PVT__goal = 0;
    __PVT__option.__PVT__at_least = 0;
    __PVT__option.__PVT__auto_bin_max = 0;
    __PVT__option.__PVT__cross_num_print_missing = 0;
    __PVT__option.__PVT__cross_retain_auto_bins = 0;
    __PVT__option.__PVT__detect_overlap = 0;
    __PVT__option.__PVT__per_instance = 0;
    __PVT__option.__PVT__get_inst_coverage = 0;
    __PVT__type_option.__PVT__weight = 0;
    __PVT__type_option.__PVT__goal = 0;
    __PVT__type_option.__PVT__strobe = 0;
    __PVT__type_option.__PVT__merge_instances = 0;
    __PVT__type_option.__PVT__distribute_first = 0;
    __PVT__type_option.__PVT__real_interval = 0;
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_empty_t__03a__03acg_empty>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_empty_t__03a__03acg_empty::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_empty_t__03a__03acg_empty::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_empty_t__03a__03acg_empty::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    return (out);
}
