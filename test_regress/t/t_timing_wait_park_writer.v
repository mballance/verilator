// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// Non-local member written only in its class parks; written outside falls back

class Cnt;
  int n;          // not local: written only in this class -> parks
  int m;          // written from outside via c.m -> falls back to polling
  task inc(); n++; endtask
  task wait_n(int k); wait (n >= k); endtask
  task wait_m(int k); wait (m >= k); endtask
endclass
module t;
  initial begin
    automatic Cnt c = new;
    automatic int sum = 0;
    fork
      begin c.wait_n(100); $display("n=%0d", c.n); end
      begin c.wait_m(50); $display("m=%0d", c.m); end
      for (int i = 1; i <= 100; i++) begin #1; c.inc(); c.m = i; sum += i; end
    join
    $display("sum=%0d", sum);
    if (sum != 5050 || c.n != 100 || c.m != 100) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
