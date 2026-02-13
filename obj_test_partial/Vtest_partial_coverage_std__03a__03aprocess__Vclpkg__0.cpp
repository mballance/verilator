// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtest_partial_coverage.h for the primary calling header

#include "Vtest_partial_coverage__pch.h"

void Vtest_partial_coverage_std__03a__03aprocess__Vclpkg::__VnoInFunc_self(VlProcessRef vlProcess, Vtest_partial_coverage__Syms* __restrict vlSymsp, VlClassRef<Vtest_partial_coverage_std__03a__03aprocess> &self__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vtest_partial_coverage_std__03a__03aprocess__Vclpkg::__VnoInFunc_self\n"); );
    // Body
    VlClassRef<Vtest_partial_coverage_std__03a__03aprocess> p;
    p = VL_NEW(Vtest_partial_coverage_std__03a__03aprocess, vlSymsp);
    self__Vfuncrtn = p;
    ++(vlSymsp->__Vcoverage[15]);
}

void Vtest_partial_coverage_std__03a__03aprocess__Vclpkg::__VnoInFunc_killQueue(Vtest_partial_coverage__Syms* __restrict vlSymsp, VlQueue<VlClassRef<Vtest_partial_coverage_std__03a__03aprocess>> &processQueue) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vtest_partial_coverage_std__03a__03aprocess__Vclpkg::__VnoInFunc_killQueue\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[21]);
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_set_status(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ s) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_set_status\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[16]);
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_status(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ &status__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_status\n"); );
    // Body
    status__Vfuncrtn = 1U;
    ++(vlSymsp->__Vcoverage[17]);
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_kill(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_kill\n"); );
    // Body
    this->__VnoInFunc_set_status(vlSymsp, 4U);
    ++(vlSymsp->__Vcoverage[18]);
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_suspend(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_suspend\n"); );
    // Body
    VL_WRITEF_NX("[%0t] %%Error: verilated_std.sv:169: Assertion failed in %Nstd.process.suspend: std::process::suspend() not supported\n",0,
                 64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name());
    VL_STOP_MT("/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 169, "");
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_resume(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_resume\n"); );
    // Body
    this->__VnoInFunc_set_status(vlSymsp, 1U);
    ++(vlSymsp->__Vcoverage[19]);
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_await(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_await\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[20]);
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_get_randstate(Vtest_partial_coverage__Syms* __restrict vlSymsp, std::string &get_randstate__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_get_randstate\n"); );
    // Body
    std::string s;
    s = VL_CVT_PACK_STR_NI(
// $c expression at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:231:26
0
    );

// $c statement at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:233:7
    s = this->__PVT__m_process->randstate();
    get_randstate__Vfuncrtn = s;
    ++(vlSymsp->__Vcoverage[22]);
}

void Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_set_randstate(Vtest_partial_coverage__Syms* __restrict vlSymsp, std::string s) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::__VnoInFunc_set_randstate\n"); );
    // Body

// $c statement at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:238:7
    this->__PVT__m_process->randstate(s);
    ++(vlSymsp->__Vcoverage[23]);
}

Vtest_partial_coverage_std__03a__03aprocess::Vtest_partial_coverage_std__03a__03aprocess(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[24]);
}

void Vtest_partial_coverage_std__03a__03aprocess::_ctor_var_reset(Vtest_partial_coverage__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
}

std::string VL_TO_STRING(const VlClassRef<Vtest_partial_coverage_std__03a__03aprocess>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vtest_partial_coverage_std__03a__03aprocess::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vtest_partial_coverage_std__03a__03aprocess::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtest_partial_coverage_std__03a__03aprocess::to_string_middle\n"); );
    // Body
    std::string out;
    out += "m_process:" + VL_TO_STRING(__PVT__m_process);
    return (out);
}
