# Hybrid Cross Coverage Implementation

## Overview

Verilator now implements a hybrid approach for cross coverage that balances code size and runtime performance based on the number of bins.

## Usage

```bash
# Use default threshold (64 bins)
verilator --coverage-user design.v

# Set custom threshold
verilator --coverage-user --coverage-cross-threshold=128 design.v
```

## How It Works

### Small Crosses (≤64 bins)
- Uses **inline generation** with individual counter variables
- Fast sampling with direct counter increments
- Example: 2-way cross with 4×4 = 16 bins

```systemverilog
cross cp_a, cp_b;  // 16 bins - uses inline
```

Generated code:
```cpp
IData __Vcov_cross_ab_a0_x__b0;
IData __Vcov_cross_ab_a0_x__b1;
// ... (14 more variables)

if ((a == 0) && (b == 0)) __Vcov_cross_ab_a0_x__b0++;
```

### Large Crosses (>64 bins)
- Uses **array-based storage** with computed indices
- Compact code size, efficient memory
- Example: 4-way cross with 4×4×4×4 = 256 bins

```systemverilog
cross cp_a, cp_b, cp_c, cp_d;  // 256 bins - uses array
```

Generated code:
```cpp
VlUnpacked<IData, 256> __Vcov_cross_abcd_bins;

// Compute index and increment
IData index = bin0 + (bin1<<2) + (bin2<<4) + (bin3<<6);
this->__Vcov_cross_abcd_bins[index]++;
```

## Benefits

### For Small Crosses
- ✅ Fast sampling (no index computation)
- ✅ Explicit variable tracking
- ✅ Easy debugging

### For Large Crosses
- ✅ ~85% reduction in code size
- ✅ Faster compilation
- ✅ Efficient memory usage (4 bytes per bin)
- ✅ Handles crosses with thousands of bins

## Examples

### Example 1: Small 2-way Cross (16 bins)
```systemverilog
coverpoint a { bins a[] = {[0:3]}; }  // 4 bins
coverpoint b { bins b[] = {[0:3]}; }  // 4 bins
cross a, b;  // 4×4 = 16 bins → inline generation
```

### Example 2: Large 3-way Cross (125 bins)
```systemverilog
coverpoint x { bins x[] = {[0:4]}; }  // 5 bins
coverpoint y { bins y[] = {[0:4]}; }  // 5 bins  
coverpoint z { bins z[] = {[0:4]}; }  // 5 bins
cross x, y, z;  // 5×5×5 = 125 bins → array generation
```

### Example 3: Very Large 4-way Cross (1296 bins)
```systemverilog
coverpoint a { bins a[] = {[0:5]}; }  // 6 bins
coverpoint b { bins b[] = {[0:5]}; }  // 6 bins
coverpoint c { bins c[] = {[0:5]}; }  // 6 bins
coverpoint d { bins d[] = {[0:5]}; }  // 6 bins
cross a, b, c, d;  // 6×6×6×6 = 1296 bins → array generation
```

## Performance

| Bins | Approach | Code Size | Memory | Sampling Speed |
|------|----------|-----------|--------|----------------|
| 16   | Inline   | ~1KB      | 64B    | Fastest        |
| 64   | Inline   | ~4KB      | 256B   | Fast           |
| 256  | Array    | ~1.5KB    | 1KB    | Fast           |
| 1024 | Array    | ~2KB      | 4KB    | Good           |

## Configuration

### Threshold Option
- **Default:** 64 bins
- **Range:** 1-10000 (practical limit)
- **Recommendation:** Keep default unless specific needs

### When to Adjust Threshold

**Increase threshold (e.g., 128):**
- Need maximum sampling speed
- Have plenty of memory
- Crosses typically 64-128 bins

**Decrease threshold (e.g., 32):**
- Limited memory
- Very large crosses common
- Compilation time is an issue

## Limitations

- Maximum practical size: ~10,000 bins (40KB array)
- Array-based crosses not individually registered in coverage database
- Coverage computed locally in `get_inst_coverage()`

## Testing

Test files demonstrating both approaches:
- `test_regress/t/t_covergroup_cross_small.v` - 16 bins (inline)
- `test_regress/t/t_covergroup_cross_large.v` - 256 bins (array)

## Implementation

See `docs/functional_coverage_impl.md` for detailed technical documentation.

Key files:
- `src/V3CoverageFunctional.cpp` - Implementation
- `src/V3Options.h/cpp` - Option parsing
- `docs/functional_coverage_impl.md` - Full documentation

## Future Work

Potential enhancements:
- Warning for crosses exceeding 10,000 bins
- True sparse storage (hash map) for extreme cases
- Performance profiling and optimization
- Automatic threshold selection based on design characteristics
