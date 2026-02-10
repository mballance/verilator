// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_bin_counts.h for the primary calling header

#include "Vt_funccov_bin_counts__pch.h"

void Vt_funccov_bin_counts_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_funccov_bin_counts_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[19]);
    get_coverage__Vfuncrtn = 0.0;
}

Vt_funccov_bin_counts_t__03a__03acg::Vt_funccov_bin_counts_t__03a__03acg(Vt_funccov_bin_counts__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[15]);
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.zero", &(this->__PVT____Vcov__zero), "type", "funccov", "filename", "test_regress/t/t_funccov_bin_counts.v", "lineno", "15", "column", "18", "bin", "zero");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.low", &(this->__PVT____Vcov__low), "type", "funccov", "filename", "test_regress/t/t_funccov_bin_counts.v", "lineno", "16", "column", "18", "bin", "low");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.mid", &(this->__PVT____Vcov__mid), "type", "funccov", "filename", "test_regress/t/t_funccov_bin_counts.v", "lineno", "17", "column", "18", "bin", "mid");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.high", &(this->__PVT____Vcov__high), "type", "funccov", "filename", "test_regress/t/t_funccov_bin_counts.v", "lineno", "18", "column", "18", "bin", "high");
}

void Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_sample(Vt_funccov_bin_counts__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_sample\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[16]);
    if ((0U == (IData)(vlSymsp->TOP__t.__PVT__data))) {
        this->__PVT____Vcov__zero = ((IData)(1U) + this->__PVT____Vcov__zero);
    }
    if (((1U <= (IData)(vlSymsp->TOP__t.__PVT__data)) 
         & (3U >= (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__low = ((IData)(1U) + this->__PVT____Vcov__low);
    }
    if (((4U <= (IData)(vlSymsp->TOP__t.__PVT__data)) 
         & (7U >= (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__mid = ((IData)(1U) + this->__PVT____Vcov__mid);
    }
    if (((8U <= (IData)(vlSymsp->TOP__t.__PVT__data)) 
         & (0x0000000fU >= (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__high = ((IData)(1U) + this->__PVT____Vcov__high);
    }
}

void Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_start(Vt_funccov_bin_counts__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_start\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[17]);
}

void Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_stop(Vt_funccov_bin_counts__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_stop\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[18]);
}

void Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_get_inst_coverage(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[20]);
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov__zero)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__low)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__mid)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__high)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 4.0));
}

void Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
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
    ++(vlSymsp->__Vcoverage[21]);
}

void Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_set_inst_name(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::__VnoInFunc_set_inst_name\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[22]);
}

void Vt_funccov_bin_counts_t__03a__03acg::_ctor_var_reset(Vt_funccov_bin_counts__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::_ctor_var_reset\n"); );
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
    __PVT____Vcov__zero = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 3321109391809128131ull);
    __PVT____Vcov__low = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 15881574630601992ull);
    __PVT____Vcov__mid = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 5257366301156952087ull);
    __PVT____Vcov__high = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 12471405194036028186ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_funccov_bin_counts_t__03a__03acg>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_funccov_bin_counts_t__03a__03acg::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_funccov_bin_counts_t__03a__03acg::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_bin_counts_t__03a__03acg::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov__zero:" + VL_TO_STRING(__PVT____Vcov__zero);
    out += ", __Vcov__low:" + VL_TO_STRING(__PVT____Vcov__low);
    out += ", __Vcov__mid:" + VL_TO_STRING(__PVT____Vcov__mid);
    out += ", __Vcov__high:" + VL_TO_STRING(__PVT____Vcov__high);
    return (out);
}
