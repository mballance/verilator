// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// @(arr[i].ev) / @(assoc[k].ev) park, as UVM's @(m_events[obj].all_dropped)

class Ev; event e; endclass
class Obj;
  Ev m_ev[Obj];
  Ev arr[2];
  int n = 0;
  task waiter(Obj o);
    repeat (3) begin @(m_ev[o].e); n++; end
  endtask
  task waiter2();
    repeat (2) begin @(arr[1].e); n += 10; end
  endtask
  function void fire(Obj o); ->m_ev[o].e; endfunction
endclass
module t;
  initial begin
    automatic Obj c = new;
    automatic Obj k = new;
    c.m_ev[k] = new; c.arr[1] = new;
    fork c.waiter(k); c.waiter2(); join_none
    repeat (3) begin #1 c.fire(k); ->c.arr[1].e; end
    #1 if (c.n != 23) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
