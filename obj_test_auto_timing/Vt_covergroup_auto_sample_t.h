// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_auto_sample.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_AUTO_SAMPLE_T_H_
#define VERILATED_VT_COVERGROUP_AUTO_SAMPLE_T_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"
class Vt_covergroup_auto_sample_t__03a__03acg;


class Vt_covergroup_auto_sample__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_auto_sample_t final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ clk;
    CData/*1:0*/ __PVT__data;
    CData/*0:0*/ __Vtogcov__clk;
    CData/*1:0*/ __Vtogcov__data;
    IData/*31:0*/ __PVT__cyc;
    VlClassRef<Vt_covergroup_auto_sample_t__03a__03acg> __PVT__cg_inst;

    // INTERNAL VARIABLES
    Vt_covergroup_auto_sample__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_auto_sample_t();
    ~Vt_covergroup_auto_sample_t();
    void ctor(Vt_covergroup_auto_sample__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_auto_sample_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
