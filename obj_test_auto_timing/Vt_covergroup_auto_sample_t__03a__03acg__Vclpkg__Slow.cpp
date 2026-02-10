// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_auto_sample.h for the primary calling header

#include "Vt_covergroup_auto_sample__pch.h"

void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___ctor_var_reset(Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg* vlSelf);

Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg::Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg() = default;
Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg::~Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg() = default;

void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg::ctor(Vt_covergroup_auto_sample__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___ctor_var_reset(this);
}

void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___configure_coverage(Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg* vlSelf, bool first);

void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
    Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg___configure_coverage(this, first);
}

void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

// Coverage
void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg::__vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp, const char* linescovp) {
    uint32_t* count32p = countp;
    static uint32_t fake_zero_count = 0;
    std::string fullhier = std::string{vlNamep} + hierp;
    if (!fullhier.empty() && fullhier[0] == '.') fullhier = fullhier.substr(1);
    if (!enable) count32p = &fake_zero_count;
    *count32p = 0;
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), vlNamep, count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
        "hier",fullhier,  "page",pagep,  "comment",commentp,  (linescovp[0] ? "linescov" : ""), linescovp);
}

// Toggle Coverage
void Vt_covergroup_auto_sample_t__03a__03acg__Vclpkg::__vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp) {
    int step = (end >= begin) ? 1 : -1;
    for (int i = begin; i != end + step; i += step) {
        for (int j = 0; j < 2; j++) {
            uint32_t* count32p = countp;
            static uint32_t fake_zero_count = 0;
            std::string fullhier = std::string{vlNamep} + hierp;
            if (!fullhier.empty() && fullhier[0] == '.') fullhier = fullhier.substr(1);
            std::string commentWithIndex = commentp;
            if (ranged) commentWithIndex += '[' + std::to_string(i) + ']';
            commentWithIndex += j ? ":0->1" : ":1->0";
            if (!enable) count32p = &fake_zero_count;
            *count32p = 0;
            VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), vlNamep, count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
                "hier",fullhier,  "page",pagep,  "comment",commentWithIndex.c_str(),  "", "");
            ++countp;
        }
    }
}
