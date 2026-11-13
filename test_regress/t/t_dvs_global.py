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

if not test.have_dv_solve:
    test.skip("Verilator not configured with dv-solve")

test.compile(verilator_flags2=['--binary', '--solver-dvs'])

test.execute()

# A read through a null handle fails the call, warned once per site
test.file_grep_count(
    test.run_log_filename,
    r'%Warning: dv-solve could not solve the constraints of the randomize\(\) call at'
    r' t/t_dvs_global.v:\d+: a constraint reads a variable through a null handle', 1)

test.passes()
