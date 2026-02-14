// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_negative_ranges.h for the primary calling header

#include "Vt_covergroup_negative_ranges__pch.h"

void Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    get_coverage__Vfuncrtn = 0.0;
}

Vt_covergroup_negative_ranges_t__03a__03acg::Vt_covergroup_negative_ranges_t__03a__03acg(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
}

void Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_sample(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_sample\n"); );
    // Body
    if ((0xffffff9cU <= vlSymsp->TOP__t.__PVT__value)) {
        this->__PVT____Vcov_cp_neg_negative = ((IData)(1U) 
                                               + this->__PVT____Vcov_cp_neg_negative);
    }
    if ((0U == vlSymsp->TOP__t.__PVT__value)) {
        this->__PVT____Vcov_cp_neg_zero = ((IData)(1U) 
                                           + this->__PVT____Vcov_cp_neg_zero);
    }
    if (((1U <= vlSymsp->TOP__t.__PVT__value) & (0x00000064U 
                                                 >= vlSymsp->TOP__t.__PVT__value))) {
        this->__PVT____Vcov_cp_neg_positive = ((IData)(1U) 
                                               + this->__PVT____Vcov_cp_neg_positive);
    }
    if (((0xfffffff6U <= vlSymsp->TOP__t.__PVT__value) 
         & (0x0000000aU >= vlSymsp->TOP__t.__PVT__value))) {
        this->__PVT____Vcov_cp_neg_mixed = ((IData)(1U) 
                                            + this->__PVT____Vcov_cp_neg_mixed);
    }
}

void Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_get_inst_coverage(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov_cp_neg_negative)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_neg_zero)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_neg_positive)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_neg_mixed)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 4.0));
}

void Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
    // Locals
    double __Vfunc_get_inst_coverage__0__Vfuncout;
    __Vfunc_get_inst_coverage__0__Vfuncout = 0;
    // Body
    std::string covered_bins;
    covered_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg__Vclpkg.__PVT____Vint);
    std::string total_bins;
    total_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg__Vclpkg.__PVT____Vint);
    this->__VnoInFunc_get_inst_coverage(vlSymsp, covered_bins, total_bins, __Vfunc_get_inst_coverage__0__Vfuncout);
    get_inst_coverage__Vtcwrap_1_2__Vfuncrtn = __Vfunc_get_inst_coverage__0__Vfuncout;
}

void Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_set_inst_name(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::__VnoInFunc_set_inst_name\n"); );
}

void Vt_covergroup_negative_ranges_t__03a__03acg::_ctor_var_reset(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::_ctor_var_reset\n"); );
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
    __PVT____Vcov_cp_neg_negative = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 12532851831779417002ull);
    __PVT____Vcov_cp_neg_zero = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 12395204860377981043ull);
    __PVT____Vcov_cp_neg_positive = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 1035948034477804921ull);
    __PVT____Vcov_cp_neg_mixed = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 14715333671981847883ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_negative_ranges_t__03a__03acg>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_negative_ranges_t__03a__03acg::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_negative_ranges_t__03a__03acg::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_negative_ranges_t__03a__03acg::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov_cp_neg_negative:" + VL_TO_STRING(__PVT____Vcov_cp_neg_negative);
    out += ", __Vcov_cp_neg_zero:" + VL_TO_STRING(__PVT____Vcov_cp_neg_zero);
    out += ", __Vcov_cp_neg_positive:" + VL_TO_STRING(__PVT____Vcov_cp_neg_positive);
    out += ", __Vcov_cp_neg_mixed:" + VL_TO_STRING(__PVT____Vcov_cp_neg_mixed);
    return (out);
}
