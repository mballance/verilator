// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// Test cross referencing an unknown coverpoint (should emit COVERIGN warning)

module t;
   logic [1:0] addr;
   logic clk;

   // Cross references 'cp_nonexistent' which is not a defined coverpoint
   covergroup cg;
      cp_addr: coverpoint addr;
      bad_cross: cross cp_addr, cp_nonexistent;
   endgroup

   cg cg_inst = new;

   initial begin
      clk = 0;
      addr = 0;
      #10;
      $write("*-* All Finished *-*\n");
      $finish;
   end

   always #5 clk = ~clk;

endmodule
