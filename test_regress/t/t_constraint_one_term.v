// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);

// Constraints over arrays of one element: SMT-LIB operators such as bvor and bvadd take at
// least two operands, so the solver must not see one applied to a single term
class C;
  rand bit [11:0] csr;
  bit [11:0] include_reg[$];
  rand bit [7:0] arr[];
  constraint c_inside {csr inside {include_reg};}
  constraint c_sum {arr.sum() == 8'd42;}
  function new();
    arr = new[1];
  endfunction
endclass

module t;
  initial begin
    automatic C c = new;
    c.include_reg.push_back(12'h340);
    repeat (5) begin
      `check(c.randomize() == 1);
      `check(c.csr == 12'h340 && c.arr.size() == 1 && c.arr[0] == 8'd42);
    end
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
