// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty.
// SPDX-License-Identifier: CC0-1.0

// Test: Covergroup with clocking event using INTERNALLY GENERATED clock
// Status: DOES NOT WORK - Verilator does not auto-sample when clk is internal
// 
// This test documents a known limitation:
//   - Clocking events work for module input clocks
//   - Clocking events do NOT work for internally generated clocks
//
// To make this test pass, either:
//   1. Implement auto-sampling for internal clock signals (proper fix)
//   2. Convert to explicit .sample() calls (workaround)

module t;
   logic clk = 0;
   always #5 clk = ~clk;
   
   logic [1:0] data;
   
   /* verilator lint_off UNSIGNED */
   covergroup cg @(posedge clk);
      cp: coverpoint data {
         bins val0 = {2'b00};
         bins val1 = {2'b01};
         bins val2 = {2'b10};
         bins val3 = {2'b11};
      }
   endgroup
   /* verilator lint_on UNSIGNED */
   
   cg cg_inst = new;
   
   initial begin
      // Cycle 0
      data = 2'b00;
      @(posedge clk);
      
      // Cycle 1
      data = 2'b01;
      @(posedge clk);
      
      // Cycle 2
      data = 2'b10;
      @(posedge clk);
      
      // Cycle 3
      data = 2'b11;
      @(posedge clk);
      
      // Check coverage
      #1; // Small delay to ensure last sample completes
      
      begin
         real cov = cg_inst.get_inst_coverage();
         $display("Coverage: %0.1f%%", cov);
         
         // Should have hit all 4 bins = 100%
         if (cov >= 99.0) begin
            $write("*-* All Finished *-*\n");
            $finish;
         end else begin
            $display("ERROR: Expected 100%% coverage, got %f%%", cov);
            $display("ERROR: This is a known limitation - auto-sampling doesn't work with internal clocks");
            $stop;
         end
      end
   end

endmodule
