// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_auto_sample.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_AUTO_SAMPLE___024ROOT_H_
#define VERILATED_VT_COVERGROUP_AUTO_SAMPLE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"
class Vt_covergroup_auto_sample_std;
class Vt_covergroup_auto_sample_std__03a__03aprocess__Vclpkg;
class Vt_covergroup_auto_sample_std__03a__03asemaphore__Vclpkg;
class Vt_covergroup_auto_sample_t;
class Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg;


class Vt_covergroup_auto_sample__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_auto_sample___024root final {
  public:
    // CELLS
    Vt_covergroup_auto_sample_t* __PVT__t;
    Vt_covergroup_auto_sample_std* __PVT__std;
    Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg* t__03a__03acg__Vclpkg;
    Vt_covergroup_auto_sample_std__03a__03asemaphore__Vclpkg* std__03a__03asemaphore__Vclpkg;
    Vt_covergroup_auto_sample_std__03a__03aprocess__Vclpkg* std__03a__03aprocess__Vclpkg;

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDynamicTriggerScheduler __VdynSched;

    // INTERNAL VARIABLES
    Vt_covergroup_auto_sample__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_auto_sample___024root(Vt_covergroup_auto_sample__Syms* symsp, const char* namep);
    ~Vt_covergroup_auto_sample___024root();
    VL_UNCOPYABLE(Vt_covergroup_auto_sample___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
