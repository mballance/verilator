// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#include "Vt_covergroup_bins_default_illegal__pch.h"

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[34]);
    get_coverage__Vfuncrtn = 0.0;
}

Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::Vt_covergroup_bins_default_illegal_t__03a__03acg_valid(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[30]);
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg_valid.data.valid", &(this->__PVT____Vcov__valid), "page", "v_funccov/cg_valid", "filename", "test_regress/t/t_covergroup_bins_default_illegal.v", "lineno", "25", "column", "15", "bin", "valid");
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_sample(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_sample\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[31]);
    if ((0x0000000aU >= (IData)(vlSymsp->TOP__t.__PVT__data))) {
        this->__PVT____Vcov__valid = ((IData)(1U) + this->__PVT____Vcov__valid);
    }
    if (VL_UNLIKELY((((0x0000000bU <= (IData)(vlSymsp->TOP__t.__PVT__data)) 
                      & (0x0000000fU >= (IData)(vlSymsp->TOP__t.__PVT__data)))))) {
        this->__PVT____Vcov__reserved = ((IData)(1U) 
                                         + this->__PVT____Vcov__reserved);
        VL_WRITEF_NX("[%0t] %%Error: t_covergroup_bins_default_illegal.v:26: Assertion failed in %Nt.cg_valid.sample: Illegal bin 'reserved' hit in coverpoint ''\n",0,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name());
        VL_STOP_MT("test_regress/t/t_covergroup_bins_default_illegal.v", 26, "", false);
    }
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_start(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_start\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[32]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_stop(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_stop\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[33]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_get_inst_coverage(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[35]);
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov__valid)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 1.0));
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
    // Locals
    double __Vfunc_get_inst_coverage__0__Vfuncout;
    __Vfunc_get_inst_coverage__0__Vfuncout = 0;
    // Body
    std::string covered_bins;
    covered_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_valid__Vclpkg.__PVT____Vint);
    std::string total_bins;
    total_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_valid__Vclpkg.__PVT____Vint);
    this->__VnoInFunc_get_inst_coverage(vlSymsp, covered_bins, total_bins, __Vfunc_get_inst_coverage__0__Vfuncout);
    get_inst_coverage__Vtcwrap_1_2__Vfuncrtn = __Vfunc_get_inst_coverage__0__Vfuncout;
    ++(vlSymsp->__Vcoverage[36]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_set_inst_name(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::__VnoInFunc_set_inst_name\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[37]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::_ctor_var_reset(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::_ctor_var_reset\n"); );
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
    __PVT____Vcov__valid = VL_SCOPED_RAND_RESET_I(32, 15167414128857486432ULL, 17233793468288362711ull);
    __PVT____Vcov__reserved = VL_SCOPED_RAND_RESET_I(32, 15167414128857486432ULL, 12427360507935579776ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_bins_default_illegal_t__03a__03acg_valid>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_valid::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov__valid:" + VL_TO_STRING(__PVT____Vcov__valid);
    out += ", __Vcov__reserved:" + VL_TO_STRING(__PVT____Vcov__reserved);
    return (out);
}
