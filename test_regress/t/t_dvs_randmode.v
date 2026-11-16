// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// rand_mode() and randomize() arguments on constrained variables with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Instr;
  rand bit [4:0] rs1, rs2, rd;
  rand bit [11:0] imm;
  bit hasRs2 = 1;
  bit hasImm = 1;
  constraint c_imm {imm[11:5] == 0;}
  constraint c_reg {
    rd != 0;
    rs1 != rd;
    rs2 != rs1;
  }
  // The riscv-dv pattern: modes set before each solve
  function void pre_randomize();
    rs2.rand_mode(hasRs2);
    imm.rand_mode(hasImm);
  endfunction
endclass

class Arr;
  rand bit [7:0] a[3];
  rand bit [7:0] y;
  constraint c_a {foreach (a[i]) a[i] < 50;}
  constraint c_y {y > a[0];}
endclass

class Base;
  rand bit [7:0] b;
  constraint c_b {b inside {[1 : 20]};}
endclass

class Derived extends Base;
  rand bit [7:0] d;
  constraint c_d {d == b + 1;}
endclass

class Dist;
  rand bit [3:0] w;
  rand bit [3:0] v;
  constraint c_w {w dist {[0 : 3] := 1, [12 : 15] := 1};}
  constraint c_v {
    v > w;
    solve w before v;
  }
endclass

class Sub;
  rand bit [7:0] s;
  constraint c_s {s < 100;}
endclass

class Top;
  rand Sub sub;
  rand bit [7:0] t;
  constraint c_t {t == sub.s + 1;}
  function new();
    sub = new;
  endfunction
endclass

class Stable;
  rand bit [15:0] p, q;
  constraint c {p != q;}
endclass

module t;
  initial begin
    Instr ins;
    Arr arr;
    Derived der;
    Dist dst;
    Top top;
    Stable st1, st2;
    bit [11:0] oldImm;
    bit [4:0] oldRs2;
    bit [7:0] oldA[3];
    bit [7:0] oldB;
    int changed;
    int ok;

    // Off: held at the value before the call, still constrained by its constraints
    ins = new;
    `check(ins.randomize() == 1);
    for (int n = 0; n < 60; ++n) begin
      ins.hasRs2 = n % 3 != 0;
      ins.hasImm = n % 2 != 0;
      oldImm = ins.imm;
      oldRs2 = ins.rs2;
      `check(ins.randomize() == 1);
      if (!ins.hasImm) `check(ins.imm == oldImm);
      if (!ins.hasRs2) `check(ins.rs2 == oldRs2);
      `check(ins.imm[11:5] == 0 && ins.rd != 0 && ins.rs1 != ins.rd && ins.rs2 != ins.rs1);
      if (ins.hasImm && ins.imm != oldImm) ++changed;
    end
    `check(changed > 20);
    // A held value that violates a constraint: UNSAT, the user's constraints reported
    ins.hasImm = 0;
    ins.imm = 12'hfff;
    `check(ins.randomize() == 0);
    `check(ins.imm == 12'hfff);
    // On again
    ins.hasImm = 1;
    `check(ins.randomize() == 1);
    `check(ins.imm[11:5] == 0);

    // Fixed-size array, the whole array off; the other variables still solved
    arr = new;
    `check(arr.randomize() == 1);
    arr.a.rand_mode(0);
    oldA = arr.a;
    for (int n = 0; n < 20; ++n) begin
      `check(arr.randomize() == 1);
      `check(arr.a == oldA && arr.y > arr.a[0]);
    end
    arr.a.rand_mode(1);
    changed = 0;
    for (int n = 0; n < 20; ++n) begin
      `check(arr.randomize() == 1);
      if (arr.a != oldA) ++changed;
      foreach (arr.a[i]) `check(arr.a[i] < 50);
    end
    `check(changed > 15);

    // A variable of the base class; the object's rand_mode()
    der = new;
    der.b = 7;
    der.b.rand_mode(0);
    for (int n = 0; n < 10; ++n) begin
      `check(der.randomize() == 1);
      `check(der.b == 7 && der.d == 8);
    end
    der.rand_mode(0);
    der.d = 3;
    `check(der.randomize() == 0);  // d == b + 1 fails with both held
    der.d = 8;
    `check(der.randomize() == 1);
    `check(der.b == 7 && der.d == 8);
    der.rand_mode(1);
    `check(der.randomize() == 1);
    `check(der.d == der.b + 1 && der.b inside {[1 : 20]});

    // Held in 'dist' and 'solve before'
    dst = new;
    dst.w = 2;
    dst.w.rand_mode(0);
    for (int n = 0; n < 20; ++n) begin
      `check(dst.randomize() == 1);
      `check(dst.w == 2 && dst.v > 2);
    end

    // A variable of a sub-object, through a global constraint
    top = new;
    top.sub.s = 41;
    top.sub.s.rand_mode(0);
    for (int n = 0; n < 10; ++n) begin
      `check(top.randomize() == 1);
      `check(top.sub.s == 41 && top.t == 42);
    end

    // randomize(args): only the arguments are solved, the modes restored after
    der = new;
    `check(der.randomize() == 1);
    for (int n = 0; n < 20; ++n) begin
      oldB = der.b;
      `check(der.randomize(d) == 1);
      `check(der.b == oldB && der.d == der.b + 1);
    end
    `check(der.b.rand_mode() == 1 && der.d.rand_mode() == 1);
    changed = 0;
    for (int n = 0; n < 20; ++n) begin
      oldB = der.b;
      `check(der.randomize(b, d) == 1);
      if (der.b != oldB) ++changed;
      `check(der.d == der.b + 1 && der.b inside {[1 : 20]});
    end
    `check(changed > 10);

    // Holding p does not change the value q gets for the same seed
    st1 = new;
    st2 = new;
    st1.srandom(5);
    st2.srandom(5);
    st2.p.rand_mode(0);
    ok = 0;
    for (int n = 0; n < 10; ++n) begin
      `check(st1.randomize() == 1);
      st2.p = st1.p;
      `check(st2.randomize() == 1);
      if (st2.q == st1.q) ++ok;
    end
    `check(ok == 10);

    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
