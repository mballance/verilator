// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vt_funccov_bin_counts__pch.h"

//============================================================
// Constructors

Vt_funccov_bin_counts::Vt_funccov_bin_counts(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vt_funccov_bin_counts__Syms(contextp(), _vcname__, this)}
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

Vt_funccov_bin_counts::Vt_funccov_bin_counts(const char* _vcname__)
    : Vt_funccov_bin_counts(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vt_funccov_bin_counts::~Vt_funccov_bin_counts() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vt_funccov_bin_counts___024root___eval_debug_assertions(Vt_funccov_bin_counts___024root* vlSelf);
#endif  // VL_DEBUG
void Vt_funccov_bin_counts___024root___eval_static(Vt_funccov_bin_counts___024root* vlSelf);
void Vt_funccov_bin_counts___024root___eval_initial(Vt_funccov_bin_counts___024root* vlSelf);
void Vt_funccov_bin_counts___024root___eval_settle(Vt_funccov_bin_counts___024root* vlSelf);
void Vt_funccov_bin_counts___024root___eval(Vt_funccov_bin_counts___024root* vlSelf);

void Vt_funccov_bin_counts::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vt_funccov_bin_counts::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vt_funccov_bin_counts___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vt_funccov_bin_counts___024root___eval_static(&(vlSymsp->TOP));
        Vt_funccov_bin_counts___024root___eval_initial(&(vlSymsp->TOP));
        Vt_funccov_bin_counts___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vt_funccov_bin_counts___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vt_funccov_bin_counts::eventsPending() { return false; }

uint64_t Vt_funccov_bin_counts::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vt_funccov_bin_counts::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vt_funccov_bin_counts___024root___eval_final(Vt_funccov_bin_counts___024root* vlSelf);

VL_ATTR_COLD void Vt_funccov_bin_counts::final() {
    Vt_funccov_bin_counts___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vt_funccov_bin_counts::hierName() const { return vlSymsp->name(); }
const char* Vt_funccov_bin_counts::modelName() const { return "Vt_funccov_bin_counts"; }
unsigned Vt_funccov_bin_counts::threads() const { return 1; }
void Vt_funccov_bin_counts::prepareClone() const { contextp()->prepareClone(); }
void Vt_funccov_bin_counts::atClone() const {
    contextp()->threadPoolpOnClone();
}
