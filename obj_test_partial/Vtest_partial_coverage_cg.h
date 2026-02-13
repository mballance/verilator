// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtest_partial_coverage.h for the primary calling header

#ifndef VERILATED_VTEST_PARTIAL_COVERAGE_CG_H_
#define VERILATED_VTEST_PARTIAL_COVERAGE_CG_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"

#include "Vtest_partial_coverage_std.h"

class Vtest_partial_coverage__Syms;

class Vtest_partial_coverage_cg : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    Vtest_partial_coverage_vl_covergroup_options_t__struct__0 __PVT__option;
    Vtest_partial_coverage_vl_covergroup_type_options_t__struct__0 __PVT__type_option;
    IData/*31:0*/ __PVT____Vcov_cp_addr_low;
    IData/*31:0*/ __PVT____Vcov_cp_addr_high;

    // INTERNAL VARIABLES
    Vtest_partial_coverage__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtest_partial_coverage_cg();
    ~Vtest_partial_coverage_cg();
    void ctor(Vtest_partial_coverage__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtest_partial_coverage_cg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
    void __VnoInFunc_get_coverage(Vtest_partial_coverage__Syms* __restrict vlSymsp, double &get_coverage__Vfuncrtn);
    void __VnoInFunc_get_inst_coverage(Vtest_partial_coverage__Syms* __restrict vlSymsp, double &get_inst_coverage__Vfuncrtn);
    void __VnoInFunc_sample(Vtest_partial_coverage__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_inst_name(Vtest_partial_coverage__Syms* __restrict vlSymsp, std::string name);
    void __VnoInFunc_start(Vtest_partial_coverage__Syms* __restrict vlSymsp);
    void __VnoInFunc_stop(Vtest_partial_coverage__Syms* __restrict vlSymsp);
    Vtest_partial_coverage_cg(Vtest_partial_coverage__Syms* __restrict vlSymsp);
};


#endif  // guard
