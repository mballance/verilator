// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_empty.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_EMPTY_STD__03A__03APROCESS__VCLPKG_H_
#define VERILATED_VT_COVERGROUP_EMPTY_STD__03A__03APROCESS__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "verilated_timing.h"
class Vt_covergroup_empty_std__03a__03aprocess;


class Vt_covergroup_empty__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_empty_std__03a__03aprocess__Vclpkg final {
  public:

    // INTERNAL VARIABLES
    Vt_covergroup_empty__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_empty_std__03a__03aprocess__Vclpkg();
    ~Vt_covergroup_empty_std__03a__03aprocess__Vclpkg();
    void ctor(Vt_covergroup_empty__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_empty_std__03a__03aprocess__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
    void __VnoInFunc_killQueue(Vt_covergroup_empty__Syms* __restrict vlSymsp, VlQueue<VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>> &processQueue);
    void __VnoInFunc_self(VlProcessRef vlProcess, Vt_covergroup_empty__Syms* __restrict vlSymsp, VlClassRef<Vt_covergroup_empty_std__03a__03aprocess> &self__Vfuncrtn);
};


class Vt_covergroup_empty__Syms;

class Vt_covergroup_empty_std__03a__03aprocess : public virtual VlClass {
  public:

    // DESIGN SPECIFIC STATE
    VlProcessRef __PVT__m_process;
    VlCoroutine __VnoInFunc_await(Vt_covergroup_empty__Syms* __restrict vlSymsp);
    void __VnoInFunc_get_randstate(Vt_covergroup_empty__Syms* __restrict vlSymsp, std::string &get_randstate__Vfuncrtn);
    void __VnoInFunc_kill(Vt_covergroup_empty__Syms* __restrict vlSymsp);
    void __VnoInFunc_resume(Vt_covergroup_empty__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_randstate(Vt_covergroup_empty__Syms* __restrict vlSymsp, std::string s);
    void __VnoInFunc_set_status(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ s);
    void __VnoInFunc_status(Vt_covergroup_empty__Syms* __restrict vlSymsp, IData/*31:0*/ &status__Vfuncrtn);
    void __VnoInFunc_suspend(Vt_covergroup_empty__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vt_covergroup_empty__Syms* __restrict vlSymsp);
  public:
    Vt_covergroup_empty_std__03a__03aprocess(Vt_covergroup_empty__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vt_covergroup_empty_std__03a__03aprocess() {}
};

std::string VL_TO_STRING(const VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>& obj);


//*** Below code from `systemc in Verilog file
// From `systemc at /home/mballance/projects/verilator/verilator-funccov/include/verilated_std.sv:197:21

template<> template<>
inline bool VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>::operator==(const VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>& rhs) const {
    if (!m_objp && !rhs.m_objp) return true;
    if (!m_objp || !rhs.m_objp) return false;
    return m_objp->__PVT__m_process == rhs.m_objp->__PVT__m_process;
};
template<> template<>
inline bool VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>::operator!=(const VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>& rhs) const {
    if (!m_objp && !rhs.m_objp) return false;
    if (!m_objp || !rhs.m_objp) return true;
    return m_objp->__PVT__m_process != rhs.m_objp->__PVT__m_process;
};
template<> template<>
inline bool VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>::operator<(const VlClassRef<Vt_covergroup_empty_std__03a__03aprocess>& rhs) const {
    if (!m_objp && !rhs.m_objp) return false;
    if (!m_objp || !rhs.m_objp) return false;
    return m_objp->__PVT__m_process < rhs.m_objp->__PVT__m_process;
};
//*** Above code from `systemc in Verilog file


#endif  // guard
