// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_funccov_auto_bins.h for the primary calling header

#ifndef VERILATED_VT_FUNCCOV_AUTO_BINS___024ROOT_H_
#define VERILATED_VT_FUNCCOV_AUTO_BINS___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"
class Vt_funccov_auto_bins_std;
class Vt_funccov_auto_bins_std__03a__03aprocess__Vclpkg;
class Vt_funccov_auto_bins_std__03a__03asemaphore__Vclpkg;
class Vt_funccov_auto_bins_t;
class Vt_funccov_auto_bins_t__03a__03acg__Vclpkg;


class Vt_funccov_auto_bins__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_funccov_auto_bins___024root final {
  public:
    // CELLS
    Vt_funccov_auto_bins_t* __PVT__t;
    Vt_funccov_auto_bins_std* __PVT__std;
    Vt_funccov_auto_bins_t__03a__03acg__Vclpkg* t__03a__03acg__Vclpkg;
    Vt_funccov_auto_bins_std__03a__03asemaphore__Vclpkg* std__03a__03asemaphore__Vclpkg;
    Vt_funccov_auto_bins_std__03a__03aprocess__Vclpkg* std__03a__03aprocess__Vclpkg;

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDynamicTriggerScheduler __VdynSched;

    // INTERNAL VARIABLES
    Vt_funccov_auto_bins__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_funccov_auto_bins___024root(Vt_funccov_auto_bins__Syms* symsp, const char* namep);
    ~Vt_funccov_auto_bins___024root();
    VL_UNCOPYABLE(Vt_funccov_auto_bins___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
