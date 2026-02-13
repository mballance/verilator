// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtest_partial_coverage.h for the primary calling header

#ifndef VERILATED_VTEST_PARTIAL_COVERAGE_STD__03A__03APROCESS__VCLPKG_H_
#define VERILATED_VTEST_PARTIAL_COVERAGE_STD__03A__03APROCESS__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class Vtest_partial_coverage_std__03a__03aprocess;


class Vtest_partial_coverage__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtest_partial_coverage_std__03a__03aprocess__Vclpkg final {
  public:

    // INTERNAL VARIABLES
    Vtest_partial_coverage__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtest_partial_coverage_std__03a__03aprocess__Vclpkg();
    ~Vtest_partial_coverage_std__03a__03aprocess__Vclpkg();
    void ctor(Vtest_partial_coverage__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtest_partial_coverage_std__03a__03aprocess__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
    void __VnoInFunc_killQueue(Vtest_partial_coverage__Syms* __restrict vlSymsp, VlQueue<VlClassRef<Vtest_partial_coverage_std__03a__03aprocess>> &processQueue);
    void __VnoInFunc_self(VlProcessRef vlProcess, Vtest_partial_coverage__Syms* __restrict vlSymsp, VlClassRef<Vtest_partial_coverage_std__03a__03aprocess> &self__Vfuncrtn);
};


class Vtest_partial_coverage__Syms;

class Vtest_partial_coverage_std__03a__03aprocess : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    VlProcessRef __PVT__m_process;
    void __VnoInFunc_await(Vtest_partial_coverage__Syms* __restrict vlSymsp);
    void __VnoInFunc_get_randstate(Vtest_partial_coverage__Syms* __restrict vlSymsp, std::string &get_randstate__Vfuncrtn);
    void __VnoInFunc_kill(Vtest_partial_coverage__Syms* __restrict vlSymsp);
    void __VnoInFunc_resume(Vtest_partial_coverage__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_randstate(Vtest_partial_coverage__Syms* __restrict vlSymsp, std::string s);
    void __VnoInFunc_set_status(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ s);
    void __VnoInFunc_status(Vtest_partial_coverage__Syms* __restrict vlSymsp, IData/*31:0*/ &status__Vfuncrtn);
    void __VnoInFunc_suspend(Vtest_partial_coverage__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vtest_partial_coverage__Syms* __restrict vlSymsp);
  public:
    Vtest_partial_coverage_std__03a__03aprocess(Vtest_partial_coverage__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vtest_partial_coverage_std__03a__03aprocess() {}
};

std::string VL_TO_STRING(const VlClassRef<Vtest_partial_coverage_std__03a__03aprocess>& obj);

#endif  // guard
