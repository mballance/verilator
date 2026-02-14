// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vt_covergroup_negative_ranges__pch.h"

//============================================================
// Constructors

Vt_covergroup_negative_ranges::Vt_covergroup_negative_ranges(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vt_covergroup_negative_ranges__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , __PVT__t{vlSymsp->TOP.__PVT__t}
    , __PVT__std{vlSymsp->TOP.__PVT__std}
    , t__03a__03acg__Vclpkg{vlSymsp->TOP.t__03a__03acg__Vclpkg}
    , std__03a__03asemaphore__Vclpkg{vlSymsp->TOP.std__03a__03asemaphore__Vclpkg}
    , std__03a__03aprocess__Vclpkg{vlSymsp->TOP.std__03a__03aprocess__Vclpkg}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vt_covergroup_negative_ranges::Vt_covergroup_negative_ranges(const char* _vcname__)
    : Vt_covergroup_negative_ranges(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vt_covergroup_negative_ranges::~Vt_covergroup_negative_ranges() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vt_covergroup_negative_ranges___024root___eval_debug_assertions(Vt_covergroup_negative_ranges___024root* vlSelf);
#endif  // VL_DEBUG
void Vt_covergroup_negative_ranges___024root___eval_static(Vt_covergroup_negative_ranges___024root* vlSelf);
void Vt_covergroup_negative_ranges___024root___eval_initial(Vt_covergroup_negative_ranges___024root* vlSelf);
void Vt_covergroup_negative_ranges___024root___eval_settle(Vt_covergroup_negative_ranges___024root* vlSelf);
void Vt_covergroup_negative_ranges___024root___eval(Vt_covergroup_negative_ranges___024root* vlSelf);

void Vt_covergroup_negative_ranges::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vt_covergroup_negative_ranges::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vt_covergroup_negative_ranges___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vt_covergroup_negative_ranges___024root___eval_static(&(vlSymsp->TOP));
        Vt_covergroup_negative_ranges___024root___eval_initial(&(vlSymsp->TOP));
        Vt_covergroup_negative_ranges___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vt_covergroup_negative_ranges___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vt_covergroup_negative_ranges::eventsPending() { return false; }

uint64_t Vt_covergroup_negative_ranges::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vt_covergroup_negative_ranges::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vt_covergroup_negative_ranges___024root___eval_final(Vt_covergroup_negative_ranges___024root* vlSelf);

VL_ATTR_COLD void Vt_covergroup_negative_ranges::final() {
    Vt_covergroup_negative_ranges___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vt_covergroup_negative_ranges::hierName() const { return vlSymsp->name(); }
const char* Vt_covergroup_negative_ranges::modelName() const { return "Vt_covergroup_negative_ranges"; }
unsigned Vt_covergroup_negative_ranges::threads() const { return 1; }
void Vt_covergroup_negative_ranges::prepareClone() const { contextp()->prepareClone(); }
void Vt_covergroup_negative_ranges::atClone() const {
    contextp()->threadPoolpOnClone();
}
