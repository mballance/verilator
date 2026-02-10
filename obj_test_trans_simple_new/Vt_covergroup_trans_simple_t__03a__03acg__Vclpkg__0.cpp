// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_trans_simple.h for the primary calling header

#include "Vt_covergroup_trans_simple__pch.h"

void Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_trans_simple_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[23]);
    get_coverage__Vfuncrtn = 0.0;
}

Vt_covergroup_trans_simple_t__03a__03acg::Vt_covergroup_trans_simple_t__03a__03acg(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[19]);
    this->__PVT____Vprev_cp_state = 0U;
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.cp_state.trans1", &(this->__PVT____Vcov_cp_state_trans1), "page", "v_funccov/cg", "filename", "test_regress/t/t_covergroup_trans_simple.v", "lineno", "15", "column", "15", "bin", "trans1");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.cp_state.trans2", &(this->__PVT____Vcov_cp_state_trans2), "page", "v_funccov/cg", "filename", "test_regress/t/t_covergroup_trans_simple.v", "lineno", "16", "column", "15", "bin", "trans2");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg.cp_state.trans3", &(this->__PVT____Vcov_cp_state_trans3), "page", "v_funccov/cg", "filename", "test_regress/t/t_covergroup_trans_simple.v", "lineno", "17", "column", "15", "bin", "trans3");
}

void Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_sample(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_sample\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[20]);
    if (((0U == (IData)(this->__PVT____Vprev_cp_state)) 
         & (1U == (IData)(vlSymsp->TOP__t.__PVT__state)))) {
        this->__PVT____Vcov_cp_state_trans1 = ((IData)(1U) 
                                               + this->__PVT____Vcov_cp_state_trans1);
    }
    if (((1U == (IData)(this->__PVT____Vprev_cp_state)) 
         & (2U == (IData)(vlSymsp->TOP__t.__PVT__state)))) {
        this->__PVT____Vcov_cp_state_trans2 = ((IData)(1U) 
                                               + this->__PVT____Vcov_cp_state_trans2);
    }
    if (((2U == (IData)(this->__PVT____Vprev_cp_state)) 
         & (3U == (IData)(vlSymsp->TOP__t.__PVT__state)))) {
        this->__PVT____Vcov_cp_state_trans3 = ((IData)(1U) 
                                               + this->__PVT____Vcov_cp_state_trans3);
    }
    this->__PVT____Vprev_cp_state = vlSymsp->TOP__t.__PVT__state;
}

void Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_start(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_start\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[21]);
}

void Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_stop(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_stop\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[22]);
}

void Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_get_inst_coverage(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[24]);
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov_cp_state_trans1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_state_trans2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_state_trans3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 3.0));
}

void Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
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
    ++(vlSymsp->__Vcoverage[25]);
}

void Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_set_inst_name(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::__VnoInFunc_set_inst_name\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[26]);
}

void Vt_covergroup_trans_simple_t__03a__03acg::_ctor_var_reset(Vt_covergroup_trans_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::_ctor_var_reset\n"); );
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
    __PVT____Vcov_cp_state_trans1 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 7223285111105156959ull);
    __PVT____Vprev_cp_state = VL_SCOPED_RAND_RESET_I(3, 16031476294656798452ULL, 12670905524288345805ull);
    __PVT____Vcov_cp_state_trans2 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 7564968094973893509ull);
    __PVT____Vcov_cp_state_trans3 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 8623368665219064398ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_trans_simple_t__03a__03acg>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_trans_simple_t__03a__03acg::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_trans_simple_t__03a__03acg::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_trans_simple_t__03a__03acg::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov_cp_state_trans1:" + VL_TO_STRING(__PVT____Vcov_cp_state_trans1);
    out += ", __Vprev_cp_state:" + VL_TO_STRING(__PVT____Vprev_cp_state);
    out += ", __Vcov_cp_state_trans2:" + VL_TO_STRING(__PVT____Vcov_cp_state_trans2);
    out += ", __Vcov_cp_state_trans3:" + VL_TO_STRING(__PVT____Vcov_cp_state_trans3);
    return (out);
}
