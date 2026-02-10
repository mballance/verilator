// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vt_cover_const_compare__pch.h"

//============================================================
// Constructors

Vt_cover_const_compare::Vt_cover_const_compare(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vt_cover_const_compare__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vt_cover_const_compare::Vt_cover_const_compare(const char* _vcname__)
    : Vt_cover_const_compare(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vt_cover_const_compare::~Vt_cover_const_compare() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vt_cover_const_compare___024root___eval_debug_assertions(Vt_cover_const_compare___024root* vlSelf);
#endif  // VL_DEBUG
void Vt_cover_const_compare___024root___eval_static(Vt_cover_const_compare___024root* vlSelf);
void Vt_cover_const_compare___024root___eval_initial(Vt_cover_const_compare___024root* vlSelf);
void Vt_cover_const_compare___024root___eval_settle(Vt_cover_const_compare___024root* vlSelf);
void Vt_cover_const_compare___024root___eval(Vt_cover_const_compare___024root* vlSelf);

void Vt_cover_const_compare::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vt_cover_const_compare::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vt_cover_const_compare___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vt_cover_const_compare___024root___eval_static(&(vlSymsp->TOP));
        Vt_cover_const_compare___024root___eval_initial(&(vlSymsp->TOP));
        Vt_cover_const_compare___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vt_cover_const_compare___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vt_cover_const_compare::eventsPending() { return false; }

uint64_t Vt_cover_const_compare::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vt_cover_const_compare::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vt_cover_const_compare___024root___eval_final(Vt_cover_const_compare___024root* vlSelf);

VL_ATTR_COLD void Vt_cover_const_compare::final() {
    Vt_cover_const_compare___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vt_cover_const_compare::hierName() const { return vlSymsp->name(); }
const char* Vt_cover_const_compare::modelName() const { return "Vt_cover_const_compare"; }
unsigned Vt_cover_const_compare::threads() const { return 1; }
void Vt_cover_const_compare::prepareClone() const { contextp()->prepareClone(); }
void Vt_cover_const_compare::atClone() const {
    contextp()->threadPoolpOnClone();
}
