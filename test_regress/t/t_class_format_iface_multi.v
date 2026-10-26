// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

interface class IA;
  pure virtual function void a();
endclass
interface class IB;
  pure virtual function void b();
endclass

// Resolved before Printed marks IA and IB as emitting to_string()
class Bridge implements IA, IB;
  virtual function void a();
  endfunction
  virtual function void b();
  endfunction
endclass

class Printed implements IA, IB;
  int x = 1;
  virtual function void a();
  endfunction
  virtual function void b();
  endfunction
endclass

module t;
  initial begin
    Bridge br = new;
    Printed p = new;
    $display("%p", p);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
