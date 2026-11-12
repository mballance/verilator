// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// constraint_mode() with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Mode;
  rand bit [7:0] x;
  constraint c_lo {x < 10;}
  constraint c_hi {x > 200;}
  static constraint c_odd {x[0] == 1'b1;}
endclass

module t;
  initial begin
    Mode m;
    Mode other;
    bit seen_mid;
    bit seen_even;
    m = new;
    other = new;
    m.c_hi.constraint_mode(0);
    repeat (20) begin
      `check(m.randomize() == 1);
      `check(m.x < 10 && m.x[0]);
    end
    m.c_hi.constraint_mode(1);
    m.c_lo.constraint_mode(0);
    repeat (20) begin
      `check(m.randomize() == 1);
      `check(m.x > 200 && m.x[0]);
    end
    // Both enabled: no solution, and x is unchanged
    m.x = 8'd3;
    m.c_lo.constraint_mode(1);
    `check(m.randomize() == 0);
    `check(m.x == 3);
    // A static constraint's mode is shared by all objects
    m.c_lo.constraint_mode(0);
    m.c_hi.constraint_mode(0);
    other.c_odd.constraint_mode(0);
    repeat (100) begin
      `check(m.randomize() == 1);
      if (m.x >= 10 && m.x <= 200) seen_mid = 1;
      if (!m.x[0]) seen_even = 1;
    end
    `check(seen_mid && seen_even);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
