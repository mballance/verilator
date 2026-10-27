// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// Member written by a function-call result in a derived class wakes waiters

class Item; int id; function int get_id(); return id; endfunction endclass
class Base;
  protected int m_id;
  task wait_for(int sid);
    m_id = -1;
    wait (m_id == sid);
  endtask
endclass
class Mid #(type T = int) extends Base; endclass
class Seqr #(type T = Item) extends Mid #(T);
  task done(T t);
    #1;
    m_id = t.get_id();
  endtask
endclass
class Push #(type T = Item) extends Mid #(T);
  T q[$];
  task run();
    fork
      forever begin
        T t;
        wait (q.size() > 0);
        t = q.pop_front();
        m_id = t.get_id();
      end
    join_none
  endtask
endclass
module t;
  Push #(Item) p = new;
  Seqr #(Item) s = new;
  initial begin
    automatic Item it = new; it.id = 7;
    fork s.wait_for(7); s.done(it); join
    $display("ok at %0t", $time);
    if ($time != 1) $stop;
    $write("*-* All Finished *-*\n"); $finish;
  end
endmodule
