// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// Killing a process parked on a semaphore wakes the next waiter

module t;
  semaphore s = new(0);
  process p1;
  int got2 = 0, got3 = 0;
  initial begin
    fork
      begin p1 = process::self(); s.get(1); $display("ERROR p1 got key"); end
      begin #1 s.get(1); got2 = 1; end
      begin #2 s.get(1); got3 = 1; end
    join_none
    #5 p1.kill();          // head waiter killed while parked
    #1 s.put(1);
    #1 s.put(1);
    #1 $display("got2=%0d got3=%0d", got2, got3);
    if (got2 != 1 || got3 != 1) $stop;
    if (s.try_get(1) != 0) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
