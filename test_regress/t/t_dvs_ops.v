// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Operators of constraints solved with --solver-dvs, each checked over many
// randomizations

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

typedef enum bit [2:0] {
  RED = 1,
  GREEN = 3,
  BLUE = 6
} color_t;

class Arith;
  rand bit [6:0] a;
  rand bit [6:0] b;
  rand bit [14:0] w;
  constraint c {
    a + b == 7'd100;
    a * 2 < 7'd90;
    w == a * b;
    (a / 3) % 2 == 1;
    a - b != 0;
    -a != 7'd5;
  }
endclass

class Signed;
  rand int s;
  rand byte sb;
  rand shortint t;
  rand bit [7:0] u;
  constraint c {
    s > -5;
    s < 5;
    sb inside {[-3 : 3], 10};
    (s >>> 1) != 1;
    t / -3 == 2;
    t % 4 == -3;
    $signed(u) > -3;
    $signed(u) < 0;
    ($signed(u) >>> 1) == -1;
  }
endclass

class Bits;
  rand bit [7:0] a;
  rand bit [7:0] b;
  rand bit [62:0] q;
  constraint c {
    a[3:0] == 4'h5;
    {a[7:6], b[1:0]} == 4'b1001;
    (a & b) == 8'h01;
    (a | b) != 8'hff;
    (a ^ b) > 8'h10;
    ~b != 8'h00;
    (b << 2) < 8'd200;
    (b >> 6) == 8'd1;
    &q[62:60];
    |q[3:0] == 1'b0;
    {2{a[0]}} == 2'b11;
    q[59:40] == 20'habcde;
  }
endclass

class Logic;
  rand bit [7:0] a;
  rand bit [7:0] b;
  rand color_t col;
  rand bit f;
  rand int si;
  constraint c {
    a < 50;
    if (a > 25) b < 20;
    else b > 200;
    a > 10 -> b != 7;
    (a == 3) || (a == 30) || (a > 40);
    !(a == 30 && b == 5);
    f == (a > 45);
    (f ? b : a) != 8'd201;
    col != GREEN;
    (a == 31) <-> (b == 9);
    si > 0;
    si < 100;
    (f ? si : 32'(b)) != 32'd7;
  }
endclass

class State;
  rand bit [9:0] x;
  bit [9:0] lo;
  bit [9:0] hi;
  function bit [9:0] limit();
    return hi - 1;
  endfunction
  constraint c {
    x >= lo;
    x <= limit();
    x != lo + 1;
  }
endclass

module t;
  initial begin
    Arith ar;
    Signed sg;
    Bits bt;
    Logic lg;
    State st;
    bit seen_neg;
    bit seen_pos;
    bit seen_col[color_t];
    ar = new;
    sg = new;
    bt = new;
    lg = new;
    st = new;
    for (int i = 0; i < 100; ++i) begin
      `check(ar.randomize() == 1);
      `check(7'(ar.a + ar.b) == 100);
      `check(7'(ar.a * 2) < 90);
      `check(ar.w == 15'(ar.a * ar.b));
      `check((ar.a / 3) % 2 == 1);
      `check(ar.a != ar.b);
      `check(7'(-ar.a) != 5);

      `check(sg.randomize() == 1);
      `check(sg.s > -5 && sg.s < 5 && (sg.s >>> 1) != 1);
      `check((sg.sb >= -3 && sg.sb <= 3) || sg.sb == 10);
      `check(sg.t / -3 == 2 && sg.t % 4 == -3);
      `check(sg.u == 8'hfe || sg.u == 8'hff);
      if (sg.s < 0) seen_neg = 1;
      if (sg.s > 0) seen_pos = 1;

      `check(bt.randomize() == 1);
      `check(bt.a[3:0] == 4'h5 && bt.a[7:6] == 2'b10 && bt.b[1:0] == 2'b01);
      `check((bt.a & bt.b) == 8'h01 && (bt.a | bt.b) != 8'hff && (bt.a ^ bt.b) > 8'h10);
      `check(8'(bt.b << 2) < 200 && (bt.b >> 6) == 1);
      `check(bt.q[62:60] == 3'b111 && bt.q[3:0] == 0 && bt.q[59:40] == 20'habcde);

      `check(lg.randomize() == 1);
      `check(lg.a < 50);
      `check(lg.a > 25 ? lg.b < 20 : lg.b > 200);
      `check(lg.a <= 10 || lg.b != 7);
      `check(lg.a == 3 || lg.a == 30 || lg.a > 40);
      `check(!(lg.a == 30 && lg.b == 5));
      `check(lg.f == (lg.a > 45));
      `check((lg.a == 31) == (lg.b == 9));
      `check(lg.si > 0 && lg.si < 100 && (lg.f ? lg.si : 32'(lg.b)) != 7);
      `check(lg.col == RED || lg.col == BLUE);
      seen_col[lg.col] = 1;

      st.lo = 10'(i * 7);
      st.hi = 10'(i * 7 + 4);
      `check(st.randomize() == 1);
      `check(st.x >= st.lo && st.x < st.hi && st.x != st.lo + 1);
    end
    `check(seen_neg && seen_pos);
    `check(seen_col.num() == 2);
    st.lo = 10;
    st.hi = 10;
    `check(st.randomize() == 0);
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
