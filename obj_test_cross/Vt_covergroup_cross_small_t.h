// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_cross_small.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_CROSS_SMALL_T_H_
#define VERILATED_VT_COVERGROUP_CROSS_SMALL_T_H_  // guard

#include "verilated.h"
class Vt_covergroup_cross_small_t__03a__03acg;


class Vt_covergroup_cross_small__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_cross_small_t final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ clk;
    CData/*3:0*/ __PVT__a;
    CData/*3:0*/ __PVT__b;
    IData/*31:0*/ __PVT__cyc;
    double __PVT__unnamedblk1__DOT__inst_cov;
    VlClassRef<Vt_covergroup_cross_small_t__03a__03acg> __PVT__cg_inst;

    // INTERNAL VARIABLES
    Vt_covergroup_cross_small__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_cross_small_t();
    ~Vt_covergroup_cross_small_t();
    void ctor(Vt_covergroup_cross_small__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_cross_small_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
