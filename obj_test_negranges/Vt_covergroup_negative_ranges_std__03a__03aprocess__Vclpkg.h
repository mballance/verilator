// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_negative_ranges.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_NEGATIVE_RANGES_STD__03A__03APROCESS__VCLPKG_H_
#define VERILATED_VT_COVERGROUP_NEGATIVE_RANGES_STD__03A__03APROCESS__VCLPKG_H_  // guard

#include "verilated.h"
class Vt_covergroup_negative_ranges_std__03a__03aprocess;


class Vt_covergroup_negative_ranges__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg final {
  public:

    // INTERNAL VARIABLES
    Vt_covergroup_negative_ranges__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg();
    ~Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg();
    void ctor(Vt_covergroup_negative_ranges__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_negative_ranges_std__03a__03aprocess__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __VnoInFunc_killQueue(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, VlQueue<VlClassRef<Vt_covergroup_negative_ranges_std__03a__03aprocess>> &processQueue);
    void __VnoInFunc_self(VlProcessRef vlProcess, Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, VlClassRef<Vt_covergroup_negative_ranges_std__03a__03aprocess> &self__Vfuncrtn);
};


class Vt_covergroup_negative_ranges__Syms;

class Vt_covergroup_negative_ranges_std__03a__03aprocess : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    VlProcessRef __PVT__m_process;
    void __VnoInFunc_await(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp) {}
    void __VnoInFunc_get_randstate(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string &get_randstate__Vfuncrtn);
    void __VnoInFunc_kill(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
    void __VnoInFunc_resume(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_randstate(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, std::string s);
    void __VnoInFunc_set_status(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, IData/*31:0*/ s);
    void __VnoInFunc_status(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp, IData/*31:0*/ &status__Vfuncrtn);
    void __VnoInFunc_suspend(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
  public:
    Vt_covergroup_negative_ranges_std__03a__03aprocess(Vt_covergroup_negative_ranges__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_covergroup_negative_ranges_std__03a__03aprocess() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_negative_ranges_std__03a__03aprocess>& obj);

#endif  // guard
