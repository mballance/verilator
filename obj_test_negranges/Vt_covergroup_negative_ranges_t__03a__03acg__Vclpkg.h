// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_negative_ranges.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_NEGATIVE_RANGES_T__03A__03ACG__VCLPKG_H_
#define VERILATED_VT_COVERGROUP_NEGATIVE_RANGES_T__03A__03ACG__VCLPKG_H_  // guard

#include "verilated.h"
#include "Vt_covergroup_negative_ranges_std.h"


class Vt_covergroup_negative_ranges__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg final {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vint;

    // INTERNAL VARIABLES
    Vt_covergroup_negative_ranges__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg();
    ~Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg();
    void ctor(Vt_covergroup_negative_ranges__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_negative_ranges_t__03a__03acg__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __VnoInFunc_get_coverage(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn);
};


class Vt_covergroup_negative_ranges__Syms;

class Vt_covergroup_negative_ranges_t__03a__03acg : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vcov_cp_neg_negative;
    IData/*31:0*/ __PVT____Vcov_cp_neg_zero;
    IData/*31:0*/ __PVT____Vcov_cp_neg_positive;
    IData/*31:0*/ __PVT____Vcov_cp_neg_mixed;
    Vt_covergroup_negative_ranges_vl_covergroup_options_t__struct__0 __PVT__option;
    Vt_covergroup_negative_ranges_vl_covergroup_type_options_t__struct__0 __PVT__type_option;
    void __VnoInFunc_get_inst_coverage(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn);
    void __VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn);
    void __VnoInFunc_sample(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_inst_name(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string name);
    void __VnoInFunc_start(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp) {}
    void __VnoInFunc_stop(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp) {}
  private:
    void _ctor_var_reset(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
  public:
    Vt_covergroup_negative_ranges_t__03a__03acg(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_covergroup_negative_ranges_t__03a__03acg() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_negative_ranges_t__03a__03acg>& obj);

#endif  // guard
