// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: dv-solve constraint solver back-end
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#ifndef VERILATOR_V3SOLVERDVS_H_
#define VERILATOR_V3SOLVERDVS_H_

#include "config_build.h"
#include "verilatedos.h"

class V3SolverBackend;

// Create the dv-solve back-end; only built when configured --with-dv-solve
V3SolverBackend* newV3SolverDvs() VL_MT_DISABLED;
// Problem format version of the dv-solve back-end, 0 if 'verilator_bin' is built without it
uint32_t dvSolveFormatVersion() VL_PURE;

#endif  // Guard
