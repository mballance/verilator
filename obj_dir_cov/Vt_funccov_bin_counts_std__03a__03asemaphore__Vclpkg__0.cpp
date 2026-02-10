// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_funccov_bin_counts.h for the primary calling header

#include "Vt_funccov_bin_counts__pch.h"

Vt_funccov_bin_counts_std__03a__03asemaphore::Vt_funccov_bin_counts_std__03a__03asemaphore(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
    this->__PVT__m_keyCount = keyCount;
    ++(vlSymsp->__Vcoverage[23]);
}

void Vt_funccov_bin_counts_std__03a__03asemaphore::__VnoInFunc_put(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::__VnoInFunc_put\n"); );
    // Body
    this->__PVT__m_keyCount = (this->__PVT__m_keyCount 
                               + keyCount);
    ++(vlSymsp->__Vcoverage[24]);
}

void Vt_funccov_bin_counts_std__03a__03asemaphore::__VnoInFunc_get(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::__VnoInFunc_get\n"); );
    // Body
    ++(vlSymsp->__Vcoverage[25]);
}

void Vt_funccov_bin_counts_std__03a__03asemaphore::__VnoInFunc_try_get(Vt_funccov_bin_counts__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount, IData/*31:0*/ &try_get__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::__VnoInFunc_try_get\n"); );
    // Body
    {
        try_get__Vfuncrtn = 0;
        if (VL_GTES_III(32, this->__PVT__m_keyCount, keyCount)) {
            this->__PVT__m_keyCount = (this->__PVT__m_keyCount 
                                       - keyCount);
            try_get__Vfuncrtn = 1U;
            goto __Vlabel0;
        } else {
            ++(vlSymsp->__Vcoverage[27]);
        }
        try_get__Vfuncrtn = 0U;
        __Vlabel0: ;
    }
    ++(vlSymsp->__Vcoverage[28]);
}

void Vt_funccov_bin_counts_std__03a__03asemaphore::_ctor_var_reset(Vt_funccov_bin_counts__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::_ctor_var_reset\n"); );
    // Body
    (void)vlSymsp;  // Prevent unused variable warning
    __PVT__m_keyCount = 0;
}

std::string VL_TO_STRING(const VlClassRef<Vt_funccov_bin_counts_std__03a__03asemaphore>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_funccov_bin_counts_std__03a__03asemaphore::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_funccov_bin_counts_std__03a__03asemaphore::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vt_funccov_bin_counts_std__03a__03asemaphore::to_string_middle\n"); );
    // Body
    std::string out;
    out += "m_keyCount:" + VL_TO_STRING(__PVT__m_keyCount);
    return (out);
}
