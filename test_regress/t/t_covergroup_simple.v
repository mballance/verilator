// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// Test basic covergroup with simple coverpoint

module t;
   logic [7:0] addr;
   logic cmd;

   // Simple covergroup with two coverpoints
   covergroup cg @(posedge clk);
      cp_addr: coverpoint addr {
         bins low = {[0:127]};
         bins high = {[128:255]};
      }
      cp_cmd: coverpoint cmd {
         bins read = {0};
         bins write = {1};
      }
   endgroup

   cg cg_inst = new;

   logic clk = 0;
   always #5 clk = ~clk;

   initial begin
      // Sample some values
      addr = 10; cmd = 0;
      @(posedge clk);
      
      addr = 200; cmd = 1;
      @(posedge clk);
      
      addr = 50; cmd = 0;
      @(posedge clk);
      
      $display("Coverage: %0.1f%%", cg_inst.get_coverage());
      
      $write("*-* All Finished *-*\n");
      $finish;
   end

endmodule
