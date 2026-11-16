// DESCRIPTION: Verilator: Verilog Test module
//
// This file ONLY is placed under the Creative Commons Public Domain.
// SPDX-FileCopyrightText: 2026 Wilson Snyder
// SPDX-License-Identifier: CC0-1.0

// Packed structs, random variables wider than 64 bits, and dynamic arrays of unpacked
// structs with --solver-dvs

// verilog_format: off
`define stop $stop
`define check(cond) do if (!(cond)) begin $write("%%Error: %s:%0d: check failed\n", `__FILE__,`__LINE__); `stop; end while(0);
// verilog_format: on

typedef enum bit [1:0] {
  OFF,
  TOR,
  NA4,
  NAPOT
} mode_t;

// riscv-dv's mseccfg_reg_t
typedef struct packed {
  bit rlb;
  bit mmwp;
  bit mml;
} cfg_t;

typedef struct packed {
  bit l;
  mode_t a;
  bit [4:0] addr;
} entry_t;

class Packed;
  rand cfg_t cfg = '{1'b1, 1'b0, 1'b0};
  rand entry_t e;
  rand entry_t arr[3];
  rand bit [7:0] x;
  constraint c_cfg {
    cfg.mml == 0;
    cfg.rlb -> cfg.mmwp;
  }
  constraint c_e {
    e.a inside {TOR, NAPOT};
    e.addr > 20;
    x == e.addr + 1;
  }
  constraint c_arr {
    foreach (arr[i]) {
      arr[i].a == NA4;
      arr[i].addr == i;
    }
    arr[0] != arr[1];
  }
endclass

// riscv-dv's vtype_t at XLEN 32: 122 bits
typedef struct packed {
  bit ill;
  bit fractional_lmul;
  bit [30:7] reserved;
  int vediv;
  int vsew;
  int vlmul;
} vtype_t;

class Wide;
  rand vtype_t vtype;
  rand bit [99:0] w;  // Selects within a word and across words
  rand bit [69:0] ws[2];
  rand int vl;
  constraint c_vtype {
    vtype.vlmul inside {1, 2, 4, 8};
    vtype.vsew inside {8, 16, 32};
    vtype.vediv inside {1, 2, 4, 8};
    vtype.vediv <= vtype.vsew / 8;
    (vtype.vlmul < 8) || (vtype.fractional_lmul == 1'b1);
    vtype.reserved == 0;
    vl inside {[1 : 256 / vtype.vsew]};
    solve vtype before vl;
  }
  constraint c_w {
    w[95:40] == 56'h12_3456_789a_bcde;
    w[99:96] == w[3:0];
    w[3:0] != 0;
    foreach (ws[i]) ws[i][69:64] == 6'(i + 1);
    ws[0][63:0] == ws[1][63:0];
  }
endclass

class Sub;
  rand bit [79:0] s;
  constraint c_s {s[79:72] < 10;}
endclass

class Top;
  rand Sub sub;
  rand bit [7:0] t;
  constraint c_t {t == sub.s[79:72] + 1;}
  function new();
    sub = new;
  endfunction
endclass

// riscv-dv's pmp_cfg_reg_t: an unpacked struct with rand members
typedef enum bit [1:0] {
  A0,
  A1,
  A2
} a_t;
typedef struct {
  rand bit l;
  bit [1:0] zero;  // Not random: kept
  rand a_t a;
  rand bit w;
  rand bit r;
  rand bit [31:0] addr;
  rand integer addr_mode;
} pmp_t;

class Pmp;
  rand pmp_t cfg[];
  rand bit hi;
  constraint c_size {cfg.size() inside {[2 : 5]};}
  constraint c_xwr {
    foreach (cfg[i]) {
      solve hi before cfg[i].w;
      !(cfg[i].w && !cfg[i].r);
    }
  }
  constraint c_mode {
    foreach (cfg[i]) {
      cfg[i].addr_mode >= 0;
      cfg[i].addr_mode <= 32;
      solve cfg[i].a before cfg[i].addr;
    }
  }
  constraint c_order {
    foreach (cfg[i]) {
      if (i > 0 && cfg[i].a == A1) cfg[i].addr > cfg[i-1].addr;
      hi -> cfg[i].addr[31:29] == 0;
    }
  }
endclass

// riscv-dv's mem_region_t and addr_c: a queue of unpacked structs that is not random
typedef struct {
  string name;  // Not integral: not passed
  int unsigned size_in_bytes;
  bit [2:0] xwr;
} region_t;

class LoadStore;
  region_t data_page[$];
  rand int unsigned data_page_id;
  rand int unsigned max_offset;
  rand int unsigned base;
  rand int unsigned other;
  constraint addr_c {
    solve data_page_id before max_offset;
    solve max_offset before base;
    data_page_id < data_page.size();
    foreach (data_page[i]) {
      if (i == data_page_id) {
        max_offset == data_page[i].size_in_bytes;
      }
    }
    base inside {[0 : max_offset - 1]};
    other < data_page[data_page_id].xwr + 1;  // At a random index
  }
endclass

// riscv-dv's riscv_instr_gen_config: the struct arrays of rand objects it holds, solved
// together with it
class Holder;
  rand Pmp pm;
  rand LoadStore ls;
  rand bit [3:0] n;
  constraint c_n {n == pm.hi + ls.data_page_id;}
  function new();
    pm = new;
    ls = new;
    ls.data_page.push_back('{"a", 16, 3'd1});
    ls.data_page.push_back('{"b", 4096, 3'd4});
  endfunction
endclass

module t;
  initial begin
    Packed p;
    int count;
    p = new;
    for (int n = 0; n < 50; ++n) begin
      `check(p.randomize() == 1);
      `check(p.cfg.mml == 0 && (!p.cfg.rlb || p.cfg.mmwp));
      `check(p.e.a inside {TOR, NAPOT} && p.e.addr > 20 && p.x == p.e.addr + 1);
      foreach (p.arr[i]) `check(p.arr[i].a == NA4 && p.arr[i].addr == i);
      if (p.e.l) ++count;
    end
    `check(count > 10 && count < 40);
    `check(p.randomize() with {e == '{1'b0, NA4, 5'd21};} == 0);
    `check(p.randomize() with {e == '{1'b1, TOR, 5'd21};} == 1);
    `check(p.e.l && p.e.a == TOR && p.x == 22);
    begin
      Wide wd;
      Top top;
      bit [99:0] oldW;
      wd = new;
      count = 0;
      for (int n = 0; n < 50; ++n) begin
        `check(wd.randomize() == 1);
        `check(wd.vtype.vlmul inside {1, 2, 4, 8} && wd.vtype.vsew inside {8, 16, 32});
        `check(wd.vtype.vediv <= wd.vtype.vsew / 8 && wd.vtype.reserved == 0);
        `check(wd.vtype.vlmul < 8 || wd.vtype.fractional_lmul);
        `check(wd.vl >= 1 && wd.vl <= 256 / wd.vtype.vsew);
        `check(wd.w[95:40] == 56'h12_3456_789a_bcde && wd.w[99:96] == wd.w[3:0] && wd.w[3:0]);
        `check(wd.ws[0][69:64] == 1 && wd.ws[1][69:64] == 2 && wd.ws[0][63:0] == wd.ws[1][63:0]);
        if (wd.vtype.ill) ++count;
      end
      `check(count > 10 && count < 40);
      // rand_mode() holds all the words
      wd.w.rand_mode(0);
      oldW = wd.w;
      `check(wd.randomize() == 1);
      `check(wd.w == oldW);
      top = new;
      for (int n = 0; n < 20; ++n) begin
        `check(top.randomize() == 1);
        `check(top.sub.s[79:72] < 10 && top.t == top.sub.s[79:72] + 1);
      end
    end
    begin
      Pmp pm;
      int sizes[6];
      pm = new;
      for (int n = 0; n < 100; ++n) begin
        foreach (pm.cfg[i]) pm.cfg[i].zero = 2'(i);
        `check(pm.randomize() == 1);
        `check(pm.cfg.size() >= 2 && pm.cfg.size() <= 5);
        ++sizes[pm.cfg.size()];
        foreach (pm.cfg[i]) begin
          `check(!(pm.cfg[i].w && !pm.cfg[i].r));
          `check(pm.cfg[i].addr_mode >= 0 && pm.cfg[i].addr_mode <= 32);
          `check(pm.cfg[i].a inside {A0, A1, A2});
          if (i > 0 && pm.cfg[i].a == A1) `check(pm.cfg[i].addr > pm.cfg[i-1].addr);
          if (pm.hi) `check(pm.cfg[i].addr[31:29] == 0);
        end
      end
      for (int k = 2; k <= 5; ++k) `check(sizes[k] > 5);
      // The members not random keep their values, as far as the array keeps its elements
      pm.cfg = new[3];
      foreach (pm.cfg[i]) pm.cfg[i].zero = 2'(i + 1);
      `check(pm.randomize() with {cfg.size() == 3;} == 1);
      foreach (pm.cfg[i]) `check(pm.cfg[i].zero == 2'(i + 1));
    end
    begin
      LoadStore ls;
      int seen[3];
      ls = new;
      ls.data_page.push_back('{"a", 16, 3'd1});
      ls.data_page.push_back('{"b", 4096, 3'd4});
      ls.data_page.push_back('{"c", 100, 3'd7});
      for (int n = 0; n < 60; ++n) begin
        `check(ls.randomize() == 1);
        `check(ls.data_page_id < 3);
        ++seen[ls.data_page_id];
        `check(ls.max_offset == ls.data_page[ls.data_page_id].size_in_bytes);
        `check(ls.base < ls.max_offset);
        `check(ls.other <= ls.data_page[ls.data_page_id].xwr);
      end
      foreach (seen[i]) `check(seen[i] > 5);
      `check(ls.data_page.size() == 3 && ls.data_page[1].name == "b");
      `check(ls.data_page[2].size_in_bytes == 100);
    end
    begin
      Holder h;
      h = new;
      for (int n = 0; n < 20; ++n) begin
        `check(h.randomize() == 1);
        `check(h.pm.cfg.size() >= 2 && h.pm.cfg.size() <= 5);
        foreach (h.pm.cfg[i]) `check(!(h.pm.cfg[i].w && !h.pm.cfg[i].r));
        `check(h.ls.max_offset == h.ls.data_page[h.ls.data_page_id].size_in_bytes);
        `check(h.n == h.pm.hi + h.ls.data_page_id);
      end
    end
    $write("*-* All Finished *-*\n");
    $finish;
  end
endmodule
