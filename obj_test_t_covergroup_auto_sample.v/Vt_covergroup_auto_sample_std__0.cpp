// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vt_covergroup_auto_sample.h for the primary calling header

#include "Vt_covergroup_auto_sample__pch.h"

std::string VL_TO_STRING(const Vt_covergroup_auto_sample_vl_covergroup_options_t__struct__0& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_auto_sample_std::VL_TO_STRING\n"); );
    // Body
    std::string out;
    out += "'{name:" + VL_TO_STRING(obj.__PVT__name);
    out += ", weight:" + VL_TO_STRING(obj.__PVT__weight);
    out += ", goal:" + VL_TO_STRING(obj.__PVT__goal);
    out += ", comment:" + VL_TO_STRING(obj.__PVT__comment);
    out += ", at_least:" + VL_TO_STRING(obj.__PVT__at_least);
    out += ", auto_bin_max:" + VL_TO_STRING(obj.__PVT__auto_bin_max);
    out += ", cross_num_print_missing:" + VL_TO_STRING(obj.__PVT__cross_num_print_missing);
    out += ", cross_retain_auto_bins:" + VL_TO_STRING(obj.__PVT__cross_retain_auto_bins);
    out += ", detect_overlap:" + VL_TO_STRING(obj.__PVT__detect_overlap);
    out += ", per_instance:" + VL_TO_STRING(obj.__PVT__per_instance);
    out += ", get_inst_coverage:" + VL_TO_STRING(obj.__PVT__get_inst_coverage);
    out += "}";
    return (out);
}

std::string VL_TO_STRING(const Vt_covergroup_auto_sample_vl_covergroup_type_options_t__struct__0& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vt_covergroup_auto_sample_std::VL_TO_STRING\n"); );
    // Body
    std::string out;
    out += "'{weight:" + VL_TO_STRING(obj.__PVT__weight);
    out += ", goal:" + VL_TO_STRING(obj.__PVT__goal);
    out += ", comment:" + VL_TO_STRING(obj.__PVT__comment);
    out += ", strobe:" + VL_TO_STRING(obj.__PVT__strobe);
    out += ", merge_instances:" + VL_TO_STRING(obj.__PVT__merge_instances);
    out += ", distribute_first:" + VL_TO_STRING(obj.__PVT__distribute_first);
    out += ", real_interval:" + VL_TO_STRING(obj.__PVT__real_interval);
    out += "}";
    return (out);
}
