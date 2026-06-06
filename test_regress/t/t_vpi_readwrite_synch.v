// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2024 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0

module t;
   reg  [7:0] a /*verilator public_flat_rw*/;
   reg  [7:0] b /*verilator public_flat_rw*/;
   reg  [7:0] c /*verilator public_flat_rw*/;
   wire [7:0] oa /*verilator public_flat_rd*/;
   wire [7:0] ob /*verilator public_flat_rd*/;
   wire [7:0] oc /*verilator public_flat_rd*/;

   initial begin
      a = 8'd0;
      b = 8'd0;
      c = 8'd0;
   end

   assign oa = a + 8'd1;
   assign ob = b + 8'd1;
   assign oc = c + 8'd1;
endmodule
