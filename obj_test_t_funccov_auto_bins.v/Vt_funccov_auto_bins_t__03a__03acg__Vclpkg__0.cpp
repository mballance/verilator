// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_auto_bins.h for the primary calling header

#include "Vt_funccov_auto_bins__pch.h"

void Vt_funccov_auto_bins_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_funccov_auto_bins_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    get_coverage__Vfuncrtn = 0.0;
}

Vt_funccov_auto_bins_t__03a__03acg::Vt_funccov_auto_bins_t__03a__03acg(Vt_funccov_auto_bins__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.auto[0]", &(this->__PVT____Vcov__auto_0_), "page", "v_funccov/cg", "filename", "test_regress/t/t_funccov_auto_bins.v", "lineno", "12", "column", "18", "bin", "auto[0]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.auto[1]", &(this->__PVT____Vcov__auto_1_), "page", "v_funccov/cg", "filename", "test_regress/t/t_funccov_auto_bins.v", "lineno", "12", "column", "18", "bin", "auto[1]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.auto[2]", &(this->__PVT____Vcov__auto_2_), "page", "v_funccov/cg", "filename", "test_regress/t/t_funccov_auto_bins.v", "lineno", "12", "column", "18", "bin", "auto[2]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.data.auto[3]", &(this->__PVT____Vcov__auto_3_), "page", "v_funccov/cg", "filename", "test_regress/t/t_funccov_auto_bins.v", "lineno", "12", "column", "18", "bin", "auto[3]");
}

void Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_sample(Vt_funccov_auto_bins__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_sample\n"); );
    // Body
    if ((1U >= (IData)(vlSymsp->TOP__t.__PVT__data))) {
        this->__PVT____Vcov__auto_0_ = ((IData)(1U) 
                                        + this->__PVT____Vcov__auto_0_);
    }
    if (((2U <= (IData)(vlSymsp->TOP__t.__PVT__data)) 
         & (3U >= (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__auto_1_ = ((IData)(1U) 
                                        + this->__PVT____Vcov__auto_1_);
    }
    if (((4U <= (IData)(vlSymsp->TOP__t.__PVT__data)) 
         & (5U >= (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__auto_2_ = ((IData)(1U) 
                                        + this->__PVT____Vcov__auto_2_);
    }
    if ((6U <= (IData)(vlSymsp->TOP__t.__PVT__data))) {
        this->__PVT____Vcov__auto_3_ = ((IData)(1U) 
                                        + this->__PVT____Vcov__auto_3_);
    }
}

void Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_get_inst_coverage(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov__auto_0_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__auto_1_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__auto_2_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__auto_3_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 4.0));
}

void Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
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

void Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_set_inst_name(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::__VnoInFunc_set_inst_name\n"); );
}

void Vt_funccov_auto_bins_t__03a__03acg::_ctor_var_reset(Vt_funccov_auto_bins__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::_ctor_var_reset\n"); );
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
    __PVT____Vcov__auto_0_ = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 1261457355951012272ull);
    __PVT____Vcov__auto_1_ = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 10245563948773088461ull);
    __PVT____Vcov__auto_2_ = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 48535520359704494ull);
    __PVT____Vcov__auto_3_ = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 16961703562653432189ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_funccov_auto_bins_t__03a__03acg>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_funccov_auto_bins_t__03a__03acg::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_funccov_auto_bins_t__03a__03acg::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_funccov_auto_bins_t__03a__03acg::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov__auto_0_:" + VL_TO_STRING(__PVT____Vcov__auto_0_);
    out += ", __Vcov__auto_1_:" + VL_TO_STRING(__PVT____Vcov__auto_1_);
    out += ", __Vcov__auto_2_:" + VL_TO_STRING(__PVT____Vcov__auto_2_);
    out += ", __Vcov__auto_3_:" + VL_TO_STRING(__PVT____Vcov__auto_3_);
    return (out);
}
