// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_cross_small.h for the primary calling header

#include "Vt_covergroup_cross_small__pch.h"

void Vt_covergroup_cross_small_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+  Vt_covergroup_cross_small_t__03a__03acg__Vclpkg::__VnoInFunc_get_coverage\n"); );
    // Body
    get_coverage__Vfuncrtn = 0.0;
}

Vt_covergroup_cross_small_t__03a__03acg::Vt_covergroup_cross_small_t__03a__03acg(Vt_covergroup_cross_small__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::new\n"); );
    // Body
    _ctor_var_reset(vlSymsp);
}

void Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_sample(Vt_covergroup_cross_small__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_sample\n"); );
    // Body
    if (((((0U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
           | (1U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (2U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         | (3U == (IData)(vlSymsp->TOP__t.__PVT__a)))) {
        this->__PVT____Vcov_cp_a_a0 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_a_a0);
    }
    if (((((4U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
           | (5U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (6U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         | (7U == (IData)(vlSymsp->TOP__t.__PVT__a)))) {
        this->__PVT____Vcov_cp_a_a1 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_a_a1);
    }
    if (((((8U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
           | (9U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__a)))) {
        this->__PVT____Vcov_cp_a_a2 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_a_a2);
    }
    if (((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__a)) 
           | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__a)))) {
        this->__PVT____Vcov_cp_a_a3 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_a_a3);
    }
    if (((((0U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
           | (1U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
          | (2U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
         | (3U == (IData)(vlSymsp->TOP__t.__PVT__b)))) {
        this->__PVT____Vcov_cp_b_b0 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_b_b0);
    }
    if (((((4U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
           | (5U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
          | (6U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
         | (7U == (IData)(vlSymsp->TOP__t.__PVT__b)))) {
        this->__PVT____Vcov_cp_b_b1 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_b_b1);
    }
    if (((((8U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
           | (9U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
          | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
         | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__b)))) {
        this->__PVT____Vcov_cp_b_b2 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_b_b2);
    }
    if (((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__b)) 
           | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
          | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
         | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__b)))) {
        this->__PVT____Vcov_cp_b_b3 = ((IData)(1U) 
                                       + this->__PVT____Vcov_cp_b_b3);
    }
    if ((((((0U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (1U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (2U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (3U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (1U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (2U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (3U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a0_x__b0 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a0_x__b0);
    }
    if ((((((0U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (1U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (2U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (3U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((4U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (5U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (6U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (7U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a0_x__b1 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a0_x__b1);
    }
    if ((((((0U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (1U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (2U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (3U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((8U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (9U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a0_x__b2 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a0_x__b2);
    }
    if ((((((0U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (1U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (2U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (3U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a0_x__b3 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a0_x__b3);
    }
    if ((((((4U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (5U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (6U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (7U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (1U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (2U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (3U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a1_x__b0 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a1_x__b0);
    }
    if ((((((4U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (5U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (6U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (7U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((4U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (5U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (6U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (7U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a1_x__b1 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a1_x__b1);
    }
    if ((((((4U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (5U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (6U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (7U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((8U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (9U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a1_x__b2 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a1_x__b2);
    }
    if ((((((4U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (5U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (6U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (7U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a1_x__b3 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a1_x__b3);
    }
    if ((((((8U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (9U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (1U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (2U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (3U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a2_x__b0 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a2_x__b0);
    }
    if ((((((8U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (9U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((4U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (5U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (6U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (7U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a2_x__b1 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a2_x__b1);
    }
    if ((((((8U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (9U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((8U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (9U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a2_x__b2 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a2_x__b2);
    }
    if ((((((8U == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (9U == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a2_x__b3 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a2_x__b3);
    }
    if ((((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (1U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (2U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (3U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a3_x__b0 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a3_x__b0);
    }
    if ((((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((4U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (5U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (6U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (7U == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a3_x__b1 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a3_x__b1);
    }
    if ((((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((8U == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (9U == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000aU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000bU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a3_x__b2 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a3_x__b2);
    }
    if ((((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__a)) 
            | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
           | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
          | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__a))) 
         & ((((0x0000000cU == (IData)(vlSymsp->TOP__t.__PVT__b)) 
              | (0x0000000dU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
             | (0x0000000eU == (IData)(vlSymsp->TOP__t.__PVT__b))) 
            | (0x0000000fU == (IData)(vlSymsp->TOP__t.__PVT__b))))) {
        this->__PVT____Vcov_cross_ab_a3_x__b3 = ((IData)(1U) 
                                                 + this->__PVT____Vcov_cross_ab_a3_x__b3);
    }
}

void Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_get_inst_coverage(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_get_inst_coverage\n"); );
    // Body
    IData/*31:0*/ __Vcovered_count;
    __Vcovered_count = 0;
    __Vcovered_count = 0U;
    if ((1U <= this->__PVT____Vcov_cp_a_a0)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_a_a1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_a_a2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_a_a3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_b_b0)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_b_b1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_b_b2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cp_b_b3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a0_x__b0)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a0_x__b1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a0_x__b2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a0_x__b3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a1_x__b0)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a1_x__b1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a1_x__b2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a1_x__b3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a2_x__b0)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a2_x__b1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a2_x__b2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a2_x__b3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a3_x__b0)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a3_x__b1)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a3_x__b2)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    if ((1U <= this->__PVT____Vcov_cross_ab_a3_x__b3)) {
        __Vcovered_count = ((IData)(1U) + __Vcovered_count);
    }
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) 
                                            / 24.0));
}

void Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_get_inst_coverage__Vtcwrap_1_2\n"); );
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

void Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_set_inst_name(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, std::string name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::__VnoInFunc_set_inst_name\n"); );
}

void Vt_covergroup_cross_small_t__03a__03acg::_ctor_var_reset(Vt_covergroup_cross_small__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::_ctor_var_reset\n"); );
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
    __PVT____Vcov_cp_a_a0 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 11449888471151479111ull);
    __PVT____Vcov_cp_a_a1 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 516983067171629182ull);
    __PVT____Vcov_cp_a_a2 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 16171248967824264271ull);
    __PVT____Vcov_cp_a_a3 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 18150244538245881596ull);
    __PVT____Vcov_cp_b_b0 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 1919694920634352331ull);
    __PVT____Vcov_cp_b_b1 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 9433533590364187850ull);
    __PVT____Vcov_cp_b_b2 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 5991231992453499226ull);
    __PVT____Vcov_cp_b_b3 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 9570331020266947632ull);
    __PVT____Vcov_cross_ab_a0_x__b0 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 16285325730749301712ull);
    __PVT____Vcov_cross_ab_a0_x__b1 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 9043115842566938221ull);
    __PVT____Vcov_cross_ab_a0_x__b2 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 12748125118650454005ull);
    __PVT____Vcov_cross_ab_a0_x__b3 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 3798953855715833200ull);
    __PVT____Vcov_cross_ab_a1_x__b0 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 663469932635099873ull);
    __PVT____Vcov_cross_ab_a1_x__b1 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 15644093188615888058ull);
    __PVT____Vcov_cross_ab_a1_x__b2 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 16869995533863788497ull);
    __PVT____Vcov_cross_ab_a1_x__b3 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 15600779369063305099ull);
    __PVT____Vcov_cross_ab_a2_x__b0 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 14363165101609402598ull);
    __PVT____Vcov_cross_ab_a2_x__b1 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 12692162326295255041ull);
    __PVT____Vcov_cross_ab_a2_x__b2 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 17597587711956972795ull);
    __PVT____Vcov_cross_ab_a2_x__b3 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 4957769858622875692ull);
    __PVT____Vcov_cross_ab_a3_x__b0 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 13888968439087410437ull);
    __PVT____Vcov_cross_ab_a3_x__b1 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 4372338188196090139ull);
    __PVT____Vcov_cross_ab_a3_x__b2 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 10674652749363251322ull);
    __PVT____Vcov_cross_ab_a3_x__b3 = VL_SCOPED_RAND_RESET_I(32, 16031476294656798452ULL, 6445710628135343481ull);
}

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_cross_small_t__03a__03acg>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vt_covergroup_cross_small_t__03a__03acg::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::to_string\n"); );
    // Body
    return ("'{"s + to_string_middle() + "}");
}

std::string Vt_covergroup_cross_small_t__03a__03acg::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_cross_small_t__03a__03acg::to_string_middle\n"); );
    // Body
    std::string out;
    out += "option:" + VL_TO_STRING(__PVT__option);
    out += ", type_option:" + VL_TO_STRING(__PVT__type_option);
    out += ", __Vcov_cp_a_a0:" + VL_TO_STRING(__PVT____Vcov_cp_a_a0);
    out += ", __Vcov_cp_a_a1:" + VL_TO_STRING(__PVT____Vcov_cp_a_a1);
    out += ", __Vcov_cp_a_a2:" + VL_TO_STRING(__PVT____Vcov_cp_a_a2);
    out += ", __Vcov_cp_a_a3:" + VL_TO_STRING(__PVT____Vcov_cp_a_a3);
    out += ", __Vcov_cp_b_b0:" + VL_TO_STRING(__PVT____Vcov_cp_b_b0);
    out += ", __Vcov_cp_b_b1:" + VL_TO_STRING(__PVT____Vcov_cp_b_b1);
    out += ", __Vcov_cp_b_b2:" + VL_TO_STRING(__PVT____Vcov_cp_b_b2);
    out += ", __Vcov_cp_b_b3:" + VL_TO_STRING(__PVT____Vcov_cp_b_b3);
    out += ", __Vcov_cross_ab_a0_x__b0:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a0_x__b0);
    out += ", __Vcov_cross_ab_a0_x__b1:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a0_x__b1);
    out += ", __Vcov_cross_ab_a0_x__b2:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a0_x__b2);
    out += ", __Vcov_cross_ab_a0_x__b3:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a0_x__b3);
    out += ", __Vcov_cross_ab_a1_x__b0:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a1_x__b0);
    out += ", __Vcov_cross_ab_a1_x__b1:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a1_x__b1);
    out += ", __Vcov_cross_ab_a1_x__b2:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a1_x__b2);
    out += ", __Vcov_cross_ab_a1_x__b3:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a1_x__b3);
    out += ", __Vcov_cross_ab_a2_x__b0:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a2_x__b0);
    out += ", __Vcov_cross_ab_a2_x__b1:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a2_x__b1);
    out += ", __Vcov_cross_ab_a2_x__b2:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a2_x__b2);
    out += ", __Vcov_cross_ab_a2_x__b3:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a2_x__b3);
    out += ", __Vcov_cross_ab_a3_x__b0:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a3_x__b0);
    out += ", __Vcov_cross_ab_a3_x__b1:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a3_x__b1);
    out += ", __Vcov_cross_ab_a3_x__b2:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a3_x__b2);
    out += ", __Vcov_cross_ab_a3_x__b3:" + VL_TO_STRING(__PVT____Vcov_cross_ab_a3_x__b3);
    return (out);
}
