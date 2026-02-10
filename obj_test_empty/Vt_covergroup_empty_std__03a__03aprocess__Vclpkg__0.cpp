// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_empty.h for the primary calling header

#include "Vt_covergroup_empty__pch.h"

void Vt_covergroup_empty_std__03a__03aprocess__Vclpkg::__VnoInFunc_self(VlProcessRef vlProcess, Vt_covergroup_empty__Syms* __restrict vlSymsp, VlClassRef<Vt_covergroup_empty_std__03a__03aprocess> &self__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_empty_std__03a__03aprocess__Vclpkg::__VnoInFunc_self\n"); );
    // Body
    VlClassRef<Vt_covergroup_empty_std__03a__03aprocess> p;
    p = VL_NEW(Vt_covergroup_empty_std__03a__03aprocess, vlSymsp);

// $c statement at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:145:7
    VL_NULL_CHECK(p, "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 145)->__PVT__m_process = vlProcess;
    self__Vfuncrtn = p;
    ++(vlSymsp->__Vcoverage[38]);
}

void Vt_covergroup_empty_std__03a__03aprocess__Vclpkg::__VnoInFunc_killQueue(Vt_covergroup_empty__Syms* __restrict vlSymsp, VlQueue<VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>> &processQueue) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_empty_std__03a__03aprocess__Vclpkg::__VnoInFunc_killQueue\n"); );
    // Body
    while (VL_LTS_III(32, 0U, processQueue.size())) {
        VL_NULL_CHECK(processQueue.pop_back(), "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 185)->__VnoInFunc_kill(vlSymsp);
        ++(vlSymsp->__Vcoverage[47]);
    }
    ++(vlSymsp->__Vcoverage[48]);
}

void Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_set_status(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ s) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_set_status\n"); );
    // Body

// $c statement at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:152:7
    this->__PVT__m_process->state(s);
    ++(vlSymsp->__Vcoverage[39]);
}

void Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_status(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ &status__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_status\n"); );
    // Body
    status__Vfuncrtn = 0;
    status__Vfuncrtn = 
// $cpure expression at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:158:21
this->__PVT__m_process->state()
    ;
    ++(vlSymsp->__Vcoverage[40]);
}

void Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_kill(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_kill\n"); );
    // Body
    this->__VnoInFunc_set_status(vlSymsp, 4U);
    ++(vlSymsp->__Vcoverage[41]);
}

void Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_suspend(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_suspend\n"); );
    // Body
    VL_WRITEF_NX("[%0t] %%Error: verilated_std.sv:169: Assertion failed in %Nstd.process.suspend: std::process::suspend() not supported\n",0,
                 64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name());
    VL_STOP_MT("/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 169, "");
}

void Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_resume(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_resume\n"); );
    // Body
    this->__VnoInFunc_set_status(vlSymsp, 1U);
    ++(vlSymsp->__Vcoverage[42]);
}

VlCoroutine Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_await(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_await\n"); );
    // Locals
    CData/*0:0*/ __Vtrigprevexpr_hbd84446c__0;
    __Vtrigprevexpr_hbd84446c__0 = 0;
    IData/*31:0*/ __Vfunc_status__2__Vfuncout;
    __Vfunc_status__2__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_status__3__Vfuncout;
    __Vfunc_status__3__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_status__4__Vfuncout;
    __Vfunc_status__4__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_status__5__Vfuncout;
    __Vfunc_status__5__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_status__6__Vfuncout;
    __Vfunc_status__6__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_status__7__Vfuncout;
    __Vfunc_status__7__Vfuncout = 0;
    // Body
    VL_KEEP_THIS;
    if ((1U & (~ ((0U == ([&]() {
                                this->__VnoInFunc_status(vlSymsp, __Vfunc_status__2__Vfuncout);
                            }(), __Vfunc_status__2__Vfuncout)) 
                  || (4U == ([&]() {
                                this->__VnoInFunc_status(vlSymsp, __Vfunc_status__3__Vfuncout);
                            }(), __Vfunc_status__3__Vfuncout)))))) {
        CData/*0:0*/ __VdynTrigger_hc76a74e6__0;
        __VdynTrigger_hc76a74e6__0 = 0;
        __VdynTrigger_hc76a74e6__0 = 0U;
        while ((1U & (~ (IData)(__VdynTrigger_hc76a74e6__0)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@([true] ((32'h0 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__2__Vfuncout); , std::process.__Vfunc_status__2__Vfuncout); ) || (32'h4 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__3__Vfuncout); , std::process.__Vfunc_status__3__Vfuncout); )))", 
                                                         "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 
                                                         178);
            __Vtrigprevexpr_hbd84446c__0 = ((0U == 
                                             ([&]() {
                            this->__VnoInFunc_status(vlSymsp, __Vfunc_status__2__Vfuncout);
                        }(), __Vfunc_status__2__Vfuncout)) 
                                            || (4U 
                                                == 
                                                ([&]() {
                            this->__VnoInFunc_status(vlSymsp, __Vfunc_status__3__Vfuncout);
                        }(), __Vfunc_status__3__Vfuncout)));
            __VdynTrigger_hc76a74e6__0 = __Vtrigprevexpr_hbd84446c__0;
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hc76a74e6__0);
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@([true] ((32'h0 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__2__Vfuncout); , std::process.__Vfunc_status__2__Vfuncout); ) || (32'h4 == $_EXPRSTMT( // Function: status __VnoInFunc_status(std::process.__Vfunc_status__3__Vfuncout); , std::process.__Vfunc_status__3__Vfuncout); )))", 
                                                     "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 
                                                     178);
    }
    if ((4U == ([&]() {
                    this->__VnoInFunc_status(vlSymsp, __Vfunc_status__4__Vfuncout);
                }(), __Vfunc_status__4__Vfuncout))) {
        ++(vlSymsp->__Vcoverage[43]);
    }
    if ((0U == ([&]() {
                    this->__VnoInFunc_status(vlSymsp, __Vfunc_status__5__Vfuncout);
                }(), __Vfunc_status__5__Vfuncout))) {
        ++(vlSymsp->__Vcoverage[44]);
    }
    if (((0U != ([&]() {
                        this->__VnoInFunc_status(vlSymsp, __Vfunc_status__6__Vfuncout);
                    }(), __Vfunc_status__6__Vfuncout)) 
         && (4U != ([&]() {
                        this->__VnoInFunc_status(vlSymsp, __Vfunc_status__7__Vfuncout);
                    }(), __Vfunc_status__7__Vfuncout)))) {
        ++(vlSymsp->__Vcoverage[45]);
    }
    ++(vlSymsp->__Vcoverage[46]);
    co_return;
}

void Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_get_randstate(Vt_covergroup_empty__Syms* __restrict vlSymsp, std::string &get_randstate__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_get_randstate\n"); );
    // Body
    std::string s;
    s = VL_CVT_PACK_STR_NI(
// $c expression at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:231:26
0
    );

// $c statement at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:233:7
    s = this->__PVT__m_process->randstate();
    get_randstate__Vfuncrtn = s;
    ++(vlSymsp->__Vcoverage[49]);
}

void Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_set_randstate(Vt_covergroup_empty__Syms* __restrict vlSymsp, std::string s) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::__VnoInFunc_set_randstate\n"); );
    // Body

// $c statement at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:238:7
    this->__PVT__m_process->randstate(s);
    ++(vlSymsp->__Vcoverage[50]);
}

Vt_covergroup_empty_std__03a__03aprocess::Vt_covergroup_empty_std__03a__03aprocess(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    ++(vlSymsp->__Vcoverage[51]);
}

void Vt_covergroup_empty_std__03a__03aprocess::_ctor_var_reset(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_empty_std__03a__03aprocess::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_empty_std__03a__03aprocess::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03aprocess::to_string_middle\n"); );
    // Body
    std::string out;
    out += "m_process:" + VL_TO_STRING(__PVT__m_process);
    return (out);
}
