// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_autobins.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_AUTOBINS___024ROOT_H_
#define VERILATED_VT_COVERGROUP_AUTOBINS___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vt_covergroup_autobins_std;
class Vt_covergroup_autobins_std__03a__03aprocess__Vclpkg;
class Vt_covergroup_autobins_std__03a__03asemaphore__Vclpkg;
class Vt_covergroup_autobins_t;
class Vt_covergroup_autobins_t__03a__03acg1__Vclpkg;
class Vt_covergroup_autobins_t__03a__03acg2__Vclpkg;
class Vt_covergroup_autobins_t__03a__03acg3__Vclpkg;
class Vt_covergroup_autobins_t__03a__03acg4__Vclpkg;
class Vt_covergroup_autobins_t__03a__03acg5__Vclpkg;


class Vt_covergroup_autobins__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_autobins___024root final {
  public:
    // CELLS
    Vt_covergroup_autobins_t* __PVT__t;
    Vt_covergroup_autobins_std* __PVT__std;
    Vt_covergroup_autobins_t__03a__03acg1__Vclpkg* t__03a__03acg1__Vclpkg;
    Vt_covergroup_autobins_t__03a__03acg2__Vclpkg* t__03a__03acg2__Vclpkg;
    Vt_covergroup_autobins_t__03a__03acg3__Vclpkg* t__03a__03acg3__Vclpkg;
    Vt_covergroup_autobins_t__03a__03acg4__Vclpkg* t__03a__03acg4__Vclpkg;
    Vt_covergroup_autobins_t__03a__03acg5__Vclpkg* t__03a__03acg5__Vclpkg;
    Vt_covergroup_autobins_std__03a__03asemaphore__Vclpkg* std__03a__03asemaphore__Vclpkg;
    Vt_covergroup_autobins_std__03a__03aprocess__Vclpkg* std__03a__03aprocess__Vclpkg;

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);

    // INTERNAL VARIABLES
    Vt_covergroup_autobins__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_autobins___024root(Vt_covergroup_autobins__Syms* symsp, const char* namep);
    ~Vt_covergroup_autobins___024root();
    VL_UNCOPYABLE(Vt_covergroup_autobins___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
