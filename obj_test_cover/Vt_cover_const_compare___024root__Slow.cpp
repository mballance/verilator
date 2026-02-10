// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_cover_const_compare.h for the primary calling header

#include "Vt_cover_const_compare__pch.h"
#include "Vt_cover_const_compare__Syms.h"
#include "Vt_cover_const_compare___024root.h"

void Vt_cover_const_compare___024root___ctor_var_reset(Vt_cover_const_compare___024root* vlSelf);

Vt_cover_const_compare___024root::Vt_cover_const_compare___024root(Vt_cover_const_compare__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vt_cover_const_compare___024root___ctor_var_reset(this);
}

void Vt_cover_const_compare___024root___configure_coverage(Vt_cover_const_compare___024root* vlSelf, bool first);

void Vt_cover_const_compare___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
    Vt_cover_const_compare___024root___configure_coverage(this, first);
}

Vt_cover_const_compare___024root::~Vt_cover_const_compare___024root() {
}

// Coverage
void Vt_cover_const_compare___024root::__vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp, const char* linescovp) {
    uint32_t* count32p = countp;
    static uint32_t fake_zero_count = 0;
    std::string fullhier = std::string{VerilatedModule::name()} + hierp;
    if (!fullhier.empty() && fullhier[0] == '.') fullhier = fullhier.substr(1);
    if (!enable) count32p = &fake_zero_count;
    *count32p = 0;
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), VerilatedModule::name(), count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
        "hier",fullhier,  "page",pagep,  "comment",commentp,  (linescovp[0] ? "linescov" : ""), linescovp);
}

// Toggle Coverage
void Vt_cover_const_compare___024root::__vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp) {
    int step = (end >= begin) ? 1 : -1;
    for (int i = begin; i != end + step; i += step) {
        for (int j = 0; j < 2; j++) {
            uint32_t* count32p = countp;
            static uint32_t fake_zero_count = 0;
            std::string fullhier = std::string{VerilatedModule::name()} + hierp;
            if (!fullhier.empty() && fullhier[0] == '.') fullhier = fullhier.substr(1);
            std::string commentWithIndex = commentp;
            if (ranged) commentWithIndex += '[' + std::to_string(i) + ']';
            commentWithIndex += j ? ":0->1" : ":1->0";
            if (!enable) count32p = &fake_zero_count;
            *count32p = 0;
            VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), VerilatedModule::name(), count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
                "hier",fullhier,  "page",pagep,  "comment",commentWithIndex.c_str(),  "", "");
            ++countp;
        }
    }
}
