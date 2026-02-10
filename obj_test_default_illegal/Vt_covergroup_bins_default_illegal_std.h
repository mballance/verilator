// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vt_covergroup_bins_default_illegal.h for the primary calling header

#ifndef VERILATED_VT_COVERGROUP_BINS_DEFAULT_ILLEGAL_STD_H_
#define VERILATED_VT_COVERGROUP_BINS_DEFAULT_ILLEGAL_STD_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
#include "Vt_covergroup_bins_default_illegal_std.h"


class Vt_covergroup_bins_default_illegal__Syms;
struct Vt_covergroup_bins_default_illegal_vl_covergroup_options_t__struct__0 {
    std::string __PVT__name;
    IData/*31:0*/ __PVT__weight;
    IData/*31:0*/ __PVT__goal;
    std::string __PVT__comment;
    IData/*31:0*/ __PVT__at_least;
    IData/*31:0*/ __PVT__auto_bin_max;
    IData/*31:0*/ __PVT__cross_num_print_missing;
    CData/*0:0*/ __PVT__cross_retain_auto_bins;
    CData/*0:0*/ __PVT__detect_overlap;
    CData/*0:0*/ __PVT__per_instance;
    CData/*0:0*/ __PVT__get_inst_coverage;

    bool operator==(const Vt_covergroup_bins_default_illegal_vl_covergroup_options_t__struct__0& rhs) const {
        return __PVT__name == rhs.__PVT__name
            && __PVT__weight == rhs.__PVT__weight
            && __PVT__goal == rhs.__PVT__goal
            && __PVT__comment == rhs.__PVT__comment
            && __PVT__at_least == rhs.__PVT__at_least
            && __PVT__auto_bin_max == rhs.__PVT__auto_bin_max
            && __PVT__cross_num_print_missing == rhs.__PVT__cross_num_print_missing
            && __PVT__cross_retain_auto_bins == rhs.__PVT__cross_retain_auto_bins
            && __PVT__detect_overlap == rhs.__PVT__detect_overlap
            && __PVT__per_instance == rhs.__PVT__per_instance
            && __PVT__get_inst_coverage == rhs.__PVT__get_inst_coverage;
    }
    bool operator!=(const Vt_covergroup_bins_default_illegal_vl_covergroup_options_t__struct__0& rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const Vt_covergroup_bins_default_illegal_vl_covergroup_options_t__struct__0& rhs) const {
        return std::tie(__PVT__name, __PVT__weight, __PVT__goal, __PVT__comment, __PVT__at_least, __PVT__auto_bin_max, __PVT__cross_num_print_missing, __PVT__cross_retain_auto_bins, __PVT__detect_overlap, __PVT__per_instance, __PVT__get_inst_coverage)
            <  std::tie(rhs.__PVT__name, rhs.__PVT__weight, rhs.__PVT__goal, rhs.__PVT__comment, rhs.__PVT__at_least, rhs.__PVT__auto_bin_max, rhs.__PVT__cross_num_print_missing, rhs.__PVT__cross_retain_auto_bins, rhs.__PVT__detect_overlap, rhs.__PVT__per_instance, rhs.__PVT__get_inst_coverage);
    }
};
template <>
struct VlIsCustomStruct<Vt_covergroup_bins_default_illegal_vl_covergroup_options_t__struct__0> : public std::true_type {};
struct Vt_covergroup_bins_default_illegal_vl_covergroup_type_options_t__struct__0 {
    IData/*31:0*/ __PVT__weight;
    IData/*31:0*/ __PVT__goal;
    std::string __PVT__comment;
    CData/*0:0*/ __PVT__strobe;
    CData/*0:0*/ __PVT__merge_instances;
    CData/*0:0*/ __PVT__distribute_first;
    double __PVT__real_interval;

    bool operator==(const Vt_covergroup_bins_default_illegal_vl_covergroup_type_options_t__struct__0& rhs) const {
        return __PVT__weight == rhs.__PVT__weight
            && __PVT__goal == rhs.__PVT__goal
            && __PVT__comment == rhs.__PVT__comment
            && __PVT__strobe == rhs.__PVT__strobe
            && __PVT__merge_instances == rhs.__PVT__merge_instances
            && __PVT__distribute_first == rhs.__PVT__distribute_first
            && __PVT__real_interval == rhs.__PVT__real_interval;
    }
    bool operator!=(const Vt_covergroup_bins_default_illegal_vl_covergroup_type_options_t__struct__0& rhs) const {
        return !(*this == rhs);
    }

    bool operator<(const Vt_covergroup_bins_default_illegal_vl_covergroup_type_options_t__struct__0& rhs) const {
        return std::tie(__PVT__weight, __PVT__goal, __PVT__comment, __PVT__strobe, __PVT__merge_instances, __PVT__distribute_first, __PVT__real_interval)
            <  std::tie(rhs.__PVT__weight, rhs.__PVT__goal, rhs.__PVT__comment, rhs.__PVT__strobe, rhs.__PVT__merge_instances, rhs.__PVT__distribute_first, rhs.__PVT__real_interval);
    }
};
template <>
struct VlIsCustomStruct<Vt_covergroup_bins_default_illegal_vl_covergroup_type_options_t__struct__0> : public std::true_type {};

class alignas(VL_CACHE_LINE_BYTES) Vt_covergroup_bins_default_illegal_std final {
  public:

    // INTERNAL VARIABLES
    Vt_covergroup_bins_default_illegal__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vt_covergroup_bins_default_illegal_std();
    ~Vt_covergroup_bins_default_illegal_std();
    void ctor(Vt_covergroup_bins_default_illegal__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vt_covergroup_bins_default_illegal_std);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};

std::string VL_TO_STRING(const Vt_covergroup_bins_default_illegal_vl_covergroup_options_t__struct__0& obj);
std::string VL_TO_STRING(const Vt_covergroup_bins_default_illegal_vl_covergroup_type_options_t__struct__0& obj);

#endif  // guard
