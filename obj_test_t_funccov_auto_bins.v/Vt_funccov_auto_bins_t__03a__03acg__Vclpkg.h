// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_funccov_auto_bins.h for the primary calling header

#ifndef VERILATED_VT_FUNCCOV_AUTO_BINS_T__03A__03ACG__VCLPKG_H_
#define VERILATED_VT_FUNCCOV_AUTO_BINS_T__03A__03ACG__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"
#include "Vt_funccov_auto_bins_std.h"


class Vt_funccov_auto_bins__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_funccov_auto_bins_t__03a__03acg__Vclpkg final {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vint;

    // INTERNAL VARIABLES
    Vt_funccov_auto_bins__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_funccov_auto_bins_t__03a__03acg__Vclpkg();
    ~Vt_funccov_auto_bins_t__03a__03acg__Vclpkg();
    void ctor(Vt_funccov_auto_bins__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_funccov_auto_bins_t__03a__03acg__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __VnoInFunc_get_coverage(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn);
};


class Vt_funccov_auto_bins__Syms;

class Vt_funccov_auto_bins_t__03a__03acg : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vcov__auto_0_;
    IData/*31:0*/ __PVT____Vcov__auto_1_;
    IData/*31:0*/ __PVT____Vcov__auto_2_;
    IData/*31:0*/ __PVT____Vcov__auto_3_;
    Vt_funccov_auto_bins_vl_covergroup_options_t__struct__0 __PVT__option;
    Vt_funccov_auto_bins_vl_covergroup_type_options_t__struct__0 __PVT__type_option;
    void __VnoInFunc_get_inst_coverage(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn);
    void __VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn);
    void __VnoInFunc_sample(Vt_funccov_auto_bins__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_inst_name(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, std::string name);
    void __VnoInFunc_start(Vt_funccov_auto_bins__Syms* __restrict vlSymsp) {}
    void __VnoInFunc_stop(Vt_funccov_auto_bins__Syms* __restrict vlSymsp) {}
  private:
    void _ctor_var_reset(Vt_funccov_auto_bins__Syms* __restrict vlSymsp);
  public:
    Vt_funccov_auto_bins_t__03a__03acg(Vt_funccov_auto_bins__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_funccov_auto_bins_t__03a__03acg() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_funccov_auto_bins_t__03a__03acg>& obj);

#endif  // guard
