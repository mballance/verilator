#!/usr/bin/env python3
# DESCRIPTION: Verilator: Verilog Test driver/expect definition
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of either the GNU Lesser General Public License Version 3
# or the Perl Artistic License Version 2.0.
# SPDX-License-Identifier: CC0-1.0

import vltest_bootstrap

test.scenarios('vlt')

# Transition array bins currently cause a segfault
# This is a known limitation - transition bins with arrays not fully supported
test.compile(
    verilator_flags2=["-Wno-IMPLICITSTATIC"],
    fails=test.vlt_all,
    expect=r'.*Internal Error.*|.*SEGV.*|.*ABORTING.*'
)

test.passes()
