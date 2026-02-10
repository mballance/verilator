// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_empty.h for the primary calling header

#include "Vt_covergroup_empty__pch.h"

Vt_covergroup_empty_std__03a__03asemaphore::Vt_covergroup_empty_std__03a__03asemaphore(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    this->__PVT__m_keyCount = keyCount;
    ++(vlSymsp->__Vcoverage[31]);
}

void Vt_covergroup_empty_std__03a__03asemaphore::__VnoInFunc_put(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::__VnoInFunc_put\n"); );
    // Body
    this->__PVT__m_keyCount = (this->__PVT__m_keyCount 
                               + keyCount);
    ++(vlSymsp->__Vcoverage[32]);
}

VlCoroutine Vt_covergroup_empty_std__03a__03asemaphore::__VnoInFunc_get(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::__VnoInFunc_get\n"); );
    // Locals
    CData/*0:0*/ __Vtrigprevexpr_h3af57c99__0;
    __Vtrigprevexpr_h3af57c99__0 = 0;
    // Body
    VL_KEEP_THIS;
    while (VL_LTS_III(32, this->__PVT__m_keyCount, keyCount)) {
        if (VL_LTS_III(32, this->__PVT__m_keyCount, keyCount)) {
            CData/*0:0*/ __VdynTrigger_h48f9aa33__0;
            __VdynTrigger_h48f9aa33__0 = 0;
            __VdynTrigger_h48f9aa33__0 = 0U;
            while ((1U & (~ (IData)(__VdynTrigger_h48f9aa33__0)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@([true] (std::semaphore.m_keyCount >= std::semaphore.keyCount))", 
                                                             "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 
                                                             114);
                __Vtrigprevexpr_h3af57c99__0 = VL_GTES_III(32, this->__PVT__m_keyCount, keyCount);
                __VdynTrigger_h48f9aa33__0 = __Vtrigprevexpr_h3af57c99__0;
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h48f9aa33__0);
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@([true] (std::semaphore.m_keyCount >= std::semaphore.keyCount))", 
                                                         "/home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv", 
                                                         114);
        }
        ++(vlSymsp->__Vcoverage[33]);
    }
    this->__PVT__m_keyCount = (this->__PVT__m_keyCount 
                               - keyCount);
    ++(vlSymsp->__Vcoverage[34]);
    co_return;
}

void Vt_covergroup_empty_std__03a__03asemaphore::__VnoInFunc_try_get(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount, IData/*31:0*/ &try_get__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::__VnoInFunc_try_get\n"); );
    // Body
    {
        try_get__Vfuncrtn = 0;
        if (VL_GTES_III(32, this->__PVT__m_keyCount, keyCount)) {
            this->__PVT__m_keyCount = (this->__PVT__m_keyCount 
                                       - keyCount);
            try_get__Vfuncrtn = 1U;
            goto __Vlabel0;
        } else {
            ++(vlSymsp->__Vcoverage[36]);
        }
        try_get__Vfuncrtn = 0U;
        __Vlabel0: ;
    }
    ++(vlSymsp->__Vcoverage[37]);
}

void Vt_covergroup_empty_std__03a__03asemaphore::_ctor_var_reset(Vt_covergroup_empty__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    __PVT__m_keyCount = 0;
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_empty_std__03a__03asemaphore>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_empty_std__03a__03asemaphore::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_empty_std__03a__03asemaphore::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_covergroup_empty_std__03a__03asemaphore::to_string_middle\n"); );
    // Body
    std::string out;
    out += "m_keyCount:" + VL_TO_STRING(__PVT__m_keyCount);
    return (out);
}
