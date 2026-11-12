// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Array elements at non-constant indices, and array reductions, with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

class Index;
  rand bit [7:0] a[5];
  rand bit [2:0] k;  // Selects the element equal to 31
  rand bit [2:0] z;  // Out of range: reads 0
  rand bit [3:0] g[3][2];
  rand bit [1:0] r;  // Random row of a 2-D array
  rand bit [7:0] b[4];
  int s = 2;  // Index read before the call
  constraint c_a {
    foreach (a[i]) a[i] == i * 10 + 1;
    a[k] == 31;
    a[z] == 0;
  }
  constraint c_g {
    foreach (g[i, j]) g[i][j] == i * 2 + j;
    g[r][1] == 5;
  }
  constraint c_b {b[s] == 99;}
endclass

class Reduce;
  rand bit [7:0] s[4];
  rand int d[5];
  rand bit [3:0] p[3];
  rand bit [7:0] q[3];
  rand bit [3:0] h[4];
  rand bit [1:0] perm[4];
  rand bit [3:0] m[2][3];
  rand byte sb[3];
  rand bit [3:0] n[2];
  int st[3] = '{1, 2, 3};
  constraint c_s {
    s.sum() == 100;
    foreach (s[i]) s[i] inside {[20 : 30]};
  }
  constraint c_d {
    foreach (d[i]) d[i] inside {[0 : 9]};
    d.sum() with (int'(item < 5)) == 3;
  }
  constraint c_p {
    p.product() with (int'(item)) == 24;
    foreach (p[i]) p[i] > 1;
  }
  constraint c_q {
    q.xor() == 8'h5a;
    q.and() == 0;
    q.or() == 8'hff;
  }
  constraint c_h {h.sum() with (item.index == 0 ? int'(item) : 0) == 7;}
  constraint c_perm {foreach (perm[i]) perm.sum() with (int'(item == perm[i])) == 1;}
  constraint c_m {m[1].sum() == 9;}
  constraint c_sb {
    sb.sum() == -30;
    foreach (sb[i]) sb[i] inside {[-20 : -1]};
  }
  // A 'with' nested in a 'with': a non-random sub-expression with its own 'item'
  constraint c_n {n.sum() with (int'(item) + st.sum() with (item)) == 20;}
endclass

// 'inside' with a fixed-size array as set member (IEEE 1800-2023 11.4.13)
class Inside;
  rand bit [7:0] a[4];
  rand bit [7:0] x;
  rand bit [7:0] z;
  rand int y;
  rand int u;
  rand bit [3:0] k[2];
  rand bit [3:0] w;
  int lim[3] = '{-7, 1000000, 42};  // Read before the call
  bit [3:0] tbl[2][2] = '{'{1, 2}, '{3, 4}};
  constraint c {
    foreach (a[i]) a[i] inside {[10 : 13]};
    x inside {a};
    !(z inside {a});
    z inside {[10 : 14]};
    y inside {lim};
    u inside {lim};
    u != y;
    foreach (k[i]) k[i] inside {tbl[i]};
    w inside {1, [5 : 6], tbl[1]};
  }
endclass

module t;
  initial begin
    Index ix;
    Reduce rd;
    Inside in;
    int ys[int];
    ix = new;
    rd = new;
    in = new;
    repeat (40) begin
      `check(in.randomize() == 1);
      `check(in.x inside {in.a});
      `check(!(in.z inside {in.a}) && in.z >= 10 && in.z <= 14);
      `check(in.y inside {in.lim} && in.u inside {in.lim} && in.u != in.y);
      ys[in.y] = 1;
      `check(in.k[0] inside {1, 2} && in.k[1] inside {3, 4});
      `check(in.w inside {1, 3, 4, 5, 6});
    end
    `check(ys.num() == 3);
    // The array is read on each call
    in.lim = '{5, 5, 6};
    repeat (10) begin
      `check(in.randomize() == 1);
      `check(in.y inside {5, 6} && in.u inside {5, 6});
    end
    repeat (20) begin
      `check(ix.randomize() == 1);
      `check(ix.k == 3);
      `check(ix.z >= 5);
      `check(ix.r == 2);
      `check(ix.b[ix.s] == 99);
      ix.s = (ix.s + 1) % 4;

      `check(rd.randomize() == 1);
      `check(8'(rd.s[0] + rd.s[1] + rd.s[2] + rd.s[3]) == 100);
      `check(int'(rd.d[0] < 5) + int'(rd.d[1] < 5) + int'(rd.d[2] < 5) + int'(rd.d[3] < 5)
             + int'(rd.d[4] < 5) == 3);
      `check(rd.p[0] * rd.p[1] * rd.p[2] == 24);
      `check((rd.q[0] ^ rd.q[1] ^ rd.q[2]) == 8'h5a);
      `check((rd.q[0] & rd.q[1] & rd.q[2]) == 0);
      `check((rd.q[0] | rd.q[1] | rd.q[2]) == 8'hff);
      `check(rd.h[0] == 7);
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < i; ++j) `check(rd.perm[i] != rd.perm[j]);
      `check(4'(rd.m[1][0] + rd.m[1][1] + rd.m[1][2]) == 9);
      `check(byte'(rd.sb[0] + rd.sb[1] + rd.sb[2]) == -30);
      `check(rd.n[0] + rd.n[1] == 8);
    end
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
