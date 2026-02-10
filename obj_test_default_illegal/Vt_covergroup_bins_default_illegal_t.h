// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_BINS_DEFAULT_ILLEGAL_T_H_
#define VERILATED_VT_COVERGROUP_BINS_DEFAULT_ILLEGAL_T_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vt_covergroup_bins_default_illegal_t__03a__03acg_default;
class Vt_covergroup_bins_default_illegal_t__03a__03acg_valid;


class Vt_covergroup_bins_default_illegal__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_bins_default_illegal_t final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*3:0*/ __PVT__data;
    CData/*3:0*/ __Vtogcov__data;
    IData/*31:0*/ __PVT__error_count;

    // INTERNAL VARIABLES
    Vt_covergroup_bins_default_illegal__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_bins_default_illegal_t();
    ~Vt_covergroup_bins_default_illegal_t();
    void ctor(Vt_covergroup_bins_default_illegal__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_bins_default_illegal_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
