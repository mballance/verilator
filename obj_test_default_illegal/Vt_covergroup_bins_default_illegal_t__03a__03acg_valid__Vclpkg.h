// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_BINS_DEFAULT_ILLEGAL_T__03A__03ACG_VALID__VCLPKG_H_
#define VERILATED_VT_COVERGROUP_BINS_DEFAULT_ILLEGAL_T__03A__03ACG_VALID__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "Vt_covergroup_bins_default_illegal_std.h"


class Vt_covergroup_bins_default_illegal__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg final {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vint;

    // INTERNAL VARIABLES
    Vt_covergroup_bins_default_illegal__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg();
    ~Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg();
    void ctor(Vt_covergroup_bins_default_illegal__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_bins_default_illegal_t__03a__03acg_valid__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
    void __VnoInFunc_get_coverage(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_coverage__Vfuncrtn);
};


class Vt_covergroup_bins_default_illegal__Syms;

class Vt_covergroup_bins_default_illegal_t__03a__03acg_valid : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT____Vcov__valid;
    IData/*31:0*/ __PVT____Vcov__reserved;
    Vt_covergroup_bins_default_illegal_vl_covergroup_options_t__struct__0 __PVT__option;
    Vt_covergroup_bins_default_illegal_vl_covergroup_type_options_t__struct__0 __PVT__type_option;
    void __VnoInFunc_get_inst_coverage(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string covered_bins, std::string total_bins, double &get_inst_coverage__Vfuncrtn);
    void __VnoInFunc_get_inst_coverage__Vtcwrap_1_2(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, double &get_inst_coverage__Vtcwrap_1_2__Vfuncrtn);
    void __VnoInFunc_sample(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_inst_name(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp, std::string name);
    void __VnoInFunc_start(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp);
    void __VnoInFunc_stop(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp);
  public:
    Vt_covergroup_bins_default_illegal_t__03a__03acg_valid(Vt_covergroup_bins_default_illegal__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_covergroup_bins_default_illegal_t__03a__03acg_valid() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_bins_default_illegal_t__03a__03acg_valid>& obj);

#endif  // guard
