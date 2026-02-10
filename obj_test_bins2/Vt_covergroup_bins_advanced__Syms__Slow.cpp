// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vt_covergroup_bins_advanced__pch.h"

Vt_covergroup_bins_advanced__Syms::Vt_covergroup_bins_advanced__Syms(VerilatedContext* contextp, const char* namep, Vt_covergroup_bins_advanced* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(702);
    // Setup sub module instances
    TOP__std.ctor(this, "std");
    TOP__t.ctor(this, "t");
    TOP__std__03a__03aprocess__Vclpkg.ctor(this, "std::process__Vclpkg");
    TOP__std__03a__03asemaphore__Vclpkg.ctor(this, "std::semaphore__Vclpkg");
    TOP__t__03a__03acg_array__Vclpkg.ctor(this, "t::cg_array__Vclpkg");
    TOP__t__03a__03acg_ignore__Vclpkg.ctor(this, "t::cg_ignore__Vclpkg");
    TOP__t__03a__03acg_wildcard__Vclpkg.ctor(this, "t::cg_wildcard__Vclpkg");
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT__std = &TOP__std;
    TOP.__PVT__t = &TOP__t;
    TOP.std__03a__03aprocess__Vclpkg = &TOP__std__03a__03aprocess__Vclpkg;
    TOP.std__03a__03asemaphore__Vclpkg = &TOP__std__03a__03asemaphore__Vclpkg;
    TOP.t__03a__03acg_array__Vclpkg = &TOP__t__03a__03acg_array__Vclpkg;
    TOP.t__03a__03acg_ignore__Vclpkg = &TOP__t__03a__03acg_ignore__Vclpkg;
    TOP.t__03a__03acg_wildcard__Vclpkg = &TOP__t__03a__03acg_wildcard__Vclpkg;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP__std.__Vconfigure(true);
    TOP__t.__Vconfigure(true);
    TOP__std__03a__03aprocess__Vclpkg.__Vconfigure(true);
    TOP__std__03a__03asemaphore__Vclpkg.__Vconfigure(true);
    TOP__t__03a__03acg_array__Vclpkg.__Vconfigure(true);
    TOP__t__03a__03acg_ignore__Vclpkg.__Vconfigure(true);
    TOP__t__03a__03acg_wildcard__Vclpkg.__Vconfigure(true);
    // Setup scopes
}

Vt_covergroup_bins_advanced__Syms::~Vt_covergroup_bins_advanced__Syms() {
    // Tear down scopes
    // Tear down sub module instances
    TOP__t__03a__03acg_wildcard__Vclpkg.dtor();
    TOP__t__03a__03acg_ignore__Vclpkg.dtor();
    TOP__t__03a__03acg_array__Vclpkg.dtor();
    TOP__std__03a__03asemaphore__Vclpkg.dtor();
    TOP__std__03a__03aprocess__Vclpkg.dtor();
    TOP__t.dtor();
    TOP__std.dtor();
}
