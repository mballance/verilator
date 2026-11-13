// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Weighted distributions with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Dist;
  rand bit [3:0] d;
  rand byte s;
  constraint c_d {d dist {0 := 1, [1 : 3] :/ 6, 15 := 3, 9 := 0};}
  constraint c_s {s dist {[-5 : -1] :/ 1, [1 : 5] :/ 1};}
endclass

module t;
  initial begin
    Dist o;
    int count[16];
    int neg;
    o = new;
    for (int i = 0; i < 2000; ++i) begin
      `check(o.randomize() == 1);
      `check(o.d inside {[0 : 3], 15});
      `check(o.s != 0 && o.s >= -5 && o.s <= 5);
      ++count[o.d];
      if (o.s < 0) ++neg;
    end
    // Expected 200, 1200 (400 each), 600; bounds are loose
    `check(count[0] > 100 && count[0] < 320);
    `check(count[1] + count[2] + count[3] > 1000 && count[1] + count[2] + count[3] < 1400);
    `check(count[1] > 250 && count[2] > 250 && count[3] > 250);
    `check(count[15] > 450 && count[15] < 750);
    `check(neg > 800 && neg < 1200);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
