// DESCRIPTION: Verilator: Verilog Test module - Edge case: multiple instances
// This file ONLY is placed into the Public Domain, for any use, without warranty.
// SPDX-License-Identifier: CC0-1.0

// Test: Multiple instances of same covergroup type
// Expected: Each instance tracks coverage independently

module t (/*AUTOARG*/
   // Inputs
   clk
   );
   input clk;

   logic [2:0] value1, value2, value3;
   
   covergroup cg;
      cp: coverpoint value1 {
         bins low = {[0:3]};
         bins high = {[4:7]};
      }
   endgroup

   // Create three independent instances
   cg cg_inst1 = new;
   cg cg_inst2 = new;
   cg cg_inst3 = new;

   int cyc = 0;

   always @(posedge clk) begin
      cyc <= cyc + 1;
      
      case (cyc)
        0: begin
           value1 <= 1;  // low bin for inst1
           value2 <= 5;  // high bin for inst2
           value3 <= 1;  // low bin for inst3
        end
        1: begin
           value1 <= 6;  // high bin for inst1 -> 100%
           value2 <= 2;  // low bin for inst2 -> 100%
           value3 <= 3;  // low bin for inst3 (still low)
        end
        2: begin
           begin
              real cov1, cov2, cov3;
              cov1 = cg_inst1.get_inst_coverage();
              cov2 = cg_inst2.get_inst_coverage();
              cov3 = cg_inst3.get_inst_coverage();
              
              $display("Instance 1 coverage: %f%%", cov1);
              $display("Instance 2 coverage: %f%%", cov2);
              $display("Instance 3 coverage: %f%%", cov3);
              
              // inst1 and inst2 should be 100%, inst3 should be 50%
              if (cov1 >= 99.0 && cov2 >= 99.0 && cov3 >= 45.0 && cov3 <= 55.0) begin
                 $write("*-* All Finished *-*\n");
                 $finish;
              end else begin
                 $display("ERROR: Coverage mismatch");
                 $display("  Expected: inst1=100%%, inst2=100%%, inst3=50%%");
                 $display("  Got: inst1=%f%%, inst2=%f%%, inst3=%f%%", cov1, cov2, cov3);
                 $stop;
              end
           end
        end
      endcase
      
      // Each instance samples its own value
      // Note: All instances use value1 in this test (same coverpoint expression)
      // In real usage, each would sample different variables
      cg_inst1.sample();
      cg_inst2.sample();
      cg_inst3.sample();
      
      if (cyc > 10) begin
         $display("ERROR: Test timed out");
         $stop;
      end
   end
endmodule
