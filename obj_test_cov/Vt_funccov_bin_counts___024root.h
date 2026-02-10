// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_funccov_bin_counts.h for the primary calling header

#ifndef VERILATED_VT_FUNCCOV_BIN_COUNTS___024ROOT_H_
#define VERILATED_VT_FUNCCOV_BIN_COUNTS___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vt_funccov_bin_counts_std;
class Vt_funccov_bin_counts_std__03a__03aprocess__Vclpkg;
class Vt_funccov_bin_counts_std__03a__03asemaphore__Vclpkg;
class Vt_funccov_bin_counts_t;
class Vt_funccov_bin_counts_t__03a__03acg__Vclpkg;


class Vt_funccov_bin_counts__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_funccov_bin_counts___024root final {
  public:
    // CELLS
    Vt_funccov_bin_counts_t* __PVT__t;
    Vt_funccov_bin_counts_std* __PVT__std;
    Vt_funccov_bin_counts_t__03a__03acg__Vclpkg* t__03a__03acg__Vclpkg;
    Vt_funccov_bin_counts_std__03a__03asemaphore__Vclpkg* std__03a__03asemaphore__Vclpkg;
    Vt_funccov_bin_counts_std__03a__03aprocess__Vclpkg* std__03a__03aprocess__Vclpkg;

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;

    // INTERNAL VARIABLES
    Vt_funccov_bin_counts__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_funccov_bin_counts___024root(Vt_funccov_bin_counts__Syms* symsp, const char* namep);
    ~Vt_funccov_bin_counts___024root();
    VL_UNCOPYABLE(Vt_funccov_bin_counts___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
