// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_cross_small.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_CROSS_SMALL_STD__03A__03ASEMAPHORE__VCLPKG_H_
#define VERILATED_VT_COVERGROUP_CROSS_SMALL_STD__03A__03ASEMAPHORE__VCLPKG_H_  // guard

#include "verilated.h"


class Vt_covergroup_cross_small__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_cross_small_std__03a__03asemaphore__Vclpkg final {
  public:

    // INTERNAL VARIABLES
    Vt_covergroup_cross_small__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_cross_small_std__03a__03asemaphore__Vclpkg();
    ~Vt_covergroup_cross_small_std__03a__03asemaphore__Vclpkg();
    void ctor(Vt_covergroup_cross_small__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_cross_small_std__03a__03asemaphore__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vt_covergroup_cross_small__Syms;

class Vt_covergroup_cross_small_std__03a__03asemaphore : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__m_keyCount;
    void __VnoInFunc_get(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_put(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_try_get(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount, IData/*31:0*/ &try_get__Vfuncrtn);
  private:
    void _ctor_var_reset(Vt_covergroup_cross_small__Syms* __restrict vlSymsp);
  public:
    Vt_covergroup_cross_small_std__03a__03asemaphore(Vt_covergroup_cross_small__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_covergroup_cross_small_std__03a__03asemaphore() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_cross_small_std__03a__03asemaphore>& obj);

#endif  // guard
