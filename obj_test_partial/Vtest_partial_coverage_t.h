// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtest_partial_coverage.h for the primary calling header

#ifndef VERILATED_VTEST_PARTIAL_COVERAGE_T_H_
#define VERILATED_VTEST_PARTIAL_COVERAGE_T_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "Vtest_partial_coverage_std.h"
class Vtest_partial_coverage_cg;


class Vtest_partial_coverage__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtest_partial_coverage_t final {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__addr;

    // INTERNAL VARIABLES
    Vtest_partial_coverage__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtest_partial_coverage_t();
    ~Vtest_partial_coverage_t();
    void ctor(Vtest_partial_coverage__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtest_partial_coverage_t);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
