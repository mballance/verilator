// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_funccov_bin_counts.h for the primary calling header

#ifndef VERILATED_VT_FUNCCOV_BIN_COUNTS_T_H_
#define VERILATED_VT_FUNCCOV_BIN_COUNTS_T_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vt_funccov_bin_counts_t__03a__03acg;


class Vt_funccov_bin_counts__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_funccov_bin_counts_t final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*3:0*/ __PVT__data;
    CData/*3:0*/ __Vtogcov__data;
    std::string __Vtask_check_coverage__7__label;

    // INTERNAL VARIABLES
    Vt_funccov_bin_counts__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_funccov_bin_counts_t();
    ~Vt_funccov_bin_counts_t();
    void ctor(Vt_funccov_bin_counts__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_funccov_bin_counts_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
