// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Fixed-size arrays and 'foreach' with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

typedef enum bit [3:0] {
  A = 1,
  B = 4,
  C = 9
} e_t;

typedef struct packed {
  bit [3:0] hi;
  bit [3:0] lo;
} ps_t;

class Arrays;
  rand bit [7:0] sorted[5];  // Strictly increasing, in [10:30]
  rand bit [3:0] grid[2][3];  // Storage order of a 2-D array
  rand bit [3:0] col[2][3];  // A dimension not iterated
  rand bit [7:0] desc[3:1];  // Descending range
  rand byte sgn[3];  // Signed elements
  rand e_t e[3];  // Enum elements
  rand bit [7:0] free[4];  // Only element 0 constrained
  rand bit [7:0] x;
  rand bit [1:0] w[6];
  rand bit [7:0] odd[3];  // Out-of-range read: odd[i + 1] at i == 2
  int st[4] = '{3, 1, 4, 1};
  constraint c_sorted {
    foreach (sorted[i]) {
      sorted[i] inside {[10 : 30]};
      i > 0 -> sorted[i] > sorted[i-1];
    }
    sorted[0] == 10;
  }
  constraint c_grid {foreach (grid[i, j]) grid[i][j] == i * 3 + j;}
  constraint c_col {foreach (col[, j]) col[1][j] == j;}
  constraint c_desc {foreach (desc[k]) desc[k] == k;}
  constraint c_sgn {foreach (sgn[i]) sgn[i] < -100;}
  constraint c_e {foreach (e[i]) e[i] != A;}
  constraint c_free {free[0] == 1;}
  constraint c_x {
    foreach (st[i]) x != st[i];
    x < 6;
    solve sorted[0] before x;
  }
  constraint c_w {foreach (w[i]) w[i] dist {0 := 1, 3 := 3};}
  constraint c_odd {foreach (odd[i]) odd[i] >= odd[i+1];}
endclass

class Soft;
  rand bit [7:0] f[3];
  rand bit [7:0] g[2][2];
  // verilator lint_off NONSTD
  constraint c_f {soft foreach (f[i]) f[i] == 7;}
  // verilator lint_on NONSTD
  constraint c_f1 {f[1] == 9;}
  constraint c_g {foreach (g[i]) foreach (g[i][j]) soft g[i][j] == i + j;}
endclass

class Whole;
  rand bit [2:0] u[2][3];  // Whole arrays in 'unique' and 'solve before'
  rand bit [2:0] v;
  rand bit [7:0] y;
  constraint c_u {
    unique {u, v};
    solve u before y;
    y == u[0][0];
  }
endclass

class Reserved;
  rand e_t r;
  rand e_t ri;  // Constrained by randomize() with {...}
  e_t reserved[];  // Not random, elements of a typedef
  rand bit [7:0] p;
  ps_t pairs[];  // Not random, packed struct elements
  constraint c_r {foreach (reserved[i]) r != reserved[i];}
  constraint c_p {
    foreach (pairs[i]) p != pairs[i];
    p < 3;
  }
endclass

class Packed;
  rand bit [15:0] v;
  rand bit [3:0] m[2];
  rand bit [7:1] d;
  rand bit [3:0] s;
  // riscv-dv's pmp_val: lock bits 0, no W=1 with R=0
  constraint c_v {
    foreach (v[i]) {
      if ((i + 1) % 4 == 0) v[i] == 1'b0;
      if (i % 4 == 0) !(v[i] == 0 && v[i+1] == 1'b1);
    }
  }
  constraint c_m {foreach (m[i, j]) m[i][j] == (i == j);}
  // d[8] is out of range, so reads 0
  constraint c_d {foreach (d[i]) d[i] != d[i+1];}
  // s[4] is out of range: s[3] == 0, then the others
  constraint c_s {foreach (s[i]) s[i+:2] != 2'b01;}
endclass

module t;
  initial begin
    Arrays o;
    Soft s;
    Whole wh;
    Reserved rs;
    Packed pk;
    e_t reservedRi[];
    int freeDiff;
    int wCount[4];
    o = new;
    s = new;
    for (int n = 0; n < 200; ++n) begin
      `check(o.randomize() == 1);
      `check(o.sorted[0] == 10);
      for (int i = 1; i < 5; ++i) `check(o.sorted[i] > o.sorted[i-1] && o.sorted[i] <= 30);
      for (int i = 0; i < 2; ++i) for (int j = 0; j < 3; ++j) `check(o.grid[i][j] == i * 3 + j);
      for (int j = 0; j < 3; ++j) `check(o.col[1][j] == j);
      for (int k = 1; k <= 3; ++k) `check(o.desc[k] == k);
      for (int i = 0; i < 3; ++i) `check(o.sgn[i] < -100);
      for (int i = 0; i < 3; ++i) `check(o.e[i] inside {B, C});
      `check(o.free[0] == 1);
      if (o.free[1] != o.free[2] || o.free[2] != o.free[3]) ++freeDiff;
      `check(o.x inside {0, 2, 5});
      for (int i = 0; i < 6; ++i) begin
        `check(o.w[i] inside {0, 3});
        ++wCount[o.w[i]];
      end
      `check(o.odd[0] >= o.odd[1] && o.odd[1] >= o.odd[2]);
    end
    `check(freeDiff > 150);
    // Expected 300 and 900
    `check(wCount[0] > 200 && wCount[0] < 400);
    `check(o.randomize() with {sorted[4] == 14;} == 1);
    `check(o.sorted[1] == 11 && o.sorted[4] == 14);
    `check(o.randomize() with {grid[1][2] == 0;} == 0);
    `check(s.randomize() == 1);
    `check(s.f[0] == 7 && s.f[1] == 9 && s.f[2] == 7);
    wh = new;
    for (int n = 0; n < 50; ++n) begin
      bit [7:0] seen;
      `check(wh.randomize() == 1);
      seen = 8'b1 << wh.v;
      foreach (wh.u[i, j]) begin
        `check(!seen[wh.u[i][j]]);
        seen[wh.u[i][j]] = 1'b1;
      end
      `check(wh.y == wh.u[0][0]);
    end
    `check(s.g[0][0] == 0 && s.g[0][1] == 1 && s.g[1][0] == 1 && s.g[1][1] == 2);
    rs = new;
    rs.reserved = '{A, B};
    rs.pairs = '{8'h00, 8'h01};
    reservedRi = '{B, C};
    for (int n = 0; n < 20; ++n) begin
      `check(rs.randomize() with {foreach (reservedRi[i]) ri != reservedRi[i];} == 1);
      `check(rs.r == C && rs.ri == A && rs.p == 2);
    end
    pk = new;
    freeDiff = 0;
    for (int n = 0; n < 50; ++n) begin
      `check(pk.randomize() == 1);
      for (int i = 0; i < 16; i += 4) `check(!pk.v[i+3] && !(!pk.v[i] && pk.v[i+1]));
      `check(pk.m[0] == 4'b0001 && pk.m[1] == 4'b0010);
      `check(pk.d == 7'b1010101 && pk.s == 0);
      if (pk.v[2:0] != 3'b010) ++freeDiff;
    end
    `check(freeDiff > 40);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
