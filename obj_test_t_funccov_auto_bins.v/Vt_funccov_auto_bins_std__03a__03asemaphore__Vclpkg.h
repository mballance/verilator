// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_funccov_auto_bins.h for the primary calling header

#ifndef VERILATED_VT_FUNCCOV_AUTO_BINS_STD__03A__03ASEMAPHORE__VCLPKG_H_
#define VERILATED_VT_FUNCCOV_AUTO_BINS_STD__03A__03ASEMAPHORE__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"


class Vt_funccov_auto_bins__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_funccov_auto_bins_std__03a__03asemaphore__Vclpkg final {
  public:

    // INTERNAL VARIABLES
    Vt_funccov_auto_bins__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_funccov_auto_bins_std__03a__03asemaphore__Vclpkg();
    ~Vt_funccov_auto_bins_std__03a__03asemaphore__Vclpkg();
    void ctor(Vt_funccov_auto_bins__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_funccov_auto_bins_std__03a__03asemaphore__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


class Vt_funccov_auto_bins__Syms;

class Vt_funccov_auto_bins_std__03a__03asemaphore : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__m_keyCount;
    VlCoroutine __VnoInFunc_get(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_put(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_try_get(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount, IData/*31:0*/ &try_get__Vfuncrtn);
  private:
    void _ctor_var_reset(Vt_funccov_auto_bins__Syms* __restrict vlSymsp);
  public:
    Vt_funccov_auto_bins_std__03a__03asemaphore(Vt_funccov_auto_bins__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_funccov_auto_bins_std__03a__03asemaphore() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_funccov_auto_bins_std__03a__03asemaphore>& obj);

#endif  // guard
