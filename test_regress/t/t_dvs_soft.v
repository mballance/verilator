// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Soft constraints and their priorities with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Base;
  rand bit [7:0] x;
  rand bit [7:0] y;
  rand bit [7:0] z;
  constraint c_soft {
    soft x == 5;
    soft y == 1;
    soft y == 2;
    soft z == 50;
  }
endclass

class Derived extends Base;
  constraint c_derived {
    soft x == 6;
    z > 100;
  }
endclass

class Guarded;
  rand bit [7:0] a;
  rand bit [7:0] b;
  constraint c {
    a < 2;
    if (a == 1) soft b == 77;
    else soft b == 88;
  }
endclass

class Limited;
  rand bit [7:0] len;
  bit [7:0] m;
  constraint c {
    len <= m;
    soft len == 64;
  }
endclass

module t;
  initial begin
    Base bs;
    Derived d;
    Guarded g;
    Limited l;
    bs = new;
    d = new;
    g = new;
    l = new;
    repeat (20) begin
      // A soft constraint holds unless it conflicts
      `check(bs.randomize() == 1);
      `check(bs.x == 5 && bs.z == 50);
      // The later of two conflicting soft constraints wins
      `check(bs.y == 2);
      // A derived class's soft constraint beats its base's; a hard constraint beats both
      `check(d.randomize() == 1);
      `check(d.x == 6 && d.y == 2 && d.z > 100);
      // An inline soft constraint beats the class's
      `check(d.randomize() with { soft x == 9; } == 1);
      `check(d.x == 9);
      `check(g.randomize() == 1);
      `check(g.b == (g.a == 1 ? 77 : 88));
      // A soft constraint gives way to a constraint on a state variable
      l.m = 32;
      `check(l.randomize() == 1);
      `check(l.len <= 32);
      l.m = 100;
      `check(l.randomize() == 1);
      `check(l.len == 64);
    end
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
