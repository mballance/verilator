// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Randomized enums hold only their values (IEEE 1800-2023 18.4) with --solver-dvs:
// std::randomize() arguments, with or without constraints naming them, and rand
// members, struct members and array elements of a class

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

typedef enum bit [7:0] {
  A = 1,
  B = 5,
  C = 200
} e_t;

typedef enum bit {
  F0,
  F1
} f_t;  // Every value of its width

typedef struct {
  rand e_t e;
  rand bit [3:0] x;
} s_t;

class Cls;
  rand e_t e;
  rand bit [3:0] x;
  rand s_t s;
  rand e_t arr[3];
  rand e_t dyn[];
  rand e_t q[$];
  rand s_t sarr[];
  constraint c {
    x < 8;
    dyn.size() == 3;
    q.size() == 3;
    sarr.size() == 2;
  }
endclass

module t;
  function automatic bit legal(e_t e);
    return e == A || e == B || e == C;
  endfunction

  initial begin
    e_t e;
    f_t f;
    int seen;
    bit [3:0] x;
    Cls o;
    o = new;
    seen = 0;
    repeat (50) begin
      `check(std::randomize(e) == 1);
      `check(legal(e));
      `check(std::randomize(e) with {e != A;} == 1);
      `check(legal(e) && e != A);
      `check(std::randomize(e, x) with {x < 4;} == 1);
      `check(legal(e) && x < 4);
      `check(std::randomize(f) == 1);
      seen |= 1 << f;
      `check(std::randomize(o.e) with {o.e != C;} == 1);
      `check(legal(o.e) && o.e != C);
      `check(o.randomize() == 1);
      `check(legal(o.e) && legal(o.s.e));
      foreach (o.arr[i]) `check(legal(o.arr[i]));
      foreach (o.dyn[i]) `check(legal(o.dyn[i]));
      foreach (o.q[i]) `check(legal(o.q[i]));
      foreach (o.sarr[i]) `check(legal(o.sarr[i].e));
      `check(o.randomize() with {e != B;} == 1);
      `check(legal(o.e) && o.e != B);
    end
    `check(seen == 3);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
