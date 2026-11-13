// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// randomize(null) checks the current values with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Check;
  rand bit [7:0] x;
  bit [7:0] lim;
  constraint c_lim {x < lim;}
  constraint c_dist {x dist {[0 : 9] :/ 1, 20 := 1};}
endclass

module t;
  initial begin
    Check c;
    c = new;
    c.lim = 15;
    c.x = 5;
    `check(c.randomize(null) == 1);
    `check(c.x == 5);
    // Outside the limit, then outside the distribution's values
    c.x = 16;
    `check(c.randomize(null) == 0);
    `check(c.x == 16);
    c.x = 12;
    `check(c.randomize(null) == 0);
    // A disabled constraint is not checked
    c.c_lim.constraint_mode(0);
    `check(c.randomize(null) == 0);
    c.x = 20;
    `check(c.randomize(null) == 1);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
