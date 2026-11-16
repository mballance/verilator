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

if not test.have_solver:
    test.skip("No constraint solver installed")

test.compile()

log = test.obj_dir + "/solver.log"
test.execute(all_run_flags=['+verilator+solver+file+' + log])
# The operator's identity leads its terms, so it has two operands where there is one term
test.file_grep(log, r'\(bvor #b0 ')
test.file_grep(log, r'\(bvadd #x00 ')

test.passes()
