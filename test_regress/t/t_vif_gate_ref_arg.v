// DESCRIPTION: Verilator: Vif trigger stays ungated for a member passed as ref to a task
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2026 by Wilson Snyder.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

interface ifc;
  int cnt;
endinterface

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

class Driver;
  static task bump(ref int x);
    #1 x = x + 1;
  endtask
  static task run(virtual ifc vif);
    repeat (5) bump(vif.cnt);
  endtask
endclass

module t;
  ifc i0 ();
  Monitor m0;
  task automatic drive();
    Driver::run(i0);
  endtask

  initial begin
    m0 = new(i0);
    fork
      m0.watch();
    join_none
    fork
      drive();
    join_none
    m0.wait_for(5);
    #2;
    if (m0.changes != 5) begin
      $display("%%Error: changes=%0d, expected 5", m0.changes);
      $stop;
    end
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
