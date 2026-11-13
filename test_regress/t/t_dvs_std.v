// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// std::randomize() with {...} with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

typedef struct {bit [6:0] x;} pair_t;

class Obj;
  bit [6:0] a;
  bit [6:0] arr[4];
  bit [6:0] dyn[];
  pair_t s;
  bit [6:0] lim;
  function new();
    dyn = new[3];
  endfunction
  // The arguments are members of this object; another member is a state value
  function int fill();
    return std::randomize(a, arr) with {
      a < lim;
      foreach (arr[i]) arr[i] == a + 7'(i);
    };
  endfunction
endclass

class Table;
  static bit [14:0] floor = 15'd1000;
  // From a static function: the generator is static too
  static function bit [14:0] pick();
    bit [14:0] v;
    if (std::randomize(v) with {v > floor; v < floor + 15'd20;} != 1) `stop;
    return v;
  endfunction
endclass

module t;
  // Module variables, several arguments, a state value read in the constraints
  initial begin
    bit [6:0] x;
    bit [14:0] y;
    bit [6:0] lim;
    int seen;
    lim = 7'd50;
    seen = 0;
    repeat (20) begin
      `check(std::randomize(x, y) with {x < lim; y == 15'(x) * 15'd3 + 15'd1;} == 1);
      `check(x < lim && y == 15'(x) * 15'd3 + 15'd1);
      seen |= 1 << (x % 32);
    end
    `check($countones(seen) > 4);  // The values vary
  end

  // Members, elements and struct members of an object
  initial begin
    Obj o;
    int i;
    o = new;
    i = 2;
    repeat (5) begin
      `check(std::randomize(o.a) with {o.a inside {[3 : 9]};} == 1);
      `check(o.a >= 3 && o.a <= 9);
      `check(std::randomize(o.arr[1]) with {o.arr[1] > 7'd100;} == 1);
      `check(o.arr[1] > 7'd100);
      `check(std::randomize(o.dyn[i]) with {o.dyn[i] inside {[20 : 22]};} == 1);
      `check(o.dyn[i] >= 20 && o.dyn[i] <= 22);
      `check(std::randomize(o.dyn[0]) with {o.dyn[0] == 7'd33;} == 1);
      `check(o.dyn[0] == 7'd33);
      `check(std::randomize(o.s.x) with {o.s.x == 7'd77;} == 1);
      `check(o.s.x == 7'd77);
      o.lim = 7'd10;
      `check(o.fill() == 1);
      `check(o.a < 10);
      foreach (o.arr[k]) `check(o.arr[k] == o.a + 7'(k));
    end
  end

  // Static function
  initial begin
    bit [14:0] v;
    v = Table::pick();
    `check(v > 15'd1000 && v < 15'd1020);
  end

  // A fixed-size array with foreach and unique, a random index into it
  initial begin
    bit [6:0] arr[5];
    bit [6:0] p;
    int i;
    repeat (10) begin
      `check(std::randomize(arr, p, i) with {
        unique {arr};
        foreach (arr[k]) arr[k] < 7'd8;
        i inside {[0 : 4]};
        p == arr[i];
      } == 1);
      `check(i >= 0 && i <= 4 && p == arr[i]);
      foreach (arr[k]) begin
        `check(arr[k] < 7'd8);
        foreach (arr[m]) if (k != m) `check(arr[k] != arr[m]);
      end
    end
  end

  // A queue with a random size, and a dynamic array with unique over more elements
  // than the dv-solve propagator takes (solved pairwise)
  initial begin
    bit [30:0] q[$];
    int d[];
    `check(std::randomize(q) with {q.size() inside {[2 : 6]}; foreach (q[k]) q[k] == 31'(k * 5);}
           == 1);
    `check(q.size() >= 2 && q.size() <= 6);
    foreach (q[k]) `check(q[k] == 31'(k * 5));
    d = new[20];
    `check(std::randomize(d) with {unique {d}; foreach (d[k]) d[k] inside {[1 : 25]};} == 1);
    foreach (d[k]) begin
      `check(d[k] >= 1 && d[k] <= 25);
      foreach (d[m]) if (k != m) `check(d[k] != d[m]);
    end
  end

  // 'inside' with an array as set member: read before the call, or an argument
  initial begin
    int q[$];
    int f[3];
    int x;
    bit [3:0] n;
    int arr[4];
    bit [7:0] d[];
    bit [7:0] v;
    int seen[int];
    q = '{3, 1000000, -7};
    f = '{11, 12, 13};
    repeat (20) begin
      `check(std::randomize(x, n, arr) with {
        x inside {q};
        !(int'(n) inside {q});
        foreach (arr[k]) arr[k] inside {f, q};
      } == 1);
      `check(x inside {q} && n != 3);
      foreach (arr[k]) `check(arr[k] inside {f, q});
      seen[x] = 1;
    end
    `check(seen.num() == 3);
    d = new[3];
    repeat (10) begin
      `check(std::randomize(d, v) with {foreach (d[k]) d[k] > 8'd200; v inside {d};} == 1);
      `check(v > 8'd200 && v inside {d});
    end
    // An empty array matches nothing
    q = {};
    x = 9;
    `check(std::randomize(x) with {x inside {q};} == 0);
    `check(x == 9);
  end

  // No solution: 0, and the arguments keep their values; no argument: a check only
  initial begin
    bit [6:0] x;
    int a;
    x = 7'd5;
    `check(std::randomize(x) with {x > 7'd10; x < 7'd3;} == 0);
    `check(x == 7'd5);
    a = 3;
    `check(std::randomize() with {a > 2;} == 1);
    `check(std::randomize() with {a > 5;} == 0);
  end

  initial begin
    #1;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
