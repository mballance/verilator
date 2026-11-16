// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// std::randomize() of an enum gives one of its values (IEEE 1800-2023 18.4),
// also when no constraint names it

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

module t;
  function automatic bit legal(e_t e);
    return e == A || e == B || e == C;
  endfunction

  initial begin
    e_t e;
    f_t f;
    int seen;
    bit [3:0] x;
    seen = 0;
    repeat (50) begin
      `check(std::randomize(e) == 1);
      `check(legal(e));
      `check(std::randomize(e, x) with {x < 4;} == 1);
      `check(legal(e) && x < 4);
      `check(std::randomize(f) == 1);
      seen |= 1 << f;
    end
    `check(seen == 3);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
