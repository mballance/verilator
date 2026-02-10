// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_advanced.h for the primary calling header

#include "Vt_covergroup_bins_advanced__pch.h"

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_advanced_t__03a__03acg_wildcard__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[47]);
    get_coverage__Vfuncrtn = 0.0;
}

Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::Vt_covergroup_bins_advanced_t__03a__03acg_wildcard(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[43]);
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg_wildcard.data.pattern0", &(this->__PVT____Vcov__pattern0), "page", "v_funccov/cg_wildcard", "filename", "test_regress/t/t_covergroup_bins_advanced.v", "lineno", "37", "column", "24", "bin", "pattern0");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg_wildcard.data.pattern1", &(this->__PVT____Vcov__pattern1), "page", "v_funccov/cg_wildcard", "filename", "test_regress/t/t_covergroup_bins_advanced.v", "lineno", "38", "column", "24", "bin", "pattern1");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg_wildcard.data.pattern2", &(this->__PVT____Vcov__pattern2), "page", "v_funccov/cg_wildcard", "filename", "test_regress/t/t_covergroup_bins_advanced.v", "lineno", "39", "column", "24", "bin", "pattern2");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg_wildcard.data.pattern3", &(this->__PVT____Vcov__pattern3), "page", "v_funccov/cg_wildcard", "filename", "test_regress/t/t_covergroup_bins_advanced.v", "lineno", "40", "column", "24", "bin", "pattern3");
}

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_sample(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_sample\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[44]);
    if ((0U == (0x0cU & (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__pattern0 = ((IData)(1U) 
                                         + this->__PVT____Vcov__pattern0);
    }
    if ((4U == (0x0cU & (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__pattern1 = ((IData)(1U) 
                                         + this->__PVT____Vcov__pattern1);
    }
    if ((8U == (0x0cU & (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__pattern2 = ((IData)(1U) 
                                         + this->__PVT____Vcov__pattern2);
    }
    if ((0x0cU == (0x0cU & (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__pattern3 = ((IData)(1U) 
                                         + this->__PVT____Vcov__pattern3);
    }
}

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_start(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_start\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[45]);
}

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_stop(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_stop\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[46]);
}

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_get_inst_coverage(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[48]);
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov__pattern0)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__pattern1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__pattern2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__pattern3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 4.0));
}

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
    // Locals
    double __Vfunc_get_inst_coverage__0__Vfuncout;
    __Vfunc_get_inst_coverage__0__Vfuncout = 0;
    // Body
    std::string covered_bins;
    covered_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_wildcard__Vclpkg.__PVT____Vint);
    std::string total_bins;
    total_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_wildcard__Vclpkg.__PVT____Vint);
    this->__VnoInFunc_get_inst_coverage(vlSymsp, covered_bins, total_bins, __Vfunc_get_inst_coverage__0__Vfuncout);
    get_inst_coverage__Vtcwrap_1_2__Vfuncrtn = __Vfunc_get_inst_coverage__0__Vfuncout;
    ++(vlSymsp->__Vcoverage[49]);
}

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_set_inst_name(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::__VnoInFunc_set_inst_name\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[50]);
}

void Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::_ctor_var_reset(Vt_covergroup_bins_advanced__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::_ctor_var_reset\n"); );
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
    __PVT____Vcov__pattern0 = VL_SCOPED_RAND_RESET_I(32, 17608603728703439748ULL, 10849443269725890667ull);
    __PVT____Vcov__pattern1 = VL_SCOPED_RAND_RESET_I(32, 17608603728703439748ULL, 6806531253821405048ull);
    __PVT____Vcov__pattern2 = VL_SCOPED_RAND_RESET_I(32, 17608603728703439748ULL, 9134181629925541044ull);
    __PVT____Vcov__pattern3 = VL_SCOPED_RAND_RESET_I(32, 17608603728703439748ULL, 16582160234740303411ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_bins_advanced_t__03a__03acg_wildcard>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_advanced_t__03a__03acg_wildcard::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov__pattern0:" + VL_TO_STRING(__PVT____Vcov__pattern0);
    out += ", __Vcov__pattern1:" + VL_TO_STRING(__PVT____Vcov__pattern1);
    out += ", __Vcov__pattern2:" + VL_TO_STRING(__PVT____Vcov__pattern2);
    out += ", __Vcov__pattern3:" + VL_TO_STRING(__PVT____Vcov__pattern3);
    return (out);
}
