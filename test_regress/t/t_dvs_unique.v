// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// unique and solve-before with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Unique;
  rand bit [6:0] a;
  rand bit [6:0] b;
  rand bit [6:0] c;
  rand bit [6:0] d;
  constraint c_range {
    a < 4;
    b < 4;
    c < 4;
    d < 4;
  }
  constraint c_unique {unique {a, b, c, d};}
endclass

// Over more than the 16 variables dv-solve once took
class UniqueArr;
  rand bit [5:0] arr[32];
  constraint c {
    foreach (arr[i]) arr[i] < 40;
    unique {arr};
  }
endclass

class Order;
  rand bit s;
  rand bit [7:0] v;
  constraint c {
    s -> v == 0;
    solve s before v;
  }
endclass

module t;
  initial begin
    Unique u;
    UniqueArr ua;
    Order o;
    int ones;
    bit [39:0] seen;
    u = new;
    ua = new;
    o = new;
    repeat (50) begin
      `check(u.randomize() == 1);
      `check(u.a != u.b && u.a != u.c && u.a != u.d && u.b != u.c && u.b != u.d && u.c != u.d);
    end
    repeat (20) begin
      `check(ua.randomize() == 1);
      seen = '0;
      foreach (ua.arr[i]) begin
        `check(ua.arr[i] < 40 && !seen[ua.arr[i]]);
        seen[ua.arr[i]] = 1'b1;
      end
    end
    // Solved first, s is 1 half the time; otherwise it would be once in 257
    for (int i = 0; i < 400; ++i) begin
      `check(o.randomize() == 1);
      `check(!o.s || o.v == 0);
      ones += int'(o.s);
    end
    `check(ones > 120 && ones < 280);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
