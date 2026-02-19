<!-- SPDX-FileCopyrightText: 2026-2026 Wilson Snyder -->
<!-- SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0 -->

# Automatic Bins Implementation Status

## What Was Implemented

Implemented implicit automatic bin creation when coverpoints have no explicit bins (IEEE 1800-2017 Section 19.4.1).

### Features Working

1. **Implicit automatic bins** - When a coverpoint has no explicit bins, automatic bins are created
2. **Default auto_bin_max=64** - Uses IEEE standard default
3. **Proper bin sizing** - If signal range ≤ auto_bin_max, creates one bin per value; otherwise divides range
4. **Coverage calculation** - Correctly calculates percentage based on covered/total bins

### Test Results

- **t_covergroup_autobins CG1**: ✅ PASSING (3-bit signal, 8 auto bins, 37.5% coverage)
- **t_covergroup_autobins CG4**: ✅ PASSING (2-bit signal, 4 auto bins, 100% coverage)
- **t_covergroup_autobins CG2**: ❌ FAILING (needs covergroup-level option.auto_bin_max=4)
- **t_covergroup_autobins CG3**: ❌ FAILING (needs ignore_bins respected during auto-creation)
- **t_covergroup_autobins CG5**: ❌ FAILING (needs covergroup-level option.auto_bin_max=2)

## Implementation Details

### Code Changes

**File**: `src/V3CoverageFunctional.cpp`

Added three new functions:

1. `getAutoBinMax()` - Extracts auto_bin_max option from coverpoint (currently only checks coverpoint-level)
2. `hasRegularBins()` - Checks if coverpoint has any non-ignore/illegal bins  
3. `createImplicitAutoBins()` - Creates automatic bins when none exist

### Algorithm

```cpp
if (!hasRegularBins(coverpointp)) {
    autoBinMax = getAutoBinMax(coverpointp);  // Default: 64
    width = exprp->width();
    numValues = 2^width;
    
    if (numValues <= autoBinMax) {
        // Create one bin per value
        numBins = numValues;
    } else {
        // Divide range into autoBinMax bins
        numBins = autoBinMax;
    }
    
    // Create bins covering [0:maxVal]
    for (i = 0; i < numBins; i++) {
        create bin auto_i covering appropriate range
    }
}
```

### Generated Code Example

For 3-bit signal (CG1), generates:

```cpp
class cg1 {
    uint32_t __Vcov_cp_data3_auto_0;  // Bin for value 0
    uint32_t __Vcov_cp_data3_auto_1;  // Bin for value 1
    ...
    uint32_t __Vcov_cp_data3_auto_7;  // Bin for value 7
    
    void sample() {
        if (data3 == 0) __Vcov_cp_data3_auto_0++;
        if (data3 == 1) __Vcov_cp_data3_auto_1++;
        ...
    }
    
    double get_inst_coverage() {
        covered = 0;
        if (__Vcov_cp_data3_auto_0 >= 1) covered++;
        if (__Vcov_cp_data3_auto_1 >= 1) covered++;
        ...
        return 100.0 * (covered / 8.0);
    }
};
```

## Known Limitations

### 1. Covergroup-Level Options Not Supported

**Issue**: `option.auto_bin_max = N` at covergroup level is ignored

**Root Cause**: V3Width deletes `AstCgOptionAssign` nodes before V3CoverageFunctional runs

**Example**:
```systemverilog
covergroup cg2;
   option.auto_bin_max = 4;  // ← IGNORED
   cp: coverpoint data;       // Uses default 64 instead
endgroup
```

**Workaround**: Use coverpoint-level options:
```systemverilog
covergroup cg2;
   coverpoint data {
      option.auto_bin_max = 4;  // ← WORKS
   }
endgroup
```

**Proper Fix Needed**: 
- Convert `AstCgOptionAssign` to `AstCoverOption` in parser
- Store in AstClass as member list
- Access in V3CoverageFunctional

### 2. Ignore Bins Not Respected

**Issue**: `ignore_bins` declarations don't exclude values from automatic bins

**Example**:
```systemverilog
coverpoint data {
   ignore_bins reserved = {7};  // ← Value 7 still gets a bin
}
```

**Current Behavior**: Creates 8 bins (0-7) even though 7 should be ignored

**Expected Behavior**: Should create 7 bins (0-6), excluding 7

**Fix Needed**:
- In `createImplicitAutoBins()`, check for existing ignore_bins
- Exclude ignored values when creating automatic bins
- Adjust total bin count for coverage calculation

### 3. Illegal Bins Not Respected

**Issue**: Similar to ignore_bins, `illegal_bins` should prevent bin creation

**Fix**: Same approach as ignore_bins fix

## Impact

### Passing Tests

With this implementation, 2 more test scenarios pass:
- ✅ Basic automatic bins (default auto_bin_max)
- ✅ Full coverage calculation for auto bins

### Still Failing

3 test scenarios still fail due to limitations:
- ❌ Covergroup-level auto_bin_max (requires parser/AST changes)
- ❌ Automatic bins with ignore_bins (needs ignore list processing)
- ❌ Automatic bins with reduced auto_bin_max (same as covergroup-level issue)

### Overall Status

**Before**: 40/56 tests passing (71.4%)
- t_covergroup_autobins: FAIL (hardcoded 100%)

**After**: 40/56 tests passing (71.4%)  
- t_covergroup_autobins: FAIL (partial support - 2/5 scenarios work)
- Progress: Basic auto-bins working, but full test requires option support

## Next Steps

### Priority 1 - Enable Covergroup-Level Options

To fix CG2 and CG5 scenarios:

1. **Modify Parser** (`src/verilog.y`):
   - Convert `AstCgOptionAssign` to `AstCoverOption`
   - Add to covergroup's option list

2. **Modify V3Width** (`src/V3Width.cpp`):
   - Don't delete `AstCoverOption` nodes
   - Process and validate them

3. **Modify V3CoverageFunctional**:
   - Add `getCovergroupOptions()` function
   - Check covergroup options in `getAutoBinMax()`

### Priority 2 - Respect Ignore/Illegal Bins

To fix CG3 scenario:

1. **Modify `createImplicitAutoBins()`**:
   - Scan existing bins for ignore_bins/illegal_bins
   - Extract excluded values/ranges
   - Skip excluded values when creating auto bins
   - Adjust total bin count

### Priority 3 - Other Test Failures

After autobins fully working, address other failures:
- t_covergroup_static_coverage (type-level coverage aggregation)
- Sample with arguments (3 tests)
- Covergroup extends (2 tests)

## Conclusion

Implemented core automatic bins functionality - sufficient for typical use cases with default auto_bin_max=64. Full IEEE compliance requires covergroup-level option support and respect for ignore/illegal bins during auto-creation.

**Current capability**: ~60% of automatic bins feature (default case works)
**Remaining work**: ~40% (option propagation and bin filtering)
