// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// A wait on another object's members, wait(f.wr != f.rd), parks on f's wait queue
class Fifo;
  int wr = 0;
  int rd = 0;
  int data[16];
  function void push(int v);
    data[wr % 16] = v;
    wr = wr + 1;
  endfunction
  function int pop();
    pop = data[rd % 16];
    rd = rd + 1;
  endfunction
endclass

class M;
  Fifo f;
  int sum = 0;
  function new();
    f = new;
  endfunction
  task run();
    repeat (100) begin
      wait (f.wr != f.rd);
      sum += f.pop();
    end
  endtask
endclass

module t;
  M m;
  initial begin
    m = new;
    fork
      m.run();
    join_none
    for (int i = 1; i <= 100; i++) begin
      #1;
      m.f.push(i);
    end
    #1;
    if (m.sum != 5050) $stop;
    $write("sum=%0d\n", m.sum);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
