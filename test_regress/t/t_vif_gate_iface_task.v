// DESCRIPTION: Verilator: Gated vif triggers for members written by iface tasks
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2026 by Wilson Snyder.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

interface ifc;
  int cnt;
  int nb;
  task incr();
    cnt++;
  endtask
  task add2();
    cnt = cnt + 2;
  endtask
  task nb_incr();
    nb <= nb + 1;
  endtask
endinterface

class Driver;
  virtual ifc vif;
  function new(virtual ifc v);
    vif = v;
  endfunction
  task run();
    repeat (5) begin
      #1 vif.incr();
      #1 vif.add2();
      #1 vif.nb_incr();
    end
  endtask
endclass

class Monitor;
  virtual ifc vif;
  int changes;
  int nb_changes;
  function new(virtual ifc v);
    vif = v;
  endfunction
  task watch_cnt();
    forever begin
      @(vif.cnt);
      changes++;
    end
  endtask
  task wait_done();
    wait (vif.cnt == 15);
    wait (vif.nb == 5);
  endtask
  task watch_nb();
    forever begin
      @(vif.nb);
      nb_changes++;
    end
  endtask
endclass

module t;
  ifc i ();
  Driver d;
  Monitor m;

  initial begin
    d = new(i);
    m = new(i);
    fork
      m.watch_cnt();
      m.watch_nb();
    join_none
    fork
      d.run();
    join_none
    m.wait_done();
    #2;
    if (m.changes != 10) begin
      $display("%%Error: changes=%0d, expected 10", m.changes);
      $stop;
    end
    if (m.nb_changes != 5) begin
      $display("%%Error: nb_changes=%0d, expected 5", m.nb_changes);
      $stop;
    end
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
