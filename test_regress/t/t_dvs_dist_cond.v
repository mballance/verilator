// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// 'dist' under a condition read before the call, in a block with constraint_mode(), and with
// values and weights read before the call, with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Cfg;
  bit enable_exception;
  int ratio = 30;
  int modes[$] = '{2, 5};
  rand bit fault;  // riscv-dv's exception_ratio_c
  rand bit [3:0] mode;  // boot_privileged_mode_dist_c
  rand bit sp;  // sp_c, a block turned off with constraint_mode()
  rand bit [3:0] two;  // Two dists: the first that applies is used
  rand bit [3:0] zero;  // All weights 0: no constraint
  rand bit [3:0] arr[];
  constraint c_fault {
    if (enable_exception) {
      fault dist {1 := ratio, 0 := 100 - ratio};
    }
  }
  constraint c_mode {
    if (modes.size() == 2) {
      mode dist {modes[0] := 6, modes[1] := 4};
    } else {
      mode dist {modes[0] := 1, modes[1] := 1, modes[2] := 1};
    }
  }
  constraint c_sp {sp dist {1 := 1, 0 := 9};}
  constraint c_two {
    if (ratio > 50) two dist {8 := 9, 9 := 1};
    two dist {[8 : 9] :/ 1};
  }
  constraint c_zero {zero dist {3 := ratio - 30};}
  constraint c_arr {
    arr.size() == 4;
    foreach (arr[i]) {
      if (i > 0) arr[i] dist {[0 : 1] :/ ratio, [14 : 15] :/ 100 - ratio};
    }
  }
endclass

module t;
  initial begin
    Cfg c;
    int faults, fives, sps, eights, zeros, lows;
    c = new;
    // Guard off: fault uniform; on: about ratio%
    for (int n = 0; n < 400; ++n) begin
      `check(c.randomize() == 1);
      if (c.fault) ++faults;
    end
    `check(faults > 150 && faults < 250);
    faults = 0;
    c.enable_exception = 1;
    for (int n = 0; n < 400; ++n) begin
      `check(c.randomize() == 1);
      if (c.fault) ++faults;
      `check(c.mode inside {2, 5});
      if (c.mode == 5) ++fives;
      if (c.sp) ++sps;
      `check(c.two inside {[8 : 9]});
      if (c.two == 8) ++eights;
      if (c.zero == 3) ++zeros;
      foreach (c.arr[i]) if (i > 0) begin
        `check(c.arr[i] inside {[0 : 1], [14 : 15]});
        if (c.arr[i] < 2) ++lows;
      end
    end
    `check(faults > 80 && faults < 160);  // 120 expected
    `check(fives > 120 && fives < 200);  // 160 expected
    `check(sps > 15 && sps < 70);  // 40 expected
    `check(eights > 150 && eights < 250);
    `check(zeros < 60);  // Any value: 3 not favored
    `check(lows > 250 && lows < 470);  // 360 expected of 1200
    // Values read on each call; the second dist applies
    c.modes = '{1, 7, 9};
    for (int n = 0; n < 20; ++n) begin
      `check(c.randomize() == 1);
      `check(c.mode inside {1, 7, 9});
    end
    // Another dist on the variable first, when its guard holds: its weights are used
    c.ratio = 60;
    eights = 0;
    for (int n = 0; n < 200; ++n) begin
      `check(c.randomize() == 1);
      `check(c.two inside {[8 : 9]});
      if (c.two == 8) ++eights;
    end
    `check(eights > 160);  // 180 expected
    // Weights that change the distribution between calls
    c.ratio = 100;
    for (int n = 0; n < 20; ++n) begin
      `check(c.randomize() == 1);
      `check(c.fault == 1);
    end
    // The block off
    c.ratio = 30;
    c.c_sp.constraint_mode(0);
    sps = 0;
    for (int n = 0; n < 200; ++n) begin
      `check(c.randomize() with {sp == 1 -> 1;} == 1);
      if (c.sp) ++sps;
    end
    `check(sps > 70 && sps < 130);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
