// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2024 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#include "vpi_user.h"

#include <cstdlib>

// These require the above. Comment prevents clang-format moving them
#include "TestSimulator.h"
#include "TestVpi.h"

#include <cstdio>
#include <cstring>
#include <iostream>

static int got_readwrite = 0;
static int got_readonly = 0;
static int got_valuechange = 0;
static int got_afterdelay = 0;
static int got_rwchain = 0;

// Kept at file scope so the handle and value buffer outlive the cbValueChange
// registration (the callback references them for the life of the simulation).
static vpiHandle oc_handle = nullptr;
static s_vpi_value oc_value;

static int read_byte(const char* signal) {
    TestVpiHandle h = vpi_handle_by_name(const_cast<PLI_BYTE8*>(TestSimulator::rooted(signal)), 0);
    if (!h) return -1;
    s_vpi_value v;
    v.format = vpiIntVal;
    vpi_get_value(h, &v);
    return v.value.integer;
}

static void put_byte(const char* signal, int val, PLI_INT32 flags) {
    TestVpiHandle h = vpi_handle_by_name(const_cast<PLI_BYTE8*>(TestSimulator::rooted(signal)), 0);
    s_vpi_value v;
    v.format = vpiIntVal;
    v.value.integer = val;
    s_vpi_time t = {vpiSimTime, 0, 0, 0};  // Some simulators require non-null time
    vpi_put_value(h, &v, &t, flags);
}

static PLI_INT32 ValueChangeCb(p_cb_data) {
    // Fires from settle_value_callbacks() when oc changes.  On the first change
    // (oc: 0 -> 1 after the initial eval) issue a put that requires the active
    // region to re-converge: c = 99 -> oc = 100 on the next eval iteration.
    got_valuechange++;
    if (got_valuechange == 1) put_byte("c", 99, vpiNoDelay);
    return 0;
}

static PLI_INT32 AfterDelayCb(p_cb_data) {
    // Pending timed callback: requesting $finish here (rather than running out
    // of events) makes the main loop exit via its !gotFinish() guard.
    got_afterdelay++;
    vpi_control(vpiFinish, 0);
    return 0;
}

static PLI_INT32 RwChainCb(p_cb_data) {
    // Re-register another cbReadWriteSynch in the same time slot, without
    // writing, so the region loop re-iterates on hasCbs(cbReadWriteSynch) with
    // no pending re-eval.  Bounded so the slot still converges.
    got_rwchain++;
    if (got_rwchain < 3) {
        s_vpi_time t = {vpiSimTime, 0, 0, 0};
        s_cb_data cb{};
        cb.time = &t;
        cb.reason = cbReadWriteSynch;
        cb.cb_rtn = RwChainCb;
        CHECK_RESULT_NZ(vpi_register_cb(&cb));
    }
    return 0;
}

static PLI_INT32 ReadOnlyCb(p_cb_data) {
    // Puts done in cbReadWriteSynch are now fully settled through the
    // combinational logic, in this same time slot.  Count only on success, so
    // a failed check leaves the EndOfSim gate (and "All Finished") unreached.
    CHECK_RESULT(read_byte("oa"), 43);  // a = 42 via vpiNoDelay -> oa = 43
    CHECK_RESULT(read_byte("ob"), 100);  // b = 99 via vpiInertialDelay -> ob = 100
    CHECK_RESULT(read_byte("oc"), 100);  // c = 99 via cbValueChange put -> oc = 100
    got_readonly++;
    return 0;
}

static PLI_INT32 ReadWriteCb(p_cb_data) {
    // Before the puts, outputs reflect the initial inputs (a == b == 0).
    CHECK_RESULT(read_byte("oa"), 1);
    CHECK_RESULT(read_byte("ob"), 1);
    put_byte("a", 42, vpiNoDelay);
    put_byte("b", 99, vpiInertialDelay);
    got_readwrite++;
    return 0;
}

static PLI_INT32 EndOfSimCb(p_cb_data) {
    CHECK_RESULT(got_readwrite, 1);
    CHECK_RESULT(got_readonly, 1);
    CHECK_RESULT(got_valuechange, 2);  // oc: 0->1 (put c=99), then 1->100
    CHECK_RESULT(got_afterdelay, 1);
    CHECK_RESULT(got_rwchain, 3);  // fires, re-registers x2, then stops
    printf("*-* All Finished *-*\n");
    return 0;
}

static PLI_INT32 StartOfSimCb(p_cb_data) {
    s_vpi_time t = {vpiSimTime, 0, 0, 0};
    s_cb_data cb{};
    cb.time = &t;

    cb.reason = cbReadWriteSynch;
    cb.cb_rtn = ReadWriteCb;
    CHECK_RESULT_NZ(vpi_register_cb(&cb));

    cb.reason = cbReadWriteSynch;
    cb.cb_rtn = RwChainCb;
    CHECK_RESULT_NZ(vpi_register_cb(&cb));

    cb.reason = cbReadOnlySynch;
    cb.cb_rtn = ReadOnlyCb;
    CHECK_RESULT_NZ(vpi_register_cb(&cb));

    // cbValueChange on oc, to exercise settle_value_callbacks() convergence and
    // the active-region re-eval loop.  Handle/value kept at file scope.
    oc_handle = vpi_handle_by_name(const_cast<PLI_BYTE8*>(TestSimulator::rooted("oc")), 0);
    CHECK_RESULT_NZ(oc_handle);
    oc_value.format = vpiIntVal;
    cb.reason = cbValueChange;
    cb.cb_rtn = ValueChangeCb;
    cb.obj = oc_handle;
    cb.value = &oc_value;
    cb.time = &t;
    CHECK_RESULT_NZ(vpi_register_cb(&cb));
    cb.obj = nullptr;
    cb.value = nullptr;

    // cbAfterDelay pending in a future time slot, to exercise the time-advance
    // region and the gotFinish() loop exit.
    s_vpi_time td = {vpiSimTime, 0, 10, 0};
    cb.reason = cbAfterDelay;
    cb.cb_rtn = AfterDelayCb;
    cb.time = &td;
    CHECK_RESULT_NZ(vpi_register_cb(&cb));
    return 0;
}

static void VPIRegister() {
    s_cb_data cb{};
    cb.reason = cbStartOfSimulation;
    cb.cb_rtn = StartOfSimCb;
    vpi_register_cb(&cb);

    cb.reason = cbEndOfSimulation;
    cb.cb_rtn = EndOfSimCb;
    vpi_register_cb(&cb);
}

// simulator entry
void (*vlog_startup_routines[])() = {VPIRegister, 0};
