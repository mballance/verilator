// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Constraints --solver-dvs does not support; each class reports its first

class Sub;
  rand bit [7:0] v;
endclass

class ArrayElem;
  bit [7:0] arr[4];
  rand bit [1:0] k;
  constraint c {arr[k] < 4;}
endclass

class Sized;
  rand bit [7:0] arr[][];
  constraint c {arr.size() < 4;}
endclass

class Wide;
  rand bit [79:0] w;
  constraint c {w != 0;}
endclass

class Foreach;
  rand bit [7:0] x;
  bit [7:0] m[][];
  constraint c {foreach (m[i, j]) x != m[i][j];}
endclass

class ArrayStateIndex;
  rand bit [7:0] arr[4];
  int k;
  constraint c {unique {arr[k], arr[0]};}
endclass

class Reduce;
  rand bit [7:0] arr[];
  constraint c {foreach (arr[i]) unique {arr[i], arr[0]};}
endclass

class DynDist;
  rand bit [7:0] arr[];
  constraint c {arr[0] dist {1 := 1, 2 := 1};}
endclass

class DynBefore;
  rand bit [7:0] arr[];
  rand bit [7:0] x;
  constraint c {
    foreach (arr[i]) arr[i] < x;
    solve x before arr;
  }
endclass

class DynWhole;
  rand bit [7:0] arr[];
  bit [7:0] b[];
  constraint c {arr == b;}
endclass

class DynFixedIndex;
  rand bit [7:0] arr[];
  bit [7:0] lim[4];
  constraint c {foreach (arr[i]) arr[i] < lim[i];}
endclass

class DynIndexFunc;
  rand bit [7:0] arr[];
  function bit [7:0] f(int i);
    return 8'(i);
  endfunction
  constraint c {foreach (arr[i]) arr[i] != f(i);}
endclass

class DynScalarDist;
  rand bit [7:0] arr[];
  rand bit [7:0] x;
  constraint c {foreach (arr[i]) x dist {1 := 1, 2 := 1};}
endclass

class ArrayRange;
  rand bit [7:0] arr[5];
  constraint c {foreach (arr[i]) unique {arr[i], arr[i+1]};}
endclass

class ArrayWhole;
  rand bit [7:0] a[2];
  rand bit [7:0] b[2];
  constraint c {a == b;}
endclass

class DistSoftForeach;
  rand bit [7:0] arr[2];
  // verilator lint_off NONSTD
  constraint c {soft foreach (arr[i]) arr[i] dist {1 := 1, 2 := 1};}
  // verilator lint_on NONSTD
endclass

class Func;
  rand bit [7:0] x;
  rand bit [7:0] y;
  function bit [7:0] f(bit [7:0] a);
    return a + 1;
  endfunction
  constraint c {x == f(y);}
endclass

class RandC;
  randc bit [3:0] x;
  constraint c {x < 10;}
endclass

class RandMode;
  rand bit [7:0] x;
  constraint c {x < 10;}
endclass

class DisableSoft;
  rand bit [7:0] x;
  constraint c1 {soft x == 1;}
  constraint c2 {disable soft x;}
endclass

class DistIf;
  rand bit [7:0] x;
  rand bit s;
  constraint c {if (s) x dist {1 := 1, 2 := 1};}
endclass

class UniqueIf;
  rand bit [7:0] x;
  rand bit [7:0] y;
  rand bit s;
  constraint c {if (s) unique {x, y};}
endclass

class UniqueWidths;
  rand bit [7:0] x;
  rand bit [6:0] y;
  constraint c {unique {x, y};}
endclass

class UniqueWide;
  rand bit [39:0] x;
  rand bit [39:0] y;
  constraint c {unique {x, y};}
endclass

class DistWeight;
  rand bit [7:0] x;
  int w;
  constraint c {x dist {1 := w, 2 := 1};}
endclass

class DistExpr;
  rand bit [7:0] x;
  rand bit [7:0] y;
  constraint c {x + y dist {1 := 1, 2 := 1};}
endclass

class Other;
  rand Sub s;
  rand bit [7:0] q[];
  function new();
    s = new;
  endfunction
endclass

class HandleArray;
  rand Sub arr[int];
  constraint c {arr[0].v < 3;}
endclass

class HandleIndex;
  rand bit k;
  rand Sub arr[2];
  constraint c {arr[k].v < 3;}
endclass

class HandleRange;
  rand Sub arr[3];
  constraint c {foreach (arr[i]) arr[i + 1].v < 3;}
endclass

class HandleDyn;
  rand Sub arr[];
  constraint c {arr.sum() with (item.v) < 3;}
endclass

class HandleDist;
  rand Sub arr[];
  rand bit [7:0] d[];
  constraint c {foreach (arr[i]) d[i] dist {1 := 1, 2 := 1};}
endclass

class HandleWith;
  rand Sub arr[];
endclass

class DynSub;
  rand bit [7:0] q[];
endclass

class OtherDyn;
  rand DynSub s;
  constraint c {s.q.size() < 3;}
endclass

class OtherCall;
  rand bit [1:0] k;
  Sub subs[4];
  function Sub pick(bit [1:0] i);
    return subs[i];
  endfunction
  constraint c {pick(k).v < 3;}
endclass

class Limited;
  rand bit [7:0] v;
  constraint c {v < 5;}
endclass

class Clones;
  rand Limited l;
  rand bit [7:0] w;
endclass

class ManyHandles;
  rand Sub h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12, h13, h14, h15, h16, h17, h18, h19, h20, h21, h22, h23, h24, h25, h26, h27, h28, h29, h30, h31, h32, h33, h34, h35, h36, h37, h38, h39, h40, h41, h42, h43, h44, h45, h46, h47, h48, h49, h50, h51, h52, h53, h54, h55, h56, h57, h58, h59, h60, h61, h62, h63, h64;
endclass

class FourState;
  rand bit [7:0] x;
  constraint c {x != 8'b1x;}
endclass

class Circular;
  rand bit [7:0] x;
  rand bit [7:0] y;
  constraint c {
    solve x before y;
    solve y before x;
  }
endclass

class NoVars;
  rand bit [7:0] x;
  constraint c {1'b1;}
endclass

class VarSelect;
  rand bit [7:0] x;
  int i;
  constraint c {x[i] == 1'b1;}
endclass

class RandSelect;
  rand bit [7:0] x;
  rand bit [2:0] k;
  constraint c {x[k] == 1'b1;}
endclass

class WideState;
  rand bit [7:0] x;
  bit [99:0] big;
  constraint c {big == {92'b0, x};}
endclass

class WideExpr;
  rand bit [7:0] x;
  bit [63:0] q;
  constraint c {{x, q} != 0;}
endclass

class Packed;
  typedef struct packed {
    bit [3:0] hi;
    bit [3:0] lo;
  } pair_t;
  rand pair_t p;
  constraint c {p != 0;}
endclass

class UniqueExpr;
  rand bit [7:0] x;
  rand bit [7:0] y;
  constraint c {unique {x, y + 8'd1};}
endclass

class RealOperand;
  rand bit [7:0] x;
  real r;
  constraint c {x < r;}
endclass

class Base;
  rand bit [7:0] x;
endclass

class Extended extends Base;
  constraint c {x < 10;}
endclass

class ManySoft;
  rand bit [7:0] x;
  constraint c {
    soft x != 8'd0;
    soft x != 8'd1;
    soft x != 8'd2;
    soft x != 8'd3;
    soft x != 8'd4;
    soft x != 8'd5;
    soft x != 8'd6;
    soft x != 8'd7;
    soft x != 8'd8;
    soft x != 8'd9;
    soft x != 8'd10;
    soft x != 8'd11;
    soft x != 8'd12;
    soft x != 8'd13;
    soft x != 8'd14;
    soft x != 8'd15;
    soft x != 8'd16;
    soft x != 8'd17;
    soft x != 8'd18;
    soft x != 8'd19;
    soft x != 8'd20;
    soft x != 8'd21;
    soft x != 8'd22;
    soft x != 8'd23;
    soft x != 8'd24;
    soft x != 8'd25;
    soft x != 8'd26;
    soft x != 8'd27;
    soft x != 8'd28;
    soft x != 8'd29;
    soft x != 8'd30;
    soft x != 8'd31;
    soft x != 8'd32;
    soft x != 8'd33;
    soft x != 8'd34;
    soft x != 8'd35;
    soft x != 8'd36;
    soft x != 8'd37;
    soft x != 8'd38;
    soft x != 8'd39;
    soft x != 8'd40;
    soft x != 8'd41;
    soft x != 8'd42;
    soft x != 8'd43;
    soft x != 8'd44;
    soft x != 8'd45;
    soft x != 8'd46;
    soft x != 8'd47;
    soft x != 8'd48;
    soft x != 8'd49;
    soft x != 8'd50;
    soft x != 8'd51;
    soft x != 8'd52;
    soft x != 8'd53;
    soft x != 8'd54;
    soft x != 8'd55;
    soft x != 8'd56;
    soft x != 8'd57;
    soft x != 8'd58;
    soft x != 8'd59;
    soft x != 8'd60;
    soft x != 8'd61;
    soft x != 8'd62;
    soft x != 8'd63;
    soft x != 8'd64;
  }
endclass

class Locator;
  rand bit [7:0] arr[4];
  constraint c {arr.find(item) with (item == 8'd1).size() > 0;}
endclass

class FuncWith;
  rand bit [7:0] x;
  rand bit [7:0] y;
  function bit [7:0] f(bit [7:0] a);
    return a + 1;
  endfunction
endclass

class NestedElem;
  rand bit [7:0] x;
  rand bit [7:0] m[][];
  constraint c {x == m[1][0];}
endclass

class HandleQueueIndex;
  rand Sub hs[$];
  int k;
  constraint c {hs[k].v == 1;}
endclass

class AssocReduce;
  rand bit [7:0] aa[int];
  constraint c {aa.sum() with (int'(item)) < 10;}
endclass

class DeepForeach;
  rand bit [7:0] q[];
  constraint c {
    foreach (q[i1])
    foreach (q[i2])
    foreach (q[i3])
    foreach (q[i4])
    foreach (q[i5])
    foreach (q[i6])
    foreach (q[i7])
    foreach (q[i8])
    foreach (q[i9]) q[i9] != 1;
  }
endclass

class OtherForeach;
  rand DynSub s;
  rand int x;
  constraint c {foreach (s.q[i]) x != i;}
endclass

class StringForeach;
  rand int x;
  string names[$];
  constraint c {foreach (names[i]) x != i;}
endclass

class WideIndex;
  rand bit [7:0] q[];
  constraint c {foreach (q[i]) q[i] != 8'(128'(i) + 128'd1);}
endclass

class IndexReduce;
  rand int q[];
  int w[$];
  constraint c {foreach (q[i]) q[i] < w.sum() with (item + i);}
endclass

class InsideReal;
  rand int x;
  real r[$];
  constraint c {x inside {r};}
endclass

class InsideIndex;
  rand int q[];
  int lims[4][3];
  constraint c {foreach (q[i]) q[i] inside {lims[i]};}
endclass

class InsideOther;
  rand DynSub s;
  rand bit [7:0] x;
  constraint c {x inside {s.q};}
endclass

class InsideDeep;
  rand bit [7:0] q[];
  constraint c {
    foreach (q[i1])
    foreach (q[i2])
    foreach (q[i3])
    foreach (q[i4])
    foreach (q[i5])
    foreach (q[i6])
    foreach (q[i7])
    foreach (q[i8]) q[i8] inside {q};
  }
endclass

class InsidePin;
  rand bit [7:0] x;
  int q[$];
  constraint c {$countones(x) inside {q};}
endclass

module t;
  initial begin
    ArrayElem a1;
    Sized a2;
    Wide a3;
    Foreach a4;
    Func a5;
    RandC a6;
    RandMode a7;
    DisableSoft a8;
    DistIf a9;
    UniqueIf a10;
    UniqueWidths a11;
    UniqueWide a12;
    DistWeight a13;
    DistExpr a14;
    Other a15;
    FourState a16;
    Circular a18;
    NoVars a19;
    VarSelect a20;
    WideState a21;
    WideExpr a22;
    ManySoft a23;
    Packed a24;
    UniqueExpr a25;
    RealOperand a26;
    ArrayStateIndex a27;
    ArrayRange a28;
    ArrayWhole a29;
    DistSoftForeach a30;
    RandSelect a31;
    Reduce a32;
    DynDist a33;
    DynBefore a34;
    DynScalarDist a35;
    DynWhole a36;
    DynFixedIndex a37;
    DynIndexFunc a38;
    Locator a39;
    NestedElem a40;
    FuncWith a41;
    HandleArray a42;
    OtherDyn a43;
    Clones a44;
    ManyHandles a45;
    OtherCall a46;
    HandleIndex a47;
    HandleRange a48;
    HandleDyn a49;
    HandleDist a50;
    HandleWith a51;
    HandleQueueIndex a52;
    AssocReduce a53;
    DeepForeach a54;
    OtherForeach a55;
    StringForeach a56;
    WideIndex a57;
    IndexReduce a58;
    InsideReal a59;
    InsideIndex a60;
    InsideOther a61;
    InsideDeep a62;
    InsidePin a63;
    bit [7:0] v, w;
    a1 = new;
    void'(a1.randomize());
    a2 = new;
    void'(a2.randomize());
    a3 = new;
    void'(a3.randomize());
    a4 = new;
    void'(a4.randomize());
    a5 = new;
    void'(a5.randomize());
    a6 = new;
    void'(a6.randomize());
    a7 = new;
    void'(a7.randomize());
    a8 = new;
    void'(a8.randomize());
    a9 = new;
    void'(a9.randomize());
    a10 = new;
    void'(a10.randomize());
    a11 = new;
    void'(a11.randomize());
    a12 = new;
    void'(a12.randomize());
    a13 = new;
    void'(a13.randomize());
    a14 = new;
    void'(a14.randomize());
    a15 = new;
    void'(a15.randomize() with {q.size() < 3;});
    a16 = new;
    void'(a16.randomize());
    a18 = new;
    void'(a18.randomize());
    a19 = new;
    void'(a19.randomize());
    a20 = new;
    void'(a20.randomize());
    a21 = new;
    void'(a21.randomize());
    a22 = new;
    void'(a22.randomize());
    a23 = new;
    void'(a23.randomize());
    a24 = new;
    void'(a24.randomize());
    a25 = new;
    void'(a25.randomize());
    a26 = new;
    void'(a26.randomize());
    a27 = new;
    void'(a27.randomize());
    a28 = new;
    void'(a28.randomize());
    a29 = new;
    void'(a29.randomize());
    a30 = new;
    void'(a30.randomize());
    a31 = new;
    void'(a31.randomize());
    a32 = new;
    void'(a32.randomize());
    a33 = new;
    void'(a33.randomize());
    a34 = new;
    void'(a34.randomize());
    a35 = new;
    void'(a35.randomize());
    a36 = new;
    void'(a36.randomize());
    a37 = new;
    void'(a37.randomize());
    a38 = new;
    void'(a38.randomize());
    a39 = new;
    void'(a39.randomize());
    a40 = new;
    void'(a40.randomize());
    a41 = new;
    void'(a41.randomize() with {x == f(y);});
    a42 = new;
    void'(a42.randomize());
    a43 = new;
    void'(a43.randomize());
    a44 = new;
    void'(a44.randomize() with {solve w before l.v;});
    a45 = new;
    void'(a45.randomize());
    a46 = new;
    void'(a46.randomize());
    a47 = new;
    void'(a47.randomize());
    a48 = new;
    void'(a48.randomize());
    a49 = new;
    void'(a49.randomize());
    a50 = new;
    void'(a50.randomize());
    a51 = new;
    void'(a51.randomize() with {arr.size() == 2;});
    a52 = new;
    void'(a52.randomize());
    a53 = new;
    void'(a53.randomize());
    a54 = new;
    void'(a54.randomize());
    a55 = new;
    void'(a55.randomize());
    a56 = new;
    void'(a56.randomize());
    a57 = new;
    void'(a57.randomize());
    a58 = new;
    void'(a58.randomize());
    a59 = new;
    void'(a59.randomize());
    a60 = new;
    void'(a60.randomize());
    a61 = new;
    void'(a61.randomize());
    a62 = new;
    void'(a62.randomize());
    a63 = new;
    void'(a63.randomize());
    begin
      Extended e;
      Base b;
      e = new;
      b = e;
      void'(e.randomize());
      void'(b.randomize(null));
    end
    a7.x.rand_mode(0);
    void'(std::randomize(v, w) with {solve v before w; solve w before v;});
  end
endmodule
