#!/usr/bin/env python3
# DESCRIPTION: Verilator: Verilog Test driver/expect definition
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of either the GNU Lesser General Public License Version 3
# or the Perl Artistic License Version 2.0.
# SPDX-FileCopyrightText: 2026 Matthew Ballance
# SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0

import vltest_bootstrap

test.scenarios('simulator')

test.compile(verilator_flags2=["--binary"])

test.execute()

if test.vlt_all:
    # Edge waits in the interface task use a per-instance trigger scheduler, not polling
    for filename in test.glob_some(test.obj_dir + "/" + test.vm_prefix + "*clk_if*.cpp"):
        test.file_grep_not(filename, r'evaluation\(')

test.passes()
