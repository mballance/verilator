// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2024 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0

// Test large cross coverage (4-way, 256 bins)

module t;

   logic [3:0] a;
   logic [3:0] b;
   logic [3:0] c;
   logic [3:0] d;

   // Each coverpoint has 4 bins, 4-way cross = 4*4*4*4 = 256 bins
   covergroup cg;
      cp_a: coverpoint a {
         bins a0 = {[0:3]};
         bins a1 = {[4:7]};
         bins a2 = {[8:11]};
         bins a3 = {[12:15]};
      }

      cp_b: coverpoint b {
         bins b0 = {[0:3]};
         bins b1 = {[4:7]};
         bins b2 = {[8:11]};
         bins b3 = {[12:15]};
      }

      cp_c: coverpoint c {
         bins c0 = {[0:3]};
         bins c1 = {[4:7]};
         bins c2 = {[8:11]};
         bins c3 = {[12:15]};
      }

      cp_d: coverpoint d {
         bins d0 = {[0:3]};
         bins d1 = {[4:7]};
         bins d2 = {[8:11]};
         bins d3 = {[12:15]};
      }

      // 4-way cross: 4*4*4*4 = 256 cross bins
      cross_abcd: cross cp_a, cp_b, cp_c, cp_d;
   endgroup

   cg cg_inst = new;
   /* verilator lint_off IMPLICITSTATIC */
   real inst_cov;
   /* verilator lint_on IMPLICITSTATIC */

   initial begin
      int cyc;
      // Sample 20 different combinations
      for (cyc = 0; cyc < 20; cyc++) begin
         a = cyc[3:0];
         b = cyc[3:0] + 4;
         c = cyc[3:0] + 8;
         d = cyc[3:0] + 12;
         cg_inst.sample();
      end

      inst_cov = cg_inst.get_inst_coverage();
      $display("Coverage: %0.1f%%", inst_cov);

      if (inst_cov < 1.0 || inst_cov > 100.0) begin
         $display("%%Error: Invalid coverage value");
         $stop;
      end

      $write("*-* All Finished *-*\n");
      $finish;
   end

endmodule
