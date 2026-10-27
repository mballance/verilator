// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// wait() on class-local members parks the process instead of polling

class Box;
  local int m_q[$];
  local int m_n;
  task put(int v);
    m_q.push_back(v);
    m_n = m_n + 1;
  endtask
  task get(output int v);
    wait (m_q.size() > 0);
    v = m_q.pop_front();
  endtask
  task waitn(int n);
    wait (m_n >= n);
  endtask
endclass
module t;
  Box b = new;
  int sum = 0;
  initial begin
    fork
      begin int v; repeat (100) begin b.get(v); sum += v; end end
      begin b.waitn(100); $display("waitn done at %0t", $time); end
      begin for (int i = 1; i <= 100; i++) begin #1 b.put(i); end end
    join
    $display("sum=%0d", sum);
    if (sum != 5050) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
