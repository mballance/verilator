#!/usr/bin/env python3
# DESCRIPTION: Verilator: Verilog Test driver/expect definition
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of either the GNU Lesser General Public License Version 3
# or the Perl Artistic License Version 2.0.
# SPDX-FileCopyrightText: 2026 Antmicro
# SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0

import vltest_bootstrap

test.scenarios('vlt')

test.compile(verilator_flags2=['--coverage'])

test.execute()

# Check that coverage database contains functional coverage entries
# Format: C 'tfunccovpage...binlow...hcg.cp.low' count
test.file_grep(test.coverage_filename, r'tfunccov')
test.file_grep(test.coverage_filename, r'binlow')
test.file_grep(test.coverage_filename, r'binhigh')
test.file_grep(test.coverage_filename, r'hcg\.cp\.low')
test.file_grep(test.coverage_filename, r'hcg\.cp\.high')

# Verify both bins have non-zero counts (they were both sampled)
test.file_grep(test.coverage_filename, r'.*binlow.*\' [1-9]')
test.file_grep(test.coverage_filename, r'.*binhigh.*\' [1-9]')

test.passes()
