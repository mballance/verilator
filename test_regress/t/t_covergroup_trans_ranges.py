#!/usr/bin/env python3
# DESCRIPTION: Verilator: Verilog Test driver/expect definition
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of either the GNU Lesser General Public License Version 3
# or the Perl Artistic License Version 2.0.
# SPDX-License-Identifier: CC0-1.0

import vltest_bootstrap

test.scenarios('vlt')

# Transition array bins are not yet supported - documented limitation
test.compile(
    verilator_flags2=["-Wno-IMPLICITSTATIC"],
    fails=test.vlt_all,
    expect=r'%Error-UNSUPPORTED:.*Array bins for transition bins not yet supported'
)

test.passes()
