// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtest_partial_coverage.h for the primary calling header

#ifndef VERILATED_VTEST_PARTIAL_COVERAGE_STD__03A__03ASEMAPHORE__VCLPKG_H_
#define VERILATED_VTEST_PARTIAL_COVERAGE_STD__03A__03ASEMAPHORE__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"


class Vtest_partial_coverage__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg final {
  public:

    // INTERNAL VARIABLES
    Vtest_partial_coverage__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg();
    ~Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg();
    void ctor(Vtest_partial_coverage__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtest_partial_coverage_std__03a__03asemaphore__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


class Vtest_partial_coverage__Syms;

class Vtest_partial_coverage_std__03a__03asemaphore : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__m_keyCount;
    void __VnoInFunc_get(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_put(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_try_get(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount, IData/*31:0*/ &try_get__Vfuncrtn);
  private:
    void _ctor_var_reset(Vtest_partial_coverage__Syms* __restrict vlSymsp);
  public:
    Vtest_partial_coverage_std__03a__03asemaphore(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vtest_partial_coverage_std__03a__03asemaphore() {}
};

std::string VL_TO_STRING(const VlClassRef<Vtest_partial_coverage_std__03a__03asemaphore>& obj);

#endif  // guard
