// DESCRIPTION: Verilator: Gated vif triggers for members written via a vif MemberSel (<=)
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2026 by Wilson Snyder.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

interface ifc;
  int cnt;
endinterface

class Holder;
  virtual ifc vif;
endclass

class Driver;
  virtual ifc vif;
  Holder h;
  function new(virtual ifc v, virtual ifc w);
    vif = v;
    h = new;
    h.vif = w;
  endfunction
  task run();
    repeat (5) begin
      #1 vif.cnt <= vif.cnt + 1;
      #1 h.vif.cnt <= h.vif.cnt + 2;
    end
  endtask
endclass

class Monitor;
  virtual ifc vif;
  int changes;
  function new(virtual ifc v);
    vif = v;
  endfunction
  task watch();
    forever begin
      @(vif.cnt);
      changes++;
    end
  endtask
  task wait_for(int n);
    wait (vif.cnt == n);
  endtask
endclass

module t;
  ifc i0 ();
  ifc i1 ();
  Driver d;
  Monitor m0, m1;
  int mod_changes;

  // Production 5.052 also counts one extra change at time 0, so check >= 5
  always @(i1.cnt) mod_changes++;

  initial begin
    d = new(i0, i1);
    m0 = new(i0);
    m1 = new(i1);
    fork
      m0.watch();
      m1.watch();
    join_none
    fork
      d.run();
    join_none
    m0.wait_for(5);
    m1.wait_for(10);
    #2;
    if (m0.changes != 5 || m1.changes != 5 || mod_changes < 5) begin
      $display("%%Error: changes=%0d/%0d/%0d, expected 5/5/>=5", m0.changes, m1.changes,
               mod_changes);
      $stop;
    end
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
