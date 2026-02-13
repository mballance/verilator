// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtest_partial_coverage__pch.h"

//============================================================
// Constructors

Vtest_partial_coverage::Vtest_partial_coverage(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtest_partial_coverage__Syms(contextp(), _vcname__, this)}
    , __PVT__t{vlSymsp->TOP.__PVT__t}
    , __PVT__std{vlSymsp->TOP.__PVT__std}
    , std__03a__03asemaphore__Vclpkg{vlSymsp->TOP.std__03a__03asemaphore__Vclpkg}
    , std__03a__03aprocess__Vclpkg{vlSymsp->TOP.std__03a__03aprocess__Vclpkg}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtest_partial_coverage::Vtest_partial_coverage(const char* _vcname__)
    : Vtest_partial_coverage(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtest_partial_coverage::~Vtest_partial_coverage() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtest_partial_coverage___024root___eval_debug_assertions(Vtest_partial_coverage___024root* vlSelf);
#endif  // VL_DEBUG
void Vtest_partial_coverage___024root___eval_static(Vtest_partial_coverage___024root* vlSelf);
void Vtest_partial_coverage___024root___eval_initial(Vtest_partial_coverage___024root* vlSelf);
void Vtest_partial_coverage___024root___eval_settle(Vtest_partial_coverage___024root* vlSelf);
void Vtest_partial_coverage___024root___eval(Vtest_partial_coverage___024root* vlSelf);

void Vtest_partial_coverage::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtest_partial_coverage::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtest_partial_coverage___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtest_partial_coverage___024root___eval_static(&(vlSymsp->TOP));
        Vtest_partial_coverage___024root___eval_initial(&(vlSymsp->TOP));
        Vtest_partial_coverage___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtest_partial_coverage___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtest_partial_coverage::eventsPending() { return false; }

uint64_t Vtest_partial_coverage::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vtest_partial_coverage::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtest_partial_coverage___024root___eval_final(Vtest_partial_coverage___024root* vlSelf);

VL_ATTR_COLD void Vtest_partial_coverage::final() {
    Vtest_partial_coverage___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtest_partial_coverage::hierName() const { return vlSymsp->name(); }
const char* Vtest_partial_coverage::modelName() const { return "Vtest_partial_coverage"; }
unsigned Vtest_partial_coverage::threads() const { return 1; }
void Vtest_partial_coverage::prepareClone() const { contextp()->prepareClone(); }
void Vtest_partial_coverage::atClone() const {
    contextp()->threadPoolpOnClone();
}
