// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Matthew Ballance
// SPDX-License-Identifier: CC0-1.0

// Writes through obj.f and from a derived class wake parked waiters

class Base;
  int f;
  int g;
  task wait_f(int v); wait (f == v); endtask
  task wait_g(int v); wait (g >= v); endtask
endclass
class Der extends Base;
  function void bump(); g = g + 1; endfunction
endclass
class Writer;
  Base b;
  function void set(int v); b.f = v; endfunction
endclass
module t;
  Der d = new;
  Writer w = new;
  int n = 0;
  initial begin
    w.b = d;
    fork
      begin for (int i = 1; i <= 100; i++) begin d.wait_f(i); n++; end end
      begin d.wait_g(50); $display("g=%0d", d.g); end
      begin for (int i = 1; i <= 100; i++) begin #1 w.set(i); d.bump(); end end
    join
    $display("n=%0d", n);
    if (n != 100) $stop;
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
