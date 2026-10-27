// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// std::mailbox and std::semaphore waits park

module t;
  mailbox #(int) mb = new(4);
  semaphore sm = new(0);
  int sum = 0;
  initial begin
    fork
      begin for (int i = 1; i <= 100; i++) mb.put(i); end
      begin int v; for (int i = 1; i <= 100; i++) begin mb.get(v); sum += v; end sm.put(1); end
    join_none
    sm.get(1);
    $display("sum=%0d", sum);
    if (sum != 5050) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
