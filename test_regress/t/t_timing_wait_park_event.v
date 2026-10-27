// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// @(ev) on a class member event parks, woken by ->ev; an aliased event falls back

class C;
  event ev;
  int n;
  task waiter();
    repeat (3) begin
      @(ev);
      n++;
    end
  endtask
  task fire();
    ->ev;
  endtask
endclass

class D;
  event ev;
  event ev2;
  int n;
  task waiter();
    repeat (3) begin
      @(ev);
      n++;
    end
  endtask
endclass

module t;
  C c = new;
  D d = new;
  initial begin
    fork
      c.waiter();
      d.waiter();
    join_none
    d.ev2 = d.ev;
    #10 ->c.ev;
    ->d.ev2;
    #10 c.fire();
    ->d.ev2;
    #10 ->c.ev;
    ->d.ev2;
    #1 $display("n=%0d m=%0d", c.n, d.n);
    if (c.n != 3 || d.n != 3) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
