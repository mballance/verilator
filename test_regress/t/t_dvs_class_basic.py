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

test.execute(all_run_flags=['+verilator+solver+file+' + test.obj_dir + '/solver.log'])

# The solver log has each problem solved, as SMT-LIB2
test.file_grep(test.obj_dir + '/solver.log', r'\(declare-const v0 \(_ BitVec 8\)\)')
test.file_grep(test.obj_dir + '/solver.log', r'; seed \d+, result 1')
# A solve across objects, and a problem with dynamic arrays, are logged without SMT-LIB2
test.file_grep(test.obj_dir + '/solver.log', r'; a problem of 2 objects')
test.file_grep(test.obj_dir + '/solver.log', r'; a problem with 1 arrays')

# There is no unsat core yet: the site and all its hard constraints are listed
test.file_grep(test.obj_dir + '/vlt_sim.log',
               r'%Warning-UNSATCONSTR: t/t_dvs_class_basic.v:\d+: Unsatisfied constraints in')
test.file_grep(
    test.obj_dir + '/vlt_sim.log',
    r"%Warning-UNSATCONSTR: t/t_dvs_class_basic.v:\d+: Unsatisfied constraint: 'y > 10;'")

# A log that cannot be written
test.execute(all_run_flags=['+verilator+solver+file+' + test.obj_dir + '/nodir/solver.log'],
             fails=True,
             expect=r"%Error: Can't write '.*/nodir/solver.log'")

test.passes()
