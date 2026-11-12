// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Dynamic arrays and queues with --solver-dvs: sized before randomize(), or
// with a constrained size, solved before the elements

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

typedef enum bit [3:0] {
  A = 1,
  B = 4,
  C = 9
} e_t;

// Each element constrained alone: solved element by element
class Local;
  rand bit [7:0] q[$];
  rand int d[];
  rand e_t e[];
  constraint c {
    foreach (q[i]) q[i] < 10 && int'(q[i]) != i;
    foreach (d[i]) d[i] inside {[-5 : 5]};
  }
endclass

// Elements constrained together: instantiated per size
class Sorted;
  rand bit [7:0] a[];
  constraint c {
    foreach (a[i]) if (i > 0) a[i] > a[i-1];
    foreach (a[i]) (i < a.size() - 1) -> a[i] != 8'd255;
  }
endclass

class Sum;
  rand bit [7:0] q[$];
  rand bit [3:0] x;
  constraint c {
    q.sum() with (int'(item)) == 100;
    q.sum() with (item.index) == 6 * x;
    foreach (q[i]) q[i] > 0;
  }
endclass

class Uniq;
  rand bit [3:0] q[$];
  constraint c {
    unique {q};
    foreach (q[i]) q[i] < 6;
  }
endclass

class State;
  rand bit [7:0] a[];
  bit [7:0] lim[];
  constraint c {foreach (a[i]) a[i] > lim[i];}
endclass

class Index;
  rand bit [7:0] q[$];
  rand bit [1:0] k;
  constraint c {
    q[k] == 77;
    q[3] != 77;
    foreach (q[i]) (i != 2) -> q[i] != 77;
  }
endclass

class Dist;
  rand bit [7:0] q[$];
  constraint c {
    foreach (q[i]) q[i] dist {0 := 1, 1 := 3};
    foreach (q[i]) soft q[i] == 0;
  }
endclass

class Size;
  rand bit [7:0] q[$];
  rand int unsigned n;
  rand bit [7:0] d[];
  rand bit [7:0] b[$:2];
  constraint c {
    q.size() == n;
    n inside {[2 : 6]};
    foreach (q[i]) q[i] < 10;
    d.size() inside {[1 : 3]};
    d.sum() with (int'(item)) == 30;
    b.size() > 0;
  }
endclass

class Unbounded;
  rand bit [7:0] q[$];
  constraint c {q.size() > 3;}
endclass

// 'inside' with a dynamic array or queue as set member (IEEE 1800-2023 11.4.13)
class Inside;
  int allowed[$];  // Read before the call
  bit [7:0] lim[];
  rand int x;
  rand bit [3:0] n;
  rand bit [7:0] r[];  // Random elements
  rand bit [7:0] v;
  rand bit [7:0] q[$];  // Random size and elements
  rand bit [7:0] w;
  int qs[2][$];  // An array of them, at a 'foreach' index
  rand int fa[2];
  bit [31:0] big[$];  // Unsigned elements
  rand int s;
  constraint c {
    x inside {allowed};
    foreach (fa[i]) fa[i] inside {qs[i]};
    s inside {big};
    !(n inside {allowed});
    foreach (r[i]) r[i] inside {lim};
    foreach (r[i]) (i inside {allowed}) -> r[i] == 7;
    v inside {r};
    q.size() inside {[1 : 3]};
    foreach (q[i]) q[i] > 100;
    w inside {q};
  }
endclass

// A mixed set, whose array may be empty
class InsideMixed;
  int s[$];
  rand int z;
  constraint c {z inside {-1, [5 : 6], s};}
endclass

module t;
  initial begin
    Local lo;
    Sorted so;
    Sum su;
    Uniq un;
    State st;
    Index ix;
    Dist di;
    int seen[int];
    int ones;
    int mask;
    lo = new;
    so = new;
    su = new;
    un = new;
    st = new;
    ix = new;
    di = new;

    // Sizes are kept, and may change between calls
    for (int n = 0; n < 40; n += 3) begin
      lo.q = {};
      repeat (n) lo.q.push_back(0);
      lo.d = new[n / 2];
      lo.e = new[n];
      `check(lo.randomize() == 1);
      `check(lo.q.size() == n && lo.d.size() == n / 2);
      foreach (lo.q[i]) begin
        `check(lo.q[i] < 10 && lo.q[i] != i);
        seen[lo.q[i]] = 1;
      end
      foreach (lo.d[i]) `check(lo.d[i] >= -5 && lo.d[i] <= 5);
      foreach (lo.e[i]) `check(lo.e[i] == A || lo.e[i] == B || lo.e[i] == C);
    end
    `check(seen.num() == 10);

    for (int r = 0; r < 20; ++r) begin
      so.a = new[r % 2 == 0 ? 6 : 12];
      `check(so.randomize() == 1);
      foreach (so.a[i]) if (i > 0) `check(so.a[i] > so.a[i-1]);
    end

    for (int r = 0; r < 20; ++r) begin
      su.q = '{0, 0, 0, 0};
      `check(su.randomize() == 1);
      `check(su.q[0] + su.q[1] + su.q[2] + su.q[3] == 100);
      `check(su.x == 1);
    end

    un.q = '{0, 0, 0, 0, 0, 0};
    for (int r = 0; r < 10; ++r) begin
      `check(un.randomize() == 1);
      mask = 0;
      foreach (un.q[i]) mask |= 1 << un.q[i];
      `check(mask == 'h3f);
    end
    un.q.push_back(0);
    `check(un.randomize() == 0);
    `check(un.q.size() == 7);

    st.a = new[5];
    st.lim = '{250, 3, 100};
    for (int r = 0; r < 10; ++r) begin
      `check(st.randomize() == 1);
      foreach (st.a[i]) `check(st.a[i] > (i < 3 ? st.lim[i] : 0));
    end
    st.lim[1] = 255;
    st.a = '{1, 2, 3, 4, 5};
    `check(st.randomize() == 0);
    `check(st.a[0] == 1 && st.a[4] == 5);

    ix.q = '{0, 0, 0, 0};
    for (int r = 0; r < 10; ++r) begin
      `check(ix.randomize() == 1);
      `check(ix.k == 2 && ix.q[2] == 77);
    end

    repeat (400) di.q.push_back(0);
    `check(di.randomize() == 1);
    ones = 0;
    foreach (di.q[i]) begin
      `check(di.q[i] <= 1);
      ones += di.q[i];
    end
    `check(ones < 40);

    begin
      Inside in;
      InsideMixed im;
      int xs[int];
      int ws[int];
      bit found;
      in = new;
      in.allowed = '{3, 1000000, -7, 12};
      in.lim = '{7, 200};
      in.r = new[5];
      in.qs = '{'{1, 2}, '{30}};
      in.big = '{32'hfffffff0};
      for (int r = 0; r < 40; ++r) begin
        `check(in.randomize() == 1);
        `check((in.fa[0] == 1 || in.fa[0] == 2) && in.fa[1] == 30);
        `check(in.s == -16);
        `check(in.x inside {in.allowed});
        xs[in.x] = 1;
        `check(in.n != 3 && in.n != 12);
        foreach (in.r[i]) `check(in.r[i] == 7 || in.r[i] == 200);
        `check(in.r[3] == 7);
        `check(in.v inside {in.r});
        `check(in.q.size() >= 1 && in.q.size() <= 3);
        found = 0;
        foreach (in.q[i]) begin
          `check(in.q[i] > 100);
          if (in.q[i] == in.w) found = 1;
        end
        `check(found);
        ws[in.q.size()] = 1;
      end
      `check(xs.num() == 4);
      `check(ws.num() == 3);
      // An empty array matches nothing
      in.allowed = {};
      in.x = 55;
      `check(in.randomize() == 0);
      `check(in.x == 55);

      im = new;
      xs.delete();
      repeat (40) begin
        `check(im.randomize() == 1);
        `check(im.z == -1 || im.z == 5 || im.z == 6);
      end
      im.s = '{100};
      repeat (40) begin
        `check(im.randomize() == 1);
        `check(im.z == -1 || im.z == 5 || im.z == 6 || im.z == 100);
        xs[im.z] = 1;
      end
      `check(xs.num() == 4);
    end

    begin
      Size sz;
      Unbounded ub;
      int sizes[int];
      sz = new;
      for (int r = 0; r < 40; ++r) begin
        `check(sz.randomize() == 1);
        `check(sz.q.size() == sz.n && sz.n >= 2 && sz.n <= 6);
        foreach (sz.q[i]) `check(sz.q[i] < 10);
        `check(sz.d.size() >= 1 && sz.d.size() <= 3);
        `check(sz.d.sum() with (int'(item)) == 30);
        `check(sz.b.size() >= 1 && sz.b.size() <= 3);
        sizes[sz.q.size()] = 1;
      end
      `check(sizes.num() == 5);
      // An array size left unbounded is almost surely over the limit: a failure
      ub = new;
      ub.q = '{1, 2};
      `check(ub.randomize() == 0);
      `check(ub.q.size() == 2);
    end

    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
