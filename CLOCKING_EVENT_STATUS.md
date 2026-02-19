<!-- SPDX-FileCopyrightText: 2026-2026 Wilson Snyder -->
<!-- SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0 -->

# Covergroup Clocking Event Status

## Overview

Covergroup clocking events (`covergroup cg @(posedge clk)`) specify when a covergroup should automatically sample. Verilator has **partial support** for this feature.

## What Works

**Clocking events with MODULE INPUT clocks:**

```systemverilog
module t(input clk);
   covergroup cg @(posedge clk);
      // ...
   endgroup
   cg cg_inst = new;

   always @(posedge clk) begin
      // Verilator automatically inserts: cg_inst.sample();
      // at the top of this block
   end
endmodule
```

**Test:** `t_covergroup_clocking_module_input.v` -  PASSES

**Implementation:** When Verilator sees a clocking event referencing a module input, it automatically inserts a `.sample()` call at the beginning of any `always @(posedge clk)` blocks in the same module.

**Examples of passing tests:**
- `t_covergroup_auto_sample.v`
- `t_covergroup_cross_small.v`
- `t_covergroup_cross_large.v`
- `t_covergroup_empty.v`
- `t_covergroup_get_coverage.v`
- `t_covergroup_iff.v`
- `t_covergroup_multi_instance.v`
- `t_covergroup_negative_ranges.v`

## What Doesn't Work

**Clocking events with INTERNALLY GENERATED clocks:**

```systemverilog
module t;
   logic clk = 0;
   always #5 clk = ~clk;  // Internal clock generation

   covergroup cg @(posedge clk);
      // ...
   endgroup
   cg cg_inst = new;

   initial begin
      @(posedge clk);
      // Verilator does NOT automatically sample here
      // The covergroup is never sampled!
   end
endmodule
```

**Test:** `t_covergroup_clocking_internal.v` -  FAILS (timeout)

**Issue:** Verilator doesn't insert automatic `.sample()` calls when the clock is an internal signal rather than a module port.

**Affected tests:**
- `t_covergroup_simple.v` - Uses internal clock, times out
- `t_covergroup_coverage_pct.v` - Uses internal clock, times out

## Workaround

For internal clocks, explicitly call `.sample()`:

```systemverilog
module t;
   logic clk = 0;
   always #5 clk = ~clk;

   covergroup cg;  // No clocking event
      // ...
   endgroup
   cg cg_inst = new;

   always @(posedge clk) begin
      cg_inst.sample();  // Explicit call
      // ... rest of code
   end
endmodule
```

## Implementation Details

### Where Auto-Sampling Code is Generated

File: `src/V3Active.cpp` or `src/V3Sched.cpp` (scheduling phase)

The Verilator scheduling phase identifies:
1. Covergroups with clocking events
2. `always @(posedge clk)` blocks in the same module
3. Inserts `.sample()` calls at the top of matching blocks

### Why Internal Clocks Don't Work

When the clock is a module input:
- The sensitivity list `@(posedge clk)` in the module directly references the input
- Verilator can match this against the covergroup's clocking event
- The scheduling phase can reliably identify where to insert sample calls

When the clock is internally generated:
- The clock may not appear in any `always @(posedge clk)` blocks in the same module
- The `initial` block uses `@(posedge clk)` but this is procedural, not structural
- Verilator's scheduling phase doesn't track internal signal edges for covergroup sampling

## IEEE 1800-2017 Reference

Section 19.4.1: "Specifying triggering events"

> A covergroup can be triggered automatically by an event, or the sampling can be explicitly controlled by calling the built-in sample() method or through an argument to the covergroup constructor.

The standard requires both automatic (clocking event) and explicit (sample()) modes. Verilator currently supports:
-  Explicit sampling (`.sample()` calls)
-  Automatic sampling for module input clocks
-  Automatic sampling for internal signals

## Recommendation

For maximum compatibility:
1. Use module input clocks when possible
2. For internal clocks, use explicit `.sample()` calls
3. Tests requiring internal clock auto-sampling should be marked as "unsupported feature"

## Future Work

To fully implement internal clock support:
1. Track internal signal edges in the scheduling phase
2. Identify which procedural blocks are sensitive to those edges
3. Insert `.sample()` calls in those contexts
4. Handle edge cases (multiple clock domains, gated clocks, etc.)

This is a more complex scheduling problem than module input clocks.
