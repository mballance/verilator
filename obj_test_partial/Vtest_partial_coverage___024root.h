// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtest_partial_coverage.h for the primary calling header

#ifndef VERILATED_VTEST_PARTIAL_COVERAGE___024ROOT_H_
#define VERILATED_VTEST_PARTIAL_COVERAGE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vtest_partial_coverage_std;
class Vtest_partial_coverage_std__03a__03aprocess__Vclpkg;
class Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg;
class Vtest_partial_coverage_t;


class Vtest_partial_coverage__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtest_partial_coverage___024root final {
  public:
    // CELLS
    Vtest_partial_coverage_t* __PVT__t;
    Vtest_partial_coverage_std* __PVT__std;
    Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg* std__03a__03asemaphore__Vclpkg;
    Vtest_partial_coverage_std__03a__03aprocess__Vclpkg* std__03a__03aprocess__Vclpkg;

    // INTERNAL VARIABLES
    Vtest_partial_coverage__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtest_partial_coverage___024root(Vtest_partial_coverage__Syms* symsp, const char* namep);
    ~Vtest_partial_coverage___024root();
    VL_UNCOPYABLE(Vtest_partial_coverage___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
