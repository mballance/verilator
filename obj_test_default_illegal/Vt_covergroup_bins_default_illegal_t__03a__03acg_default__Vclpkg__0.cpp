// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#include "Vt_covergroup_bins_default_illegal__pch.h"

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_bins_default_illegal_t__03a__03acg_default__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[26]);
    get_coverage__Vfuncrtn = 0.0;
}

Vt_covergroup_bins_default_illegal_t__03a__03acg_default::Vt_covergroup_bins_default_illegal_t__03a__03acg_default(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[22]);
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg_default.data.special", &(this->__PVT____Vcov__special), "page", "v_funccov/cg_default", "filename", "test_regress/t/t_covergroup_bins_default_illegal.v", "lineno", "17", "column", "15", "bin", "special");
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), "cg_default.data.others", &(this->__PVT____Vcov__others), "page", "v_funccov/cg_default", "filename", "test_regress/t/t_covergroup_bins_default_illegal.v", "lineno", "18", "column", "15", "bin", "others");
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_sample(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_sample\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[23]);
    if ((((0U == (IData)(vlSymsp->TOP__t.__PVT__data)) 
          | (5U == (IData)(vlSymsp->TOP__t.__PVT__data))) 
         | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__data)))) {
        this->__PVT____Vcov__special = ((IData)(1U) 
                                        + this->__PVT____Vcov__special);
    }
    if ((1U & (~ (((0U == (IData)(vlSymsp->TOP__t.__PVT__data)) 
                   | (5U == (IData)(vlSymsp->TOP__t.__PVT__data))) 
                  | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__data)))))) {
        this->__PVT____Vcov__others = ((IData)(1U) 
                                       + this->__PVT____Vcov__others);
    }
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_start(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_start\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[24]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_stop(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_stop\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[25]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_get_inst_coverage(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[27]);
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov__special)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov__others)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 2.0));
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
    // Locals
    double __Vfunc_get_inst_coverage__0__Vfuncout;
    __Vfunc_get_inst_coverage__0__Vfuncout = 0;
    // Body
    std::string covered_bins;
    covered_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_default__Vclpkg.__PVT____Vint);
    std::string total_bins;
    total_bins = VL_CVT_PACK_STR_NI(vlSymsp->TOP__t__03a__03acg_default__Vclpkg.__PVT____Vint);
    this->__VnoInFunc_get_inst_coverage(vlSymsp, covered_bins, total_bins, __Vfunc_get_inst_coverage__0__Vfuncout);
    get_inst_coverage__Vtcwrap_1_2__Vfuncrtn = __Vfunc_get_inst_coverage__0__Vfuncout;
    ++(vlSymsp->__Vcoverage[28]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_set_inst_name(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::__VnoInFunc_set_inst_name\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[29]);
}

void Vt_covergroup_bins_default_illegal_t__03a__03acg_default::_ctor_var_reset(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::_ctor_var_reset\n"); );
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
    __PVT____Vcov__special = VL_SCOPED_RAND_RESET_I(32, 8763269169098162105ULL, 8646252829999757695ull);
    __PVT____Vcov__others = VL_SCOPED_RAND_RESET_I(32, 8763269169098162105ULL, 15781130357016166739ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_bins_default_illegal_t__03a__03acg_default>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_bins_default_illegal_t__03a__03acg_default::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_bins_default_illegal_t__03a__03acg_default::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_bins_default_illegal_t__03a__03acg_default::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov__special:" + VL_TO_STRING(__PVT____Vcov__special);
    out += ", __Vcov__others:" + VL_TO_STRING(__PVT____Vcov__others);
    return (out);
}
