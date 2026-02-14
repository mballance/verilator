// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_cross_small.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_CROSS_SMALL_T__03A__03ACG__VCLPKG_H_
#define VERILATED_VT_COVERGROUP_CROSS_SMALL_T__03A__03ACG__VCLPKG_H_  // guard

#include "verilated.h"
#include "Vt_covergroup_cross_small_std.h"


class Vt_covergroup_cross_small__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_cross_small_t__03a__03acg__Vclpkg final {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vint;

    // INTERNAL VARIABLES
    Vt_covergroup_cross_small__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_cross_small_t__03a__03acg__Vclpkg();
    ~Vt_covergroup_cross_small_t__03a__03acg__Vclpkg();
    void ctor(Vt_covergroup_cross_small__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_cross_small_t__03a__03acg__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __VnoInFunc_get_coverage(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn);
};


class Vt_covergroup_cross_small__Syms;

class Vt_covergroup_cross_small_t__03a__03acg : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vcov_cp_a_a0;
    IData/*31:0*/ __PVT____Vcov_cp_a_a1;
    IData/*31:0*/ __PVT____Vcov_cp_a_a2;
    IData/*31:0*/ __PVT____Vcov_cp_a_a3;
    IData/*31:0*/ __PVT____Vcov_cp_b_b0;
    IData/*31:0*/ __PVT____Vcov_cp_b_b1;
    IData/*31:0*/ __PVT____Vcov_cp_b_b2;
    IData/*31:0*/ __PVT____Vcov_cp_b_b3;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a0_x__b0;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a0_x__b1;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a0_x__b2;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a0_x__b3;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a1_x__b0;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a1_x__b1;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a1_x__b2;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a1_x__b3;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a2_x__b0;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a2_x__b1;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a2_x__b2;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a2_x__b3;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a3_x__b0;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a3_x__b1;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a3_x__b2;
    IData/*31:0*/ __PVT____Vcov_cross_ab_a3_x__b3;
    Vt_covergroup_cross_small_vl_covergroup_options_t__struct__0 __PVT__option;
    Vt_covergroup_cross_small_vl_covergroup_type_options_t__struct__0 __PVT__type_option;
    void __VnoInFunc_get_inst_coverage(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn);
    void __VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn);
    void __VnoInFunc_sample(Vt_covergroup_cross_small__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_inst_name(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, std::string name);
    void __VnoInFunc_start(Vt_covergroup_cross_small__Syms* __restrict vlSymsp) {}
    void __VnoInFunc_stop(Vt_covergroup_cross_small__Syms* __restrict vlSymsp) {}
  private:
    void _ctor_var_reset(Vt_covergroup_cross_small__Syms* __restrict vlSymsp);
  public:
    Vt_covergroup_cross_small_t__03a__03acg(Vt_covergroup_cross_small__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_covergroup_cross_small_t__03a__03acg() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_cross_small_t__03a__03acg>& obj);

#endif  // guard
