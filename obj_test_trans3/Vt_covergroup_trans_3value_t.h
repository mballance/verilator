// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_trans_3value.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_TRANS_3VALUE_T_H_
#define VERILATED_VT_COVERGROUP_TRANS_3VALUE_T_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vt_covergroup_trans_3value_t__03a__03acg;


class Vt_covergroup_trans_3value__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_trans_3value_t final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*2:0*/ __PVT__state;
    CData/*2:0*/ __Vtogcov__state;
    IData/*31:0*/ __PVT__errors;
    VlClassRef<Vt_covergroup_trans_3value_t__03a__03acg> __PVT__cg_inst;

    // INTERNAL VARIABLES
    Vt_covergroup_trans_3value__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_trans_3value_t();
    ~Vt_covergroup_trans_3value_t();
    void ctor(Vt_covergroup_trans_3value__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_trans_3value_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
