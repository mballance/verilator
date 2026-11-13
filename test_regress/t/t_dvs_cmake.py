#!/usr/bin/env python3
# DESCRIPTION: Verilator: Verilog Test driver/expect definition
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of either the GNU Lesser General Public License Version 3
# or the Perl Artistic License Version 2.0.
# SPDX-FileCopyrightText: 2026 Wilson Snyder
# SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0

import vltest_bootstrap

test.scenarios('vlt')
test.top_filename = "t/t_dvs_soft.v"

if not test.have_dv_solve:
    test.skip("Verilator not configured with dv-solve")

# A CMake-built model gets the dv-solve flags from the manifest, with
# $(DV_SOLVE_ROOT) expanded
test.compile(verilator_flags2=['--solver-dvs'],
             verilator_make_gmake=False,
             verilator_make_cmake=True)

test.execute()

test.passes()
