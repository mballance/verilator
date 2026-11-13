// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Constraints across objects (IEEE 1800-2023 18.5.8) with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

// Nested handles: constraints of each object, and on members two handles away
class Inner;
  rand bit [6:0] v;
  rand bit [14:0] free;  // Exported, constrained by no one
  constraint c_inner {v inside {[1 : 10]};}
endclass

class Mid;
  rand Inner inner;
  rand bit [6:0] x;
  bit [6:0] limit;  // A state value of the part of Mid
  constraint c_mid {
    x <= limit;
    x > inner.v;
  }
  function new;
    inner = new;
    limit = 15;
  endfunction
endclass

class Top;
  rand Mid m;
  rand bit [6:0] y;
  constraint c_top {
    y < m.x;
    m.inner.v < y;
  }
  function new;
    m = new;
  endfunction
endclass

// A derived object in a base handle: its overriding and added blocks apply
class Shape;
  rand bit [7:0] a;
  constraint c_a {a > 10;}
  constraint c_b {a < 20;}
endclass

class Square extends Shape;
  rand bit [7:0] b;
  constraint c_b {a > 30;}  // Overrides Shape's
  constraint c_sq {b == a + 1;}
endclass

class Holder;
  rand Shape s;
  constraint c {s.a < 50;}
endclass

// A null handle guarded, and not
class Leaf;
  rand bit [6:0] v;
  constraint c_leaf {v < 60;}
endclass

class Opt;
  rand Leaf l;
  rand bit [7:0] k;
  constraint c {
    if (l != null) k == l.v + 1;
    else k == 7;
  }
endclass

class Bad;
  rand Leaf l;
  rand bit [6:0] k;
  constraint c {k < l.v;}
endclass

// Soft constraints across objects (IEEE 1800-2023 18.5.13)
class SoftSub;
  rand bit [7:0] t;
  constraint c_soft {soft t == 10;}
endclass

class SoftTop;
  rand SoftSub p;
  rand SoftSub q;
  rand SoftSub r;
  constraint c {
    soft r.t == 20;  // The container's soft beats the contained's
    p.t == q.t;  // Conflicting softs: the later handle's wins
  }
  function new;
    p = new;
    q = new;
    r = new;
    q.c_soft.constraint_mode(0);
  endfunction
endclass

class SoftQ extends SoftSub;
  constraint c_soft2 {soft t == 30;}
endclass

// One object reached through two handles is solved once
class Pair;
  rand Leaf a;
  rand Leaf b;
  constraint c {a.v + b.v == 100;}
endclass

// constraint_mode() of a sub-object is that object's own
class Ci;
  rand bit [7:0] v;
  constraint c_lo {v < 10;}
endclass

class Co;
  rand Ci c;
  rand bit [7:0] w;
  constraint k {w == c.v;}
  function new;
    c = new;
  endfunction
endclass

// A sub-object constrained only by the derived class of the object holding it: it is not
// basic-randomized again after the solve
class BrIn;
  rand bit [7:0] v;
endclass

class BrMid;
  rand BrIn i;
  function new;
    i = new;
  endfunction
endclass

class BrMidD extends BrMid;
  constraint c {i.v == 77;}
endclass

class BrTop;
  rand BrMid m;
endclass

// randomize() with {...} on an object solved with others: the inline constraints name the
// object's members and those of its sub-objects, and rank above their constraints
class WSub;
  rand bit [7:0] v;
  constraint c {v < 50;}
  constraint c_soft {soft v == 7;}
endclass

class WTop;
  rand WSub s;
  rand WSub n;
  rand bit [7:0] x;
  rand bit [7:0] y;
  constraint c {x > s.v;}
  function new;
    s = new;
  endfunction
  function int go(bit [7:0] t);
    return this.randomize() with {s.v == t;};
  endfunction
endclass

// Fixed-size arrays of rand handles: each element is a slot
class AItem;
  rand int unsigned value;
  constraint c_item {value < 100;}
endclass

class AItemD extends AItem;
  constraint c_d {value > 50;}
endclass

class AHolder;
  rand AItem items[4];
  rand AItem grid[2][2];
  rand int unsigned first;
  rand Leaf after;
  rand bit [7:0] k;
  constraint c {
    k == after.v + 1;
    first == items[0].value;
    // items[-1], out of range, is never read: a null handle, as if guarded
    foreach (items[i]) if (i > 0) items[i].value > items[i - 1].value;
    foreach (grid[i, j]) if (grid[i][j] != null) grid[i][j].value == 10 * i + j + first;
  }
  function new;
    foreach (items[i]) items[i] = new;
    foreach (grid[i, j]) grid[i][j] = new;
    after = new;
  endfunction
endclass

// Dynamic arrays and queues of rand handles: slot arrays
class DItem;
  rand int v;
  rand Leaf sub;
  constraint c_item {v inside {[0 : 99]};}
  function new;
    sub = new;
  endfunction
endclass

class DItemD extends DItem;
  constraint c_d {v > 50;}
endclass

class DHolder;
  rand DItem items[];
  rand DItem q[$];
  rand int first;
  constraint c {
    first inside {[0 : 49]};
    // size() in a foreach over the array is that of the call
    foreach (items[i]) {
      if (items[i] != null) {
        items[i].v >= 10 * i + items.size();
        int'(items[i].sub.v) == i;
      }
    }
    foreach (q[i]) q[i].v == first + i;
  }
  function new(int n);
    DItem it;
    items = new[n];
    foreach (items[i]) items[i] = new;
    repeat (2) begin
      it = new;
      q.push_back(it);
    end
  endfunction
endclass

// Random sizes: shrunk, and grown with the new (null) elements guarded
class DSized;
  rand DItem items[];
  constraint c {
    items.size() == 2;
    foreach (items[i]) items[i].v == i + 1;
  }
  function new;
    items = new[3];
    foreach (items[i]) items[i] = new;
  endfunction
endclass

// The container's soft ranks above its elements' under randomize() with
class DSoftItem;
  rand int v;
  constraint c {soft v == 2;}
endclass

class DSoft;
  rand DSoftItem items[];
  constraint c {soft items[0].v == 1;}
  function new;
    items = new[1];
    items[0] = new;
  endfunction
endclass

class DGrow;
  rand DItem items[$];
  rand int n;
  constraint c {
    n inside {[3 : 4]};
    items.size() == n;
    foreach (items[i]) if (items[i] != null) items[i].v == 7;
  }
  function new;
    DItem it = new;
    items.push_back(it);
  endfunction
endclass

module t;
  initial begin
    Top top;
    top = new;
    repeat (20) begin
      `check(top.randomize() == 1);
      `check(top.m.inner.v >= 1 && top.m.inner.v <= 10);
      `check(top.m.x <= 15 && top.m.x > top.m.inner.v);
      `check(top.y < top.m.x && top.m.inner.v < top.y);
    end
    // A state value of a sub-object is read from that object
    top.m.limit = 3;
    `check(top.randomize() == 1);
    `check(top.m.x <= 3 && top.m.inner.v == 1 && top.y == 2);
  end

  initial begin
    Holder h;
    Square sq;
    h = new;
    h.s = new;
    repeat (20) begin
      `check(h.randomize() == 1);
      `check(h.s.a > 10 && h.s.a < 20);
    end
    sq = new;
    h.s = sq;
    repeat (20) begin
      `check(h.randomize() == 1);
      `check(sq.a > 30 && sq.a < 50 && sq.b == sq.a + 1);
    end
  end

  initial begin
    Opt o;
    Leaf lf;
    o = new;
    repeat (5) begin
      `check(o.randomize() == 1);
      `check(o.k == 7);
    end
    lf = new;
    o.l = lf;
    repeat (20) begin
      `check(o.randomize() == 1);
      `check(lf.v < 60 && o.k == lf.v + 1);
    end
    // An inactive handle: its object is not randomized, its values are read
    o.l.rand_mode(0);
    lf.v = 42;
    repeat (5) begin
      `check(o.randomize() == 1);
      `check(lf.v == 42 && o.k == 43);
    end
  end

  initial begin
    Bad b;
    b = new;
    // A read through a null handle that no guard rules out fails, with a warning once
    `check(b.randomize() == 0);
    `check(b.randomize() == 0);
    b.l = new;
    `check(b.randomize() == 1);
    `check(b.k < b.l.v);
  end

  initial begin
    SoftTop st;
    SoftQ sqq;
    st = new;
    repeat (10) begin
      `check(st.randomize() == 1);
      `check(st.r.t == 20 && st.p.t == 10 && st.q.t == 10);
    end
    // The derived object's soft beats the base's within it; the later handle's beats both
    sqq = new;
    st.p = sqq;
    st.q.c_soft.constraint_mode(1);
    repeat (10) begin
      `check(st.randomize() == 1);
      `check(st.p.t == 10 && st.q.t == 10);
    end
    st.q.c_soft.constraint_mode(0);
    repeat (10) begin
      `check(st.randomize() == 1);
      `check(st.p.t == 30 && st.q.t == 30);
    end
  end

  initial begin
    Pair p;
    Leaf lf;
    p = new;
    lf = new;
    p.a = lf;
    p.b = lf;
    repeat (10) begin
      `check(p.randomize() == 1);
      `check(lf.v == 50);
    end
  end

  initial begin
    WTop wt;
    WSub n;
    bit [7:0] t;
    wt = new;
    repeat (20) begin
      t = 8'($urandom_range(30, 1));
      `check(wt.randomize() with {
        s.v == t;
        x < s.v + 8'd5;
      } == 1);
      `check(wt.s.v == t && wt.x > t && wt.x < t + 5);
      `check(wt.go(t + 1) == 1);
      `check(wt.s.v == t + 1 && wt.x > t + 1);
    end
    // The sub-object's own constraint holds
    `check(wt.randomize() with {s.v > 60;} == 0);
    // Its soft gives way to an inline soft
    `check(wt.randomize() == 1);
    `check(wt.s.v == 7);
    `check(wt.randomize() with {soft s.v == 9;} == 1);
    `check(wt.s.v == 9);
    // A null handle guarded in the inline constraints
    `check(wt.randomize() with {
      if (n != null) n.v == 3;
      else x == 99;
    } == 1);
    `check(wt.x == 99);
    n = new;
    wt.n = n;
    `check(wt.randomize() with {
      if (n != null) n.v == 3;
      else x == 99;
    } == 1);
    `check(n.v == 3);
    // 'dist' and 'unique' on the object's variables
    repeat (10) begin
      `check(wt.randomize() with {
        x dist {25 := 1, 26 := 1};
        unique {x, y};
        y >= 25;
        y <= 26;
      } == 1);
      `check((wt.x == 25 || wt.x == 26) && wt.y == 51 - wt.x && wt.s.v < wt.x);
    end
  end

  initial begin
    Shape sh;
    Square sq;
    // A derived object in a base handle: its overriding and added blocks apply
    sq = new;
    sh = sq;
    repeat (20) begin
      `check(sh.randomize() with {a < 40;} == 1);
      `check(sq.a > 30 && sq.a < 40 && sq.b == sq.a + 1);
    end
    sh = new;
    repeat (20) begin
      `check(sh.randomize() with {a > 15;} == 1);
      `check(sh.a > 15 && sh.a < 20);
    end
  end

  initial begin
    BrTop bt;
    BrMidD md;
    bt = new;
    md = new;
    bt.m = md;
    repeat (10) begin
      `check(bt.randomize() == 1);
      `check(md.i.v == 77);
    end
  end

  initial begin
    AHolder ah;
    AItemD d;
    ah = new;
    repeat (20) begin
      `check(ah.randomize() == 1);
      `check(ah.first == ah.items[0].value && ah.items[3].value < 100);
      for (int i = 1; i < 4; ++i) `check(ah.items[i].value > ah.items[i - 1].value);
      foreach (ah.grid[i, j]) `check(ah.grid[i][j].value == 10 * i + j + ah.first);
    end
    // A derived object in an element, and a null element guarded
    d = new;
    ah.items[1] = d;
    ah.grid[1][0] = null;
    repeat (20) begin
      `check(ah.randomize() == 1);
      `check(d.value > 50 && ah.items[3].value < 100);
      for (int i = 1; i < 4; ++i) `check(ah.items[i].value > ah.items[i - 1].value);
      `check(ah.grid[0][0].value == ah.first && ah.grid[1][1].value == 11 + ah.first);
    end
    // Inline constraints on an element
    `check(ah.randomize() with {items[2].value == 60;} == 1);
    `check(ah.items[2].value == 60 && d.value > 50 && d.value < 60);
    // rand_mode(0) of a handle after the arrays: its slot follows their elements' slots
    ah.after.rand_mode(0);
    ah.after.v = 42;
    repeat (5) begin
      `check(ah.randomize() == 1);
      `check(ah.after.v == 42 && ah.k == 43);
    end
  end

  initial begin
    DHolder dh;
    DItemD d;
    DItem keep;
    DSized ds;
    DSoft dsoft;
    DGrow dg;
    dh = new(3);
    repeat (20) begin
      `check(dh.randomize() == 1);
      foreach (dh.items[i]) begin
        `check(dh.items[i].v >= 10 * i + 3 && dh.items[i].v < 100);
        `check(int'(dh.items[i].sub.v) == i);
      end
      `check(dh.q[0].v == dh.first && dh.q[1].v == dh.first + 1);
    end
    // A derived object in an element, and a null element guarded
    d = new;
    dh.items[1] = d;
    keep = dh.items[2];
    dh.items[2] = null;
    repeat (10) begin
      `check(dh.randomize() == 1);
      `check(d.v > 50 && d.v < 100 && d.sub.v == 1 && dh.items[0].v >= 3);
    end
    // Another size (another shape), and an object in both arrays
    dh.items = new[5];
    foreach (dh.items[i]) dh.items[i] = new;
    dh.q.push_back(dh.items[4]);
    repeat (10) begin
      `check(dh.randomize() == 1);
      foreach (dh.items[i]) `check(dh.items[i].v >= 10 * i + 5 && int'(dh.items[i].sub.v) == i);
      `check(dh.q[2] == dh.items[4] && dh.items[4].v == dh.first + 2);
    end
    // Inline constraints on the elements
    repeat (10) begin
      `check(dh.randomize() with {foreach (items[i]) items[i].v < 60;} == 1);
      foreach (dh.items[i]) `check(dh.items[i].v >= 10 * i + 5 && dh.items[i].v < 60);
    end
    // Random sizes
    ds = new;
    `check(ds.randomize() == 1);
    `check(ds.items.size() == 2 && ds.items[0].v == 1 && ds.items[1].v == 2);
    // A size the object's constraints change, iterated by inline constraints
    ds = new;
    `check(ds.randomize() with {foreach (items[i]) items[i].v < 5;} == 1);
    `check(ds.items.size() == 2 && ds.items[0].v == 1 && ds.items[1].v == 2);
    dsoft = new;
    `check(dsoft.randomize() with {foreach (items[i]) items[i].v >= 0;} == 1);
    `check(dsoft.items[0].v == 1);
    dg = new;
    `check(dg.randomize() == 1);
    `check(dg.items.size() == dg.n && dg.items[0].v == 7);
    for (int i = 1; i < dg.items.size(); ++i) `check(dg.items[i] == null);
  end

  initial begin
    Co co;
    bit seen;
    co = new;
    repeat (20) begin
      `check(co.randomize() == 1);
      `check(co.w == co.c.v && co.w < 10);
    end
    co.c.c_lo.constraint_mode(0);
    seen = 0;
    repeat (20) begin
      `check(co.randomize() == 1);
      `check(co.w == co.c.v);
      if (co.w >= 10) seen = 1;
    end
    `check(seen);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
