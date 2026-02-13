// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest_partial_coverage.h for the primary calling header

#include "Vtest_partial_coverage__pch.h"

void Vtest_partial_coverage_cg::__VnoInFunc_sample(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg::__VnoInFunc_sample\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[1]);
    if ((0x0000007fU >= vlSymsp->TOP__t.__PVT__addr)) {
        this->__PVT____Vcov_cp_addr_low = ((IData)(1U) 
                                           + this->__PVT____Vcov_cp_addr_low);
    }
    if (((0x00000080U <= vlSymsp->TOP__t.__PVT__addr) 
         & (0x000000ffU >= vlSymsp->TOP__t.__PVT__addr))) {
        this->__PVT____Vcov_cp_addr_high = ((IData)(1U) 
                                            + this->__PVT____Vcov_cp_addr_high);
    }
}

void Vtest_partial_coverage_cg::__VnoInFunc_start(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg::__VnoInFunc_start\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[2]);
}

void Vtest_partial_coverage_cg::__VnoInFunc_stop(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg::__VnoInFunc_stop\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[3]);
}

void Vtest_partial_coverage_cg::__VnoInFunc_get_coverage(Vtest_partial_coverage__Syms* __restrict vlSymsp, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg::__VnoInFunc_get_coverage\n"); );
    // Locals
    double __Vfunc_get_inst_coverage__0__Vfuncout;
    __Vfunc_get_inst_coverage__0__Vfuncout = 0;
    // Body
    get_coverage__Vfuncrtn = 0;
    ++(vlSymsp->__Vcoverage[4]);
    this->__VnoInFunc_get_inst_coverage(vlSymsp, __Vfunc_get_inst_coverage__0__Vfuncout);
    get_coverage__Vfuncrtn = __Vfunc_get_inst_coverage__0__Vfuncout;
}

void Vtest_partial_coverage_cg::__VnoInFunc_get_inst_coverage(Vtest_partial_coverage__Syms* __restrict vlSymsp, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[5]);
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov_cp_addr_low)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_addr_high)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 2.0));
}

void Vtest_partial_coverage_cg::__VnoInFunc_set_inst_name(Vtest_partial_coverage__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtest_partial_coverage_cg::__VnoInFunc_set_inst_name\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[6]);
}
