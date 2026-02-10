// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_autobins.h for the primary calling header

#include "Vt_covergroup_autobins__pch.h"

void Vt_covergroup_autobins_t__03a__03acg3__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_autobins__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_autobins_t__03a__03acg3__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    get_coverage__Vfuncrtn = 0.0;
}

Vt_covergroup_autobins_t__03a__03acg3::Vt_covergroup_autobins_t__03a__03acg3(Vt_covergroup_autobins__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[0]", &(this->__PVT____Vcov_cp_data3___auto_0_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[0]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[1]", &(this->__PVT____Vcov_cp_data3___auto_1_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[1]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[2]", &(this->__PVT____Vcov_cp_data3___auto_2_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[2]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[3]", &(this->__PVT____Vcov_cp_data3___auto_3_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[3]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[4]", &(this->__PVT____Vcov_cp_data3___auto_4_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[4]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[5]", &(this->__PVT____Vcov_cp_data3___auto_5_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[5]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[6]", &(this->__PVT____Vcov_cp_data3___auto_6_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[6]");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg3.cp_data3.__auto[7]", &(this->__PVT____Vcov_cp_data3___auto_7_), "page", "v_funccov/cg3", "filename", "test_regress/t/t_covergroup_autobins.v", "lineno", "34", "column", "17", "bin", "__auto[7]");
}

void Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_sample(Vt_covergroup_autobins__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_sample\n"); );
    // Body
    if ((7U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3_reserved = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cp_data3_reserved);
    }
    if ((0U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_0_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_0_);
    }
    if ((1U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_1_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_1_);
    }
    if ((2U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_2_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_2_);
    }
    if ((3U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_3_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_3_);
    }
    if ((4U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_4_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_4_);
    }
    if ((5U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_5_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_5_);
    }
    if ((6U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_6_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_6_);
    }
    if ((7U == (IData)(vlSymsp->TOP__t.__PVT__data3))) {
        this->__PVT____Vcov_cp_data3___auto_7_ = ((IData)(1U) 
                                                  + this->__PVT____Vcov_cp_data3___auto_7_);
    }
}

void Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_get_inst_coverage(Vt_covergroup_autobins__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_0_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_1_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_2_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_3_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_4_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_5_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_6_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_data3___auto_7_)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 8.0));
}

void Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_autobins__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
    // Locals
    double __Vfunc_get_inst_coverage__0__Vfuncout;
    __Vfunc_get_inst_coverage__0__Vfuncout = 0;
    // Body
    std::string covered_bins;
    covered_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg3__Vclpkg.__PVT____Vint);
    std::string total_bins;
    total_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg3__Vclpkg.__PVT____Vint);
    this->__VnoInFunc_get_inst_coverage(vlSymsp, covered_bins, total_bins, __Vfunc_get_inst_coverage__0__Vfuncout);
    get_inst_coverage__Vtcwrap_1_2__Vfuncrtn = __Vfunc_get_inst_coverage__0__Vfuncout;
}

void Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_set_inst_name(Vt_covergroup_autobins__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::__VnoInFunc_set_inst_name\n"); );
}

void Vt_covergroup_autobins_t__03a__03acg3::_ctor_var_reset(Vt_covergroup_autobins__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::_ctor_var_reset\n"); );
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
    __PVT____Vcov_cp_data3_reserved = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 10142351206491292917ull);
    __PVT____Vcov_cp_data3___auto_0_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 5134874585609275844ull);
    __PVT____Vcov_cp_data3___auto_1_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 1601514131553691173ull);
    __PVT____Vcov_cp_data3___auto_2_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 13871032851404298889ull);
    __PVT____Vcov_cp_data3___auto_3_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 16002832924935352360ull);
    __PVT____Vcov_cp_data3___auto_4_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 1155204285815924016ull);
    __PVT____Vcov_cp_data3___auto_5_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 4306416238724532990ull);
    __PVT____Vcov_cp_data3___auto_6_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 18286470442067642655ull);
    __PVT____Vcov_cp_data3___auto_7_ = VL_SCOPED_RAND_RESET_I(32, 13820104232573974452ULL, 8882961891117881800ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_autobins_t__03a__03acg3>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_autobins_t__03a__03acg3::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_autobins_t__03a__03acg3::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_autobins_t__03a__03acg3::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov_cp_data3_reserved:" + VL_TO_STRING(__PVT____Vcov_cp_data3_reserved);
    out += ", __Vcov_cp_data3___auto_0_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_0_);
    out += ", __Vcov_cp_data3___auto_1_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_1_);
    out += ", __Vcov_cp_data3___auto_2_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_2_);
    out += ", __Vcov_cp_data3___auto_3_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_3_);
    out += ", __Vcov_cp_data3___auto_4_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_4_);
    out += ", __Vcov_cp_data3___auto_5_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_5_);
    out += ", __Vcov_cp_data3___auto_6_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_6_);
    out += ", __Vcov_cp_data3___auto_7_:" + VL_TO_STRING(__PVT____Vcov_cp_data3___auto_7_);
    return (out);
}
