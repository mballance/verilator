// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_cover_const_compare.h for the primary calling header

#ifndef VERILATED_VT_COVER_CONST_COMPARE___024ROOT_H_
#define VERILATED_VT_COVER_CONST_COMPARE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"


class Vt_cover_const_compare__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_cover_const_compare___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*0:0*/ t__DOT__a;
    CData/*0:0*/ t__DOT____Vtogcov__clk;
    CData/*0:0*/ t__DOT____Vtogcov__a;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ t__DOT__cyc;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vt_cover_const_compare__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vt_cover_const_compare___024root(Vt_cover_const_compare__Syms* symsp, const char* v__name);
    ~Vt_cover_const_compare___024root();
    VL_UNCOPYABLE(Vt_cover_const_compare___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
