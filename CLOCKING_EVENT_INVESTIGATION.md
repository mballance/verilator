# Clocking Event Investigation Summary

**Date:** 2026-02-13

## Initial Confusion

Tests `t_covergroup_simple` and `t_covergroup_coverage_pct` were failing with:
```
%Error-NEEDTIMINGOPT: Use --timing or --no-timing to specify how delays should be handled
```

This appeared to be a simple test configuration issue - just add `--timing` flag.

## Discovery

After investigation, found that **8+ other tests** successfully use clocking events:
- `t_covergroup_auto_sample` ✅
- `t_covergroup_cross_small` ✅
- `t_covergroup_cross_large` ✅
- `t_covergroup_empty` ✅
- `t_covergroup_get_coverage` ✅
- `t_covergroup_iff` ✅
- `t_covergroup_multi_instance` ✅
- `t_covergroup_negative_ranges` ✅

**Key difference identified:**

**Passing tests:** Use `module t(input clk);` - clock is a **module port**

**Failing tests:** Use `module t; logic clk; always #5 clk = ~clk;` - clock is **internal**

## Root Cause

Verilator's clocking event implementation has **partial support**:

✅ **Works:** Clocking events with module input clocks
- Verilator automatically inserts `.sample()` calls in `always @(posedge clk)` blocks
- This is the common use case

❌ **Doesn't Work:** Clocking events with internally generated clocks
- No automatic `.sample()` insertion for internal signals
- Tests timeout because covergroups never sample

## Actions Taken

### 1. Created Specific Test Cases

**`t_covergroup_clocking_module_input.v/.py`** - Documents working case
- Uses module input clock
- ✅ PASSES

**`t_covergroup_clocking_internal.v/.py`** - Documents limitation
- Uses internally generated clock
- ❌ FAILS (as expected)
- Contains clear comments explaining the limitation

### 2. Created Documentation

**`CLOCKING_EVENT_STATUS.md`** - Comprehensive documentation
- Explains what works and what doesn't
- Shows code examples
- Suggests workarounds
- References IEEE 1800-2017 standard
- Identifies future work needed

### 3. Updated Analysis

**`FAILING_TESTS_ANALYSIS.md`** - Updated to clarify
- These are NOT simple timing flag issues
- They expose a partial feature implementation
- Categorized as "limitation" rather than "bug"

## Test Suite Impact

**Before investigation:** 46/56 passing (82.1%)

**After adding specific tests:** 47/58 passing (81.0%)
- Added 2 new tests
- 1 passes (module input case)
- 1 fails (internal clock case - documents limitation)

## Recommendations

1. **For users:** Use module input clocks with clocking events, or call `.sample()` explicitly

2. **For developers:** To fully implement internal clock support:
   - Track internal signal edges in scheduling phase
   - Identify procedural blocks sensitive to those edges  
   - Insert `.sample()` calls appropriately
   - Handle edge cases (multiple domains, gated clocks)

3. **For tests:**
   - `t_covergroup_simple` and `t_covergroup_coverage_pct` should be marked as "unsupported feature" or updated to use explicit `.sample()` calls
   - The new specific tests clearly document the feature boundary

## Conclusion

This investigation revealed that what appeared to be a simple test configuration issue was actually a deeper discovery about **partial feature implementation**. The clocking event feature **does work** for the common case (module inputs), but has a known limitation with internal signals.

The new tests and documentation make this boundary explicit and will help future developers understand the current implementation state.
