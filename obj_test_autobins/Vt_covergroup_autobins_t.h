// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_autobins.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_AUTOBINS_T_H_
#define VERILATED_VT_COVERGROUP_AUTOBINS_T_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vt_covergroup_autobins_t__03a__03acg1;
class Vt_covergroup_autobins_t__03a__03acg2;
class Vt_covergroup_autobins_t__03a__03acg3;
class Vt_covergroup_autobins_t__03a__03acg4;
class Vt_covergroup_autobins_t__03a__03acg5;


class Vt_covergroup_autobins__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_autobins_t final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ clk;
    CData/*2:0*/ __PVT__data3;
    CData/*1:0*/ __PVT__data2;

    // INTERNAL VARIABLES
    Vt_covergroup_autobins__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_autobins_t();
    ~Vt_covergroup_autobins_t();
    void ctor(Vt_covergroup_autobins__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_autobins_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
