// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// verilog_format: off
`define stop $stop
`define checkd(gotv,expv) do if ((gotv) !== (expv)) begin $write("%%Error: %s:%0d:  got=%0d exp=%0d\n", `__FILE__,`__LINE__, (gotv), (expv)); `stop; end while(0);
// verilog_format: on

class Packet;
  rand bit [7:0] x;
  constraint c {
    x > 10;
    x < 20;
  }
endclass

class Ops;
  rand bit [4:0] a;
  rand bit [4:0] b;
  rand bit [39:0] q;
  constraint c {
    q[39:32] == 8'hab;
    a >= 3;
    a <= 9;
    a != b;
    b == 5'd7;
  }
endclass

class Unsat;
  rand bit [6:0] y;
  constraint c {
    y < 5;
    y > 10;
  }
endclass

// A signed comparison of a sign-extended value, on dv-solve's CDCL engine, which soft
// constraints need
class SoftSigned;
  rand byte b;
  constraint c {
    b > -3;
    soft b == 1;
  }
endclass

// dv-solve's CDCL engine, which soft constraints need, inverts this hash: the hard
// constraints have one solution, so the soft one is dropped
class HashInverse;
  rand bit [63:0] a;
  rand bit [63:0] t;
  constraint c {
    t == a * 64'h9e3779b97f4a7c15;
    (t ^ (t >> 31)) * 64'hbf58476d1ce4e5b9 == 64'hf3f518da3c22a1f3;  // a == 'h123456789
    soft a == 3;
  }
endclass

class NoConstraints;
  rand bit [6:0] z;
endclass

// No random variables, and a block with no constraints
class EmptyBlock;
  int a;
  constraint e {}
endclass

// A dynamic array of an enum: each element is one of its values
typedef enum bit [1:0] {
  E_A,
  E_B,
  E_C
} e_t;

class EnumArray;
  rand e_t q[];
  constraint c {q.size() == 8;}
endclass

// A rand class handle: the solve spans this object and that of h
class Holder;
  rand EnumArray h;
  rand bit [7:0] x;
  constraint c {x < 5;}
  function new();
    h = new;
  endfunction
endclass

module t;
  // Sum of the values of 'iters' randomizations of an object seeded with 'seed'
  function automatic int unsigned run(int seed, int iters);
    Packet p = new;
    bit seen[bit [7:0]];
    int unsigned sum = 0;
    p.srandom(seed);
    for (int i = 0; i < iters; ++i) begin
      int ok = p.randomize();
      `checkd(ok, 1);
      if (p.x <= 10 || p.x >= 20) begin
        $write("%%Error: x=%0d out of range\n", p.x);
        `stop;
      end
      seen[p.x] = 1;
      sum = sum * 31 + 32'(p.x);
    end
    // 200 draws over 9 values: all are seen
    if (iters == 200) `checkd(seen.num(), 9);
    return sum;
  endfunction

  initial begin
    // The same seed gives the same values; another seed gives others
    `checkd(run(1, 200), run(1, 200));
    if (run(1, 20) == run(2, 20)) begin
      $write("%%Error: seeds 1 and 2 gave the same values\n");
      `stop;
    end
  end

  initial begin
    Ops o;
    o = new;
    for (int i = 0; i < 100; ++i) begin
      automatic int ok = o.randomize();
      `checkd(ok, 1);
      `checkd(o.b, 7);
      `checkd(o.q[39:32], 8'hab);
      if (o.a < 3 || o.a > 9 || o.a == 7) begin
        $write("%%Error: a=%0d out of range\n", o.a);
        `stop;
      end
    end
  end

  initial begin
    Unsat u;
    NoConstraints n;
    SoftSigned s;
    HashInverse g;
    int ok;
    u = new;
    n = new;
    s = new;
    g = new;
    ok = u.randomize();
    `checkd(ok, 0);
    ok = s.randomize();
    `checkd(ok, 1);
    `checkd(s.b, 1);
    ok = g.randomize();
    `checkd(ok, 1);
    `checkd(g.a, 64'h123456789);
    ok = n.randomize();
    `checkd(ok, 1);
    begin
      EmptyBlock eb;
      Holder h;
      eb = new;
      ok = eb.randomize();
      `checkd(ok, 1);
      h = new;
      // Solved across the two objects, then the array's object alone
      ok = h.randomize();
      `checkd(ok, 1);
      `checkd(h.h.q.size(), 8);
      foreach (h.h.q[i]) if (h.h.q[i] == 3) `stop;
      ok = h.h.randomize();
      `checkd(ok, 1);
      `checkd(h.h.q.size(), 8);
      foreach (h.h.q[i]) if (h.h.q[i] == 3) `stop;
    end
    #1;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
