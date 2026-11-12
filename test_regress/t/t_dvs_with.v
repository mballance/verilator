// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// randomize() with {...} with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Item;
  rand bit [7:0] x;
  rand bit [7:0] y;
  bit [7:0] lim;
  constraint c {x < 100;}
endclass

class Driver;
  bit [7:0] floor;
  Item it;
  function new();
    it = new;
  endfunction
  // Inline constraints read the caller's members
  function int go();
    return it.randomize() with {
      x > floor;
      y == x + 1;
    };
  endfunction
endclass

class Base;
  bit [7:0] bound;
  rand bit [7:0] z;
endclass

class Derived extends Base;
  rand bit [7:0] a;
  // this.randomize() with: a state member and a random member, both inherited
  function int go();
    return this.randomize() with {
      a <= bound;
      z == a + 8'd1;
    };
  endfunction
endclass

class Caller;
  rand bit [7:0] r;
  rand bit [7:0] m[][];
  Item it;
  function new();
    it = new;
    m = new[2];
    m[1] = new[3];
  endfunction
  // Random members of the caller are state values of the call
  function int go();
    return it.randomize() with {
      x == m[1][2];
      y == (r ^ 8'h5a);
    };
  endfunction
  // An array of the caller in an 'inside' set: read before the call
  function int goInside();
    return it.randomize() with {x inside {m[1]};};
  endfunction
endclass

module t;
  initial begin
    Item it;
    Driver dr;
    bit [7:0] lo;
    bit [7:0] seen[bit [7:0]];
    it = new;
    dr = new;
    for (int i = 0; i < 50; ++i) begin
      lo = 8'(i);
      it.lim = 8'(i + 20);
      // Locals of the caller, members of the object, and a variable only the inline
      // constraints name
      `check(it.randomize() with {
        x >= lo;
        x < lim;
        y == 8'd7;
      } == 1);
      `check(it.x >= lo && it.x < it.lim && it.y == 7);
      dr.floor = 8'(i + 40);
      `check(dr.go() == 1);
      `check(dr.it.x > dr.floor && dr.it.x < 100 && dr.it.y == dr.it.x + 1);
      seen[it.x] = 1;
    end
    `check(seen.num() > 20);
    begin
      Derived d;
      d = new;
      for (int i = 0; i < 20; ++i) begin
        d.bound = 8'(i * 7);
        `check(d.go() == 1);
        `check(d.a <= d.bound && d.z == d.a + 8'd1 && d.bound == 8'(i * 7));
      end
    end
    begin
      Caller c;
      c = new;
      for (int i = 0; i < 20; ++i) begin
        c.r = 8'(i * 13);
        c.m[1][2] = 8'(i * 3);
        `check(c.go() == 1);
        `check(c.it.x == 8'(i * 3) && c.it.y == (8'(i * 13) ^ 8'h5a));
        `check(c.r == 8'(i * 13) && c.m[1][2] == 8'(i * 3));
      end
    end
    begin
      Caller c;
      bit [7:0] pool[$];
      c = new;
      c.m[1] = '{8'd5, 8'd200, 8'd77};
      pool = '{8'd3, 8'd150, 8'd99};
      repeat (20) begin
        `check(c.goInside() == 1);
        `check(c.it.x == 5 || c.it.x == 77);
        `check(it.randomize() with {x inside {pool}; !(y inside {pool}); y < 8'd5;} == 1);
        `check((it.x == 3 || it.x == 99) && it.y < 5 && it.y != 3);
      end
    end
    // The class constraints still hold
    `check(it.randomize() with {x > 150;} == 0);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
