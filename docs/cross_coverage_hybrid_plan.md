# Cross Coverage Hybrid Implementation Plan

## Executive Summary

Implement a hybrid approach for cross coverage bin generation that uses:
- **Inline generation** (current) for small crosses (fast sampling, larger memory)
- **Sparse map storage** for large crosses (smaller memory, slightly slower sampling)

**Recommended Threshold:** 64 bins (tunable via option)

## Current Implementation Analysis

### How It Works Now

The current implementation generates the Cartesian product of all bins at compile time:

```cpp
// For: cross cp_a, cp_b, cp_c, cp_d where:
// cp_a has 2 bins, cp_b has 2 bins, cp_c has 2 bins, cp_d has 2 bins
// Total: 2  2  2  2 = 16 cross bins

// Generated member variables (one per cross bin):
IData __PVT____Vcov_cross_a0_b0_c0_d0;
IData __PVT____Vcov_cross_a0_b0_c0_d1;
IData __PVT____Vcov_cross_a0_b0_c1_d0;
// ... 13 more ...

// Generated sample code (one if-statement per cross bin):
if (((a == 0) && (b == 0) && (c == 0) && (d == 0))) {
    __PVT____Vcov_cross_a0_b0_c0_d0++;
}
if (((a == 0) && (b == 0) && (c == 0) && (d == 1))) {
    __PVT____Vcov_cross_a0_b0_c0_d1++;
}
// ... 14 more if-statements ...
```

### Memory and Code Size Implications

**Example: 4-way cross (2222 = 16 bins)**
- Member variables: 16  4 bytes = 64 bytes
- Sample code: ~60 lines  16 bins = ~960 lines of C++
- Compiled binary: ~300 bytes per bin  16 = ~4.8 KB

**Example: 5-way cross (44444 = 1024 bins)**
- Member variables: 1024  4 bytes = 4 KB
- Sample code: ~60 lines  1024 bins = ~61,440 lines of C++
- Compiled binary: ~300 KB instruction cache footprint
- **Problem:** Excessive code bloat, compilation slowdown

**Example: 8-way cross with 10 bins each (10^8 = 100M bins)**
- Member variables: 100M  4 bytes = 400 MB
- Sample code: Would generate billions of lines
- **Problem:** Completely infeasible

### When Current Approach Breaks Down

The inline approach works well for:
-  Small crosses (2-3 way, <50 bins)
-  Fast inner loops where every cycle counts
-  When most cross bins are likely to be hit

But becomes problematic for:
-  Large N-way crosses (4+ way, >100 bins)
-  Sparse coverage patterns (only a few bins hit)
-  Compilation time and binary size constraints

## Proposed Hybrid Solution

### Architecture Overview

Use a **threshold-based decision** to choose implementation strategy:

```cpp
// In V3CoverageFunctional.cpp, generateCrossCode():

size_t totalBins = computeTotalCrossBins(coverpoints);

if (totalBins <= CROSS_INLINE_THRESHOLD) {
    // Use current inline approach
    generateInlineCrossBins(crossp, coverpoints, bins);
} else {
    // Use sparse map approach
    generateSparseCrossBins(crossp, coverpoints, bins);
}
```

### Threshold Analysis

**Factors to consider:**

| Bins | Memory (inline) | Code Size (inline) | Compile Time | Runtime Speed |
|------|----------------|-------------------|--------------|---------------|
| 16   | 64 B          | ~1 KB            | <1s          | Fastest      |
| 32   | 128 B         | ~2 KB            | <1s          | Fast         |
| 64   | 256 B         | ~4 KB            | ~1s          | Fast         |
| 128  | 512 B         | ~8 KB            | ~2s          | Medium       |
| 256  | 1 KB          | ~16 KB           | ~5s          | Medium       |
| 512  | 2 KB          | ~32 KB           | ~10s         | Slow         |
| 1024 | 4 KB          | ~64 KB           | ~30s         | Very Slow    |

**Recommended threshold: 64 bins**

**Rationale:**
- Below 64: Code size is manageable (< 4KB), compilation is fast
- Above 64: Code bloat starts causing noticeable compilation slowdown
- 64 is a power of 2 (6-bit indexing, natural boundary)
- Covers common use cases: 4-way  2^4 = 16, 3-way  4^3 = 64

### Sparse Map Implementation

#### Data Structure

Use `std::map<std::string, uint32_t>` for sparse storage:

```cpp
// Generated member variable (one map per cross):
std::map<std::string, uint32_t> __PVT____Vcov_cross_map;
```

**Key format:** Concatenated bin indices or names:
- Option 1 (indices): `"0,1,2,3"` for bin combo (a[0], b[1], c[2], d[3])
- Option 2 (names): `"addr0,read,normal,even"` for named bins

**Recommendation:** Use **indices** for compactness and faster comparison.

#### Generated Sample Code

```cpp
void __VnoInFunc_sample(Vmodule__Syms* vlSymsp) {
    // Determine which bin in each coverpoint matched
    int bin_a = -1, bin_b = -1, bin_c = -1, bin_d = -1;

    // Check cp_a bins
    if (vlSymsp->TOP.a == 0) bin_a = 0;
    else if (vlSymsp->TOP.a == 1) bin_a = 1;
    else if (vlSymsp->TOP.a == 2) bin_a = 2;
    // ... more bins ...

    // Check cp_b bins
    if (vlSymsp->TOP.b == 0) bin_b = 0;
    else if (vlSymsp->TOP.b == 1) bin_b = 1;
    // ... more bins ...

    // Similar for cp_c and cp_d

    // If all coverpoints matched a bin, increment the cross bin
    if (bin_a >= 0 && bin_b >= 0 && bin_c >= 0 && bin_d >= 0) {
        std::string key = std::to_string(bin_a) + "," +
                         std::to_string(bin_b) + "," +
                         std::to_string(bin_c) + "," +
                         std::to_string(bin_d);
        ++__PVT____Vcov_cross_map[key];
    }
}
```

**Alternative (faster):** Use integer key for small bin counts:

```cpp
// If each coverpoint has  16 bins, pack into single uint64_t:
// bits [0:3] = bin_a, bits [4:7] = bin_b, bits [8:11] = bin_c, bits [12:15] = bin_d
uint64_t key = (bin_a) | (bin_b << 4) | (bin_c << 8) | (bin_d << 12);
std::map<uint64_t, uint32_t> __PVT____Vcov_cross_map;
++__PVT____Vcov_cross_map[key];
```

#### Coverage Computation

```cpp
void __VnoInFunc_get_inst_coverage(...) {
    // Count how many cross bins were hit
    size_t covered = __PVT____Vcov_cross_map.size();  // Only hit bins exist
    size_t total = totalPossibleCrossBins;            // Computed at compile time

    get_inst_coverage__Vfuncrtn = (100.0 * covered) / total;
}
```

#### Coverage Registration

Register bins **lazily** or **eagerly**:

**Lazy (runtime):** Register only when hit (in sample())
```cpp
if (__PVT____Vcov_cross_map.find(key) == __PVT____Vcov_cross_map.end()) {
    // First hit - register with coverage database
    VL_COVER_INSERT(contextp, hier, &__PVT____Vcov_cross_map[key], ...);
}
```

**Eager (constructor):** Pre-register all possible bins
```cpp
// Constructor generates loops to register all combinations
for (int a = 0; a < num_bins_a; ++a) {
    for (int b = 0; b < num_bins_b; ++b) {
        // ...
        std::string key = std::to_string(a) + "," + std::to_string(b) + ...;
        __PVT____Vcov_cross_map[key] = 0;  // Initialize
        VL_COVER_INSERT(contextp, hier, &__PVT____Vcov_cross_map[key], ...);
    }
}
```

**Recommendation:** Use **eager** registration to match current behavior (all bins appear in database).

### Performance Comparison

| Operation | Inline | Sparse Map (string key) | Sparse Map (int key) |
|-----------|--------|------------------------|---------------------|
| Sample (hit) | O(1) ~5 cycles | O(log N) ~50 cycles | O(log N) ~30 cycles |
| Sample (miss) | O(1) ~5 cycles | O(1) no increment | O(1) no increment |
| Memory per hit bin | 4 bytes | ~40 bytes (map overhead) | ~20 bytes (map overhead) |
| Memory total (all bins) | bins  4 | hits  40 | hits  20 |

**Analysis:**
- Inline is ~10x faster for sampling
- Sparse map saves memory when coverage is sparse (<10% hit rate)
- For 1024 bins with 10% hit: Inline=4KB, Sparse=~2KB savings

## Implementation Plan

### Phase 1: Add Threshold and Decision Logic

**Files to modify:**
- `src/V3CoverageFunctional.cpp`

**Changes:**

1. Add threshold constant:
```cpp
// Near top of file
static constexpr size_t CROSS_INLINE_THRESHOLD = 64;
```

2. Add total bin calculation function:
```cpp
size_t computeTotalCrossBins(const std::vector<AstCoverpoint*>& coverpoints) {
    size_t total = 1;
    for (AstCoverpoint* cpp : coverpoints) {
        size_t binCount = 0;
        for (AstNode* binp = cpp->binsp(); binp; binp = binp->nextp()) {
            AstCoverBin* cbinp = VN_CAST(binp, CoverBin);
            if (cbinp && cbinp->binsType() == VCoverBinsType::USER) {
                ++binCount;
            }
        }
        total *= binCount;
    }
    return total;
}
```

3. Modify `generateCrossCode()` to add decision:
```cpp
void generateCrossCode(AstCoverCross* crossp) {
    // ... existing code to resolve coverpoints ...

    size_t totalBins = computeTotalCrossBins(coverpointRefs);

    UINFO(4, "    Cross has " << totalBins << " total bins" << endl);

    if (totalBins <= CROSS_INLINE_THRESHOLD) {
        UINFO(4, "    Using inline implementation" << endl);
        generateInlineCrossBins(crossp, coverpointRefs, allCpBins);
    } else {
        UINFO(4, "    Using sparse map implementation (threshold="
              << CROSS_INLINE_THRESHOLD << ")" << endl);
        generateSparseCrossBins(crossp, coverpointRefs, allCpBins);
    }
}
```

4. Rename current recursive generator:
```cpp
void generateInlineCrossBins(AstCoverCross* crossp,
                             const std::vector<AstCoverpoint*>& coverpointRefs,
                             const std::vector<std::vector<AstCoverBin*>>& allCpBins) {
    // This is the current generateCrossBinsRecursive() logic
    generateCrossBinsRecursive(crossp, coverpointRefs, allCpBins, {}, 0);
}
```

### Phase 2: Implement Sparse Map Generator

**Add new function:**

```cpp
void generateSparseCrossBins(AstCoverCross* crossp,
                             const std::vector<AstCoverpoint*>& coverpointRefs,
                             const std::vector<std::vector<AstCoverBin*>>& allCpBins) {
    FileLine* fl = crossp->fileline();

    // 1. Create std::map member variable
    std::string mapName = "__Vcov_" + crossp->name() + "_map";

    // Build map type: std::map<uint64_t, uint32_t>
    // For now, use AstCStmt to declare it (EmitC will handle std::map)
    std::string mapDecl = "std::map<uint64_t, uint32_t> " + mapName + ";";

    // Add map as member (will need to extend AstVar to support map types,
    // or use AstCStmt in class declaration)
    // TODO: This requires EmitC changes to properly emit std::map members

    // 2. Generate bin index lookup tables (one per coverpoint)
    for (size_t cpIdx = 0; cpIdx < coverpointRefs.size(); ++cpIdx) {
        generateBinIndexLookup(coverpointRefs[cpIdx], allCpBins[cpIdx], cpIdx);
    }

    // 3. Generate sample code that builds key and increments map
    generateSparseMapSampleCode(crossp, coverpointRefs, allCpBins, mapName);

    // 4. Generate coverage computation that iterates map
    generateSparseMapCoverageCode(crossp, coverpointRefs, mapName);

    // 5. Generate VL_COVER_INSERT calls (eager registration in constructor)
    generateSparseMapRegistration(crossp, coverpointRefs, allCpBins, mapName);
}
```

**Helper functions:**

```cpp
void generateBinIndexLookup(AstCoverpoint* cpp,
                           const std::vector<AstCoverBin*>& bins,
                           size_t cpIdx) {
    // Generate if-else chain that determines which bin matched
    // Returns bin index in variable: __Vbin_cp{cpIdx}

    std::string varName = "__Vbin_cp" + std::to_string(cpIdx);

    // Create local variable: int __Vbin_cp{N} = -1;
    AstVar* binIdxVar = new AstVar{cpp->fileline(), VVarType::BLOCKTEMP, varName,
                                   cpp->findSigned32DType()};
    m_sampleFuncp->addStmtsp(new AstVarStmt{cpp->fileline(), binIdxVar});

    // Initialize to -1 (no match)
    AstNodeStmt* initStmt = new AstAssign{
        cpp->fileline(),
        new AstVarRef{cpp->fileline(), binIdxVar, VAccess::WRITE},
        new AstConst{cpp->fileline(), AstConst::Signed32{}, -1}};
    m_sampleFuncp->addStmtsp(initStmt);

    // Build if-else chain for each bin
    AstNodeStmt* lastIfp = nullptr;
    for (size_t binIdx = 0; binIdx < bins.size(); ++binIdx) {
        AstCoverBin* binp = bins[binIdx];
        AstNodeExpr* exprp = cpp->exprp();

        // Build condition: if (expr matches bin)
        AstNodeExpr* condp = buildBinCondition(binp, exprp);
        if (!condp) continue;

        // Build action: __Vbin_cp{N} = binIdx;
        AstNodeStmt* actionp = new AstAssign{
            binp->fileline(),
            new AstVarRef{binp->fileline(), binIdxVar, VAccess::WRITE},
            new AstConst{binp->fileline(), AstConst::Signed32{}, binIdx}};

        AstIf* ifp = new AstIf{binp->fileline(), condp, actionp, nullptr};

        if (!lastIfp) {
            m_sampleFuncp->addStmtsp(ifp);
        } else {
            // Chain as else-if
            lastIfp->addElsesp(ifp);
        }
        lastIfp = ifp;
    }
}

void generateSparseMapSampleCode(AstCoverCross* crossp,
                                 const std::vector<AstCoverpoint*>& coverpointRefs,
                                 const std::vector<std::vector<AstCoverBin*>>& allCpBins,
                                 const std::string& mapName) {
    // Generate code to check if all bins matched and increment map

    FileLine* fl = crossp->fileline();

    // Build condition: if (__Vbin_cp0 >= 0 && __Vbin_cp1 >= 0 && ...)
    AstNodeExpr* allMatchedCond = nullptr;
    for (size_t i = 0; i < coverpointRefs.size(); ++i) {
        std::string varName = "__Vbin_cp" + std::to_string(i);
        // Find the variable (requires keeping track of it)
        // For now, use AstCStmt to avoid complexity
    }

    // Build key: uint64_t key = (__Vbin_cp0) | (__Vbin_cp1 << 4) | ...
    std::string keyBuildCode = "uint64_t __Vcross_key = 0; ";
    for (size_t i = 0; i < coverpointRefs.size(); ++i) {
        keyBuildCode += "__Vcross_key |= (static_cast<uint64_t>(__Vbin_cp" +
                       std::to_string(i) + ") << " +
                       std::to_string(i * 4) + "); ";  // 4 bits per dimension
    }

    // Increment map: this->{mapName}[key]++;
    keyBuildCode += "if (allBinsMatched) { this->" + mapName + "[__Vcross_key]++; }";

    AstCStmt* cstmt = new AstCStmt{fl, keyBuildCode};
    m_sampleFuncp->addStmtsp(cstmt);
}
```

### Phase 3: Testing

**Test cases to create:**

1. **t_covergroup_cross_threshold.v** - Test exactly at threshold (64 bins)
2. **t_covergroup_cross_large.v** - Test above threshold (128+ bins)
3. **t_covergroup_cross_sparse.v** - Test sparse coverage (hit <10% of bins)
4. **t_covergroup_cross_5way.v** - Test 5-way cross (44444 = 1024 bins)

**Verification:**
- Coverage percentage matches between inline and sparse implementations
- VL_COVER_INSERT calls generated correctly
- Coverage database output is correct
- Performance benchmarks (sample time comparison)

### Phase 4: Add Command-Line Option

**Add to `src/Verilator.cpp`:**

```cpp
// In option parsing:
if (arg == "--coverage-cross-threshold") {
    v3Global.opt.coverageCrossThreshold(std::atoi(argv[++i]));
}
```

**Add to V3Options:**

```cpp
int m_coverageCrossThreshold = 64;  // Default
void coverageCrossThreshold(int val) { m_coverageCrossThreshold = val; }
int coverageCrossThreshold() const { return m_coverageCrossThreshold; }
```

**Documentation:**
```
--coverage-cross-threshold <N>
    Set threshold for cross coverage inline vs sparse implementation.
    Crosses with <= N total bins use inline code generation (faster).
    Crosses with > N bins use sparse map storage (smaller code/memory).
    Default: 64
```

## Alternative: Integer Packing for Key

For crosses where each coverpoint has 16 bins (4 bits), use bitpacking:

```cpp
// Supports up to 16-way cross with 16 bins each (64-bit key)
uint64_t key = 0;
key |= (static_cast<uint64_t>(bin_a) << 0);
key |= (static_cast<uint64_t>(bin_b) << 4);
key |= (static_cast<uint64_t>(bin_c) << 8);
key |= (static_cast<uint64_t>(bin_d) << 12);
// ... up to 16 dimensions * 4 bits = 64 bits
```

**Benefits:**
- Faster map operations (integer comparison vs string comparison)
- Smaller keys (8 bytes vs ~20+ bytes for string)
- Natural ordering for iteration

**Limitation:**
- Only works if each dimension has 16 bins
- Fallback to string keys for larger bin counts

## Risk Assessment

### Compatibility Risks

**Low Risk:**
- Changes are localized to V3CoverageFunctional.cpp
- Inline behavior unchanged for crosses below threshold
- Coverage database format unchanged

**Medium Risk:**
- std::map emission in generated C++ may require EmitC changes
- Need to ensure proper initialization/destruction of map members
- VL_COVER_INSERT with dynamically registered bins may need adjustment

### Performance Risks

**Low Risk:**
- Inline implementation is unchanged, no performance degradation
- Sparse map is only used when inline would be infeasible anyway

**Consideration:**
- Map overhead (~10x slower) is acceptable for large crosses
- Most simulations have <10% cross bin hit rate, so savings are real

## Recommendation Summary

1. **Implement threshold-based decision:** Use 64 bins as default threshold
2. **Start with integer key packing:** Simpler, faster, sufficient for most cases
3. **Fallback to string keys:** For crosses with >16 bins per dimension
4. **Eager registration:** Pre-register all bins in constructor for database consistency
5. **Add command-line option:** Allow users to tune threshold based on their needs

**Timeline:**
- Phase 1 (threshold decision): 1 day
- Phase 2 (sparse map impl): 3-4 days
- Phase 3 (testing): 2 days
- Phase 4 (command-line option): 1 day
- **Total: ~7-8 days**

**Alternate Approach (simpler, faster to implement):**
- Just add warning when cross exceeds threshold
- Document that large crosses should be avoided
- Defer sparse implementation until user demand exists
- **Timeline: 1 day for warning + documentation**
