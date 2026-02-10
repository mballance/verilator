// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_funccov_auto_bins.h for the primary calling header

#ifndef VERILATED_VT_FUNCCOV_AUTO_BINS_T_H_
#define VERILATED_VT_FUNCCOV_AUTO_BINS_T_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"
class Vt_funccov_auto_bins_t__03a__03acg;


class Vt_funccov_auto_bins__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_funccov_auto_bins_t final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*2:0*/ __PVT__data;

    // INTERNAL VARIABLES
    Vt_funccov_auto_bins__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_funccov_auto_bins_t();
    ~Vt_funccov_auto_bins_t();
    void ctor(Vt_funccov_auto_bins__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_funccov_auto_bins_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
};


#endif  // guard
