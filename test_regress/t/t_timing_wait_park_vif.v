// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

interface clk_if(input logic clk);
  task automatic wait_clks(int n);
    repeat (n) @(posedge clk);
  endtask
endinterface
class Drv;
  virtual clk_if vif;
  task run(output int t); vif.wait_clks(10); t = int'($time); endtask
endclass
module t;
  logic clk = 0, clk2 = 0;
  always #5 clk = ~clk;
  always #7 clk2 = ~clk2;
  clk_if i0(clk);
  clk_if i1(clk);
  clk_if i2(clk2);
  initial begin
    Drv d0, d1, d2;
    int t0, t1, t2;
    d0 = new; d1 = new; d2 = new;
    d0.vif = i0; d1.vif = i1; d2.vif = i2;
    fork
      d0.run(t0);
      d1.run(t1);
      d2.run(t2);
    join
    $display("t0=%0d t1=%0d t2=%0d", t0, t1, t2);
    if (t0 != 95 || t1 != 95 || t2 != 133) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
