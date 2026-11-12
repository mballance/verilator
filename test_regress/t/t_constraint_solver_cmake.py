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
test.top_filename = "t/t_constraint.v"

if not test.have_solver:
    test.skip("No constraint solver installed")

# $VERILATOR_SOLVER and $VERILATOR_RAND_SAMPLER when Verilator runs are
# compiled into a CMake-built model as its defaults
test.setenv('VERILATOR_SOLVER', 'someimaginarysolver --in')
test.setenv('VERILATOR_RAND_SAMPLER', 'solver')

test.compile(verilator_make_gmake=False, verilator_make_cmake=True)

os.environ.pop('VERILATOR_SOLVER', None)
os.environ.pop('VERILATOR_RAND_SAMPLER', None)
log = test.obj_dir + "/solver.log"
test.execute(all_run_flags=['+verilator+solver+file+' + log], fails=True)
test.file_grep(test.run_log_filename, r'Tried: \$ someimaginarysolver --in')
test.file_grep(log, r'; sampler: solver')

test.passes()
