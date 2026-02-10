# SystemVerilog Functional Coverage Implementation in Verilator

## Document Overview

This document describes the implementation architecture, design decisions, and technical details of SystemVerilog functional coverage support in Verilator. It covers the AST transformation pipeline, code generation strategy, runtime infrastructure, and coverage database integration.

**Last Updated:** 2026-02-10  
**Status:** Production-ready with documented limitations

## Table of Contents

1. [Architecture Overview](#architecture-overview)
2. [AST Transformation Pipeline](#ast-transformation-pipeline)
3. [Code Generation Strategy](#code-generation-strategy)
4. [Runtime Infrastructure](#runtime-infrastructure)
5. [Coverage Database Format](#coverage-database-format)
6. [Implementation Details by Feature](#implementation-details-by-feature)
7. [Performance Considerations](#performance-considerations)
8. [Supported Features and Test Validation](#supported-features-and-test-validation)
9. [Known Limitations and Workarounds](#known-limitations-and-workarounds)

---

## Architecture Overview

### High-Level Design Philosophy

Verilator's functional coverage implementation follows these principles:

1. **Pure C++ Code Generation**: Convert SystemVerilog covergroups into efficient C++ classes with minimal runtime overhead
2. **Integration with Existing Coverage Infrastructure**: Reuse Verilator's proven coverage database format (`SystemC::Coverage-3`) and reporting tools
3. **Compile-Time Resolution**: Resolve as much as possible during Verilator compilation to minimize runtime overhead
4. **No External Dependencies**: All functional coverage logic is implemented in standard C++11 without requiring external libraries

### Component Architecture

```
┌─────────────────────────────────────────────────────────────┐
│  SystemVerilog Source Code (covergroups, bins, etc.)       │
└─────────────────────┬───────────────────────────────────────┘
                      │
                      v
┌─────────────────────────────────────────────────────────────┐
│  V3Parse.y - Parser                                         │
│  Creates: AstCovergroup, AstCoverpoint, AstCoverBin, etc.  │
└─────────────────────┬───────────────────────────────────────┘
                      │
                      v
┌─────────────────────────────────────────────────────────────┐
│  V3CoverageFunctional.cpp - AST Transformation              │
│  - Generates bin counter variables                          │
│  - Generates sample() method implementation                 │
│  - Generates get_inst_coverage() method                     │
│  - Generates VL_COVER_INSERT() calls                        │
└─────────────────────┬───────────────────────────────────────┘
                      │
                      v
┌─────────────────────────────────────────────────────────────┐
│  V3EmitC - Code Generator                                   │
│  Emits: C++ classes for covergroups                         │
└─────────────────────┬───────────────────────────────────────┘
                      │
                      v
┌─────────────────────────────────────────────────────────────┐
│  Runtime (verilated_cov.cpp, verilated_funccov.h)          │
│  - VL_COVER_INSERT macro registers bins                    │
│  - Coverage database accumulation                           │
│  - Coverage reporting via verilator_coverage tool           │
└─────────────────────────────────────────────────────────────┘
```

---

## AST Transformation Pipeline

### Overview

The `V3CoverageFunctional` pass runs after type resolution and before code emission. It transforms covergroup AST nodes into executable code structures.

### Key AST Node Types

| AST Node | Purpose | Created By |
|----------|---------|------------|
| `AstClass` (with `isCovergroup()=true`) | Represents a covergroup type | Parser |
| `AstCovergroup` | Metadata node for clocking events | Parser |
| `AstCoverpoint` | Coverage point within a covergroup | Parser |
| `AstCoverBin` | Bin definition within a coverpoint | Parser |
| `AstCoverCross` | Cross coverage between coverpoints | Parser |

### Transformation Stages

#### Stage 1: Covergroup Discovery

```cpp
void visit(AstClass* nodep) override {
    if (nodep->isCovergroup()) {
        // Initialize state for this covergroup
        m_covergroupp = nodep;
        m_coverpoints.clear();
        m_coverCrosses.clear();
        m_binInfos.clear();
        
        // Process all members
        iterateChildren(nodep);
        
        // Generate code
        processCovergroup();
    }
}
```

**What happens:**
- Identifies classes marked as covergroups
- Collects all coverpoints and crosses
- Prepares for code generation

#### Stage 2: Bin Variable Generation

For each bin, a counter variable is created:

```cpp
// Generated AST structure:
AstVar* binVar = new AstVar{
    fileline,
    VVarType::MEMBER,  // Member variable
    binName,           // e.g., "__Vcov_cp_state_low"
    new VBasicDTypeKwd{fileline, VBasicDTypeKwd::UINT32}  // uint32_t
};
binVar->funcLocal(false);
binVar->lifetime(VLifetime::STATIC);  // Persists across sample() calls
m_covergroupp->addMembersp(binVar);
```

**Generated C++ (example):**
```cpp
class Vmodule_cg : public VlClass {
public:
    IData/*31:0*/ __PVT____Vcov_cp_state_low;   // Bin counter
    IData/*31:0*/ __PVT____Vcov_cp_state_high;  // Bin counter
    // ...
};
```

**Key details:**
- Variables use `__PVT__` prefix (private to module)
- Type is always `IData` (32-bit unsigned integer)
- Naming convention: `__Vcov_{coverpoint}_{bin}`

#### Stage 3: Sample Method Generation

The `sample()` method body is populated with bin-matching and increment logic.

**For value bins:**
```cpp
// AST structure generated:
if (exprValue == binValue) {
    binCounter++;
}
```

**Generated C++ (example):**
```cpp
void __VnoInFunc_sample(Vmodule__Syms* __restrict vlSymsp) {
    // Check if coverpoint value matches bin range
    if ((vlSymsp->TOP__t.__PVT__state >= 0U) 
        && (vlSymsp->TOP__t.__PVT__state <= 3U)) {
        // Increment bin counter
        this->__PVT____Vcov_cp_state_low = (1U + this->__PVT____Vcov_cp_state_low);
    }
    if ((vlSymsp->TOP__t.__PVT__state >= 4U) 
        && (vlSymsp->TOP__t.__PVT__state <= 7U)) {
        this->__PVT____Vcov_cp_state_high = (1U + this->__PVT____Vcov_cp_state_high);
    }
}
```

**For transition bins:**

Transition bins require state tracking. An additional "previous value" variable is generated:

```cpp
// Generated variables:
CData/*2:0*/ __PVT____Vprev_cp_state;  // Previous value storage
IData/*31:0*/ __PVT____Vcov_cp_state_trans1;  // Transition counter
```

**Generated sample code (simple 2-value transition):**
```cpp
void __VnoInFunc_sample(Vmodule__Syms* __restrict vlSymsp) {
    // Check for transition (prev_value => current_value)
    if (((0U == (IData)(this->__PVT____Vprev_cp_state)) 
         && (1U == (IData)(vlSymsp->TOP__t.__PVT__state)))) {
        this->__PVT____Vcov_cp_state_trans1 = (1U + this->__PVT____Vcov_cp_state_trans1);
    }
    
    // Update previous value for next sample
    this->__PVT____Vprev_cp_state = vlSymsp->TOP__t.__PVT__state;
}
```

**For multi-value transition bins (e.g., `bins t = (0 => 1 => 2 => 3)`):**

A sequence state variable tracks progress through the sequence:

```cpp
// Generated variables:
CData/*1:0*/ __PVT____Vseqstate_trans_4val;  // 0=idle, 1=saw 0, 2=saw 0=>1, 3=saw 0=>1=>2
```

**Generated state machine logic:**
```cpp
// State 0: Looking for first value (0)
if ((0U == __PVT____Vseqstate_trans_4val) && (0U == current)) {
    __PVT____Vseqstate_trans_4val = 1U;  // Advance to state 1
}
// State 1: Looking for second value (1)
else if ((1U == __PVT____Vseqstate_trans_4val) && (1U == current)) {
    __PVT____Vseqstate_trans_4val = 2U;  // Advance to state 2
}
// State 2: Looking for third value (2)
else if ((2U == __PVT____Vseqstate_trans_4val) && (2U == current)) {
    __PVT____Vseqstate_trans_4val = 3U;  // Advance to state 3
}
// State 3: Looking for final value (3)
else if ((3U == __PVT____Vseqstate_trans_4val) && (3U == current)) {
    __PVT____Vcov_trans_4val++;  // Success! Hit the bin
    __PVT____Vseqstate_trans_4val = 0U;  // Reset to idle
}
// Restart logic: Mismatch resets to idle if value matches first in sequence
else if (0U == current) {
    __PVT____Vseqstate_trans_4val = 1U;  // Restart from state 1
}
else {
    __PVT____Vseqstate_trans_4val = 0U;  // Complete reset to idle
}
```

#### Stage 4: Coverage Computation Method Generation

The `get_inst_coverage()` method calculates coverage percentage:

```cpp
void __VnoInFunc_get_inst_coverage(..., double &get_inst_coverage__Vfuncrtn) {
    IData/*31:0*/ __Vcovered_count = 0;
    
    // Count bins that meet at_least threshold
    if (1U <= this->__PVT____Vcov_cp_state_low) {
        __Vcovered_count = (1U + __Vcovered_count);
    }
    if (1U <= this->__PVT____Vcov_cp_state_high) {
        __Vcovered_count = (1U + __Vcovered_count);
    }
    
    // Calculate percentage: (covered / total) * 100
    get_inst_coverage__Vfuncrtn = (100.0 * (VL_ITOR_D_I(32, __Vcovered_count) / 2.0));
}
```

**Empty covergroup handling:**

Empty covergroups (no coverpoints) return 100% per IEEE 1800 specification:

```cpp
// For empty covergroups, the assignment is modified during generation:
get_inst_coverage__Vfuncrtn = 100.0;  // No bins to miss = 100% coverage
```

#### Stage 5: Coverage Database Registration

VL_COVER_INSERT calls are generated in the constructor to register bins:

```cpp
// Generated constructor code:
Vmodule_cg::Vmodule_cg(Vmodule__Syms* symsp) {
    // ... variable initialization ...
    
    // Register each bin with coverage database
    VL_COVER_INSERT(vlSymsp->_vm_contextp__->coveragep(), 
                   "cg.cp_state.low",           // Hierarchical name
                   &(this->__PVT____Vcov_cp_state_low),  // Pointer to counter
                   "page", "v_funccov/cg",      // Page type for reporting
                   "filename", "test.v",        // Source location
                   "lineno", "15",
                   "column", "10",
                   "bin", "low");               // Bin name
}
```

---

## Code Generation Strategy

### C++ Class Structure

Each covergroup becomes a C++ class derived from `VlClass`:

```cpp
class Vmodule_t__03a__03acg : public virtual VlClass {
  public:
    // Member variables (bins, previous values, state vars)
    IData/*31:0*/ __PVT____Vcov_cp_state_bin1;
    CData/*2:0*/ __PVT____Vprev_cp_state;
    
    // Option structures (IEEE 1800-2023 Section 19.6)
    Vmodule_vl_covergroup_options_t__struct__0 __PVT__option;
    Vmodule_vl_covergroup_type_options_t__struct__0 __PVT__type_option;
    
    // Methods (IEEE 1800-2023 Section 19.9)
    void __VnoInFunc_sample(Vmodule__Syms* vlSymsp);
    void __VnoInFunc_get_inst_coverage(..., double& retval);
    void __VnoInFunc_set_inst_name(Vmodule__Syms* vlSymsp, std::string name);
    void __VnoInFunc_start(Vmodule__Syms* vlSymsp) {}  // No-op
    void __VnoInFunc_stop(Vmodule__Syms* vlSymsp) {}   // No-op
    
    // Constructor/Destructor
    Vmodule_t__03a__03acg(Vmodule__Syms* vlSymsp);
    ~Vmodule_t__03a__03acg() {}
};
```

### Method Implementation Patterns

**sample() - No Arguments:**
```cpp
void __VnoInFunc_sample(Vmodule__Syms* __restrict vlSymsp) {
    // Access coverpoint via symbol table
    auto current = vlSymsp->TOP__t.__PVT__state;
    
    // Bin matching logic
    if (current == 0) { this->__PVT____Vcov_bin0++; }
    if (current == 1) { this->__PVT____Vcov_bin1++; }
}
```

**sample() - With Arguments (via function sample):**

When `covergroup cg with function sample(int arg);` is specified:

```cpp
void __VnoInFunc_sample(Vmodule__Syms* __restrict vlSymsp, IData arg) {
    // Use argument instead of accessing module state
    if (arg == 0) { this->__PVT____Vcov_bin0++; }
    if (arg == 1) { this->__PVT____Vcov_bin1++; }
}
```

### Cross Coverage Generation

Cross coverage generates the Cartesian product of bin combinations. Verilator uses an **array-based approach** for all cross coverage to ensure consistent behavior and efficient memory usage.

#### Array-Based Implementation Strategy

All cross coverage uses **array-based storage** with computed indices:

- **Compact code size**: Single array per cross, computed index at runtime
- **Efficient memory**: 4 bytes (uint32_t) per possible bin combination
- **Scalable**: Handles small (2×2=4 bins) to large (10×10×10×10=10,000 bins) crosses uniformly
- **Consistent behavior**: Same code generation pattern for all cross coverage

#### Example: Small 2-Way Cross

For a 2-way cross with 2×2=4 bins:

```cpp
// Single unpacked array for all bins
VlUnpacked<IData/*31:0*/, 4> __PVT____Vcov_cross_ab_bins;

// Sample code with computed index
void __VnoInFunc_sample(...) {
    // Step 1: Determine which bin matched for each coverpoint
    IData __Vbin_cp0 = 0xffffffffU;  // Start with "no match"
    if (a >= 0 && a <= 3) {
        __Vbin_cp0 = 0;  // Matched bin a0
    } else if (a >= 4 && a <= 7) {
        __Vbin_cp0 = 1;  // Matched bin a1
    }
    
    IData __Vbin_cp1 = 0xffffffffU;
    if (b >= 0 && b <= 3) {
        __Vbin_cp1 = 0;  // Matched bin b0
    } else if (b >= 4 && b <= 7) {
        __Vbin_cp1 = 1;  // Matched bin b1
    }
    
    // Step 2: Check if all coverpoints matched
    if (__Vbin_cp0 != 0xffffffffU && __Vbin_cp1 != 0xffffffffU) {
        // Step 3: Calculate linear array index
        IData __Vindex = __Vbin_cp0 + (__Vbin_cp1 * 2);
        
        // Step 4: Increment array element
        this->__PVT____Vcov_cross_ab_bins[__Vindex]++;
    }
}

// Coverage calculation (loop through array)
void __VnoInFunc_get_inst_coverage(...) {
    IData __Vcovered_count = 0;
    for (size_t __Vi = 0; __Vi < 4; ++__Vi) {
        if (this->__PVT____Vcov_cross_ab_bins[__Vi] >= 1) {
            __Vcovered_count++;
        }
    }
}
```

#### Example: Large 4-Way Cross

For a 4-way cross with 4×4×4×4=256 bins:

```cpp
// Single unpacked array for all bins
VlUnpacked<IData/*31:0*/, 256> __PVT____Vcov_cross_abcd_bins;

// Sample code with computed index
void __VnoInFunc_sample(...) {
    // Step 1: Determine which bin matched for each coverpoint
    IData __Vbin_cp0 = 0xffffffffU;  // Start with "no match"
    if (a >= 0 && a <= 3) {
        __Vbin_cp0 = 0;  // Matched bin a0
    } else if (a >= 4 && a <= 7) {
        __Vbin_cp0 = 1;  // Matched bin a1
    }
    // ... similar for __Vbin_cp1, __Vbin_cp2, __Vbin_cp3
    
    // Step 2: Calculate linear array index
    // Formula: index = bin0 + bin1*size0 + bin2*size0*size1 + bin3*size0*size1*size2
    IData __Vindex = (__Vbin_cp0 
                    + (__Vbin_cp1 << 2)   // × 4
                    + (__Vbin_cp2 << 4)   // × 16
                    + (__Vbin_cp3 << 6)); // × 64
    
    // Step 3: Increment array element
    this->__PVT____Vcov_cross_abcd_bins[__Vindex]++;
}

// Coverage calculation (loop through array)
void __VnoInFunc_get_inst_coverage(...) {
    IData __Vcovered_count = 0;
    // Count non-zero entries meeting atLeast threshold
    for (size_t __Vi = 0; __Vi < 256; ++__Vi) {
        if (this->__PVT____Vcov_cross_abcd_bins[__Vi] >= 1) {
            __Vcovered_count++;
        }
    }
}
```

#### Index Calculation Formula

The linear array index is calculated using a multi-dimensional to single-dimensional mapping:

```
index = bin[0] + bin[1] × size[0] + bin[2] × size[0] × size[1] + ...
```

For optimization, multiplications by powers of 2 are converted to bit shifts:
- `× 4` → `<< 2`
- `× 16` → `<< 4`
- `× 64` → `<< 6`

#### Implementation Details

**Threshold Selection Rationale:**
- Below 64 bins: Code size is manageable (typically <2-4KB)
- Above 64 bins: Compilation time increases significantly with inline approach
- Memory comparison for 256-bin cross:
  - Inline: 256 × 4 bytes = 1KB (variables) + ~10KB (code)
  - Array: 256 × 4 bytes = 1KB (array) + ~0.5KB (code)

**Array Index Calculation:**
Uses bit shifts for power-of-2 sizes (optimized to multiply for non-power-of-2):
- `bin0 + (bin1 << log2(size0)) + (bin2 << log2(size0*size1)) + ...`
- Compiler optimizes shifts to multiplies when needed

**Coverage Registration:**
- Inline bins: Each variable registered via `VL_COVER_INSERT`
- Array bins: Skipped (array elements not individually tracked in coverage database)
- Coverage percentage computed locally in `get_inst_coverage()`

**Memory Overhead:**
- Maximum practical size: ~10,000 bins (40KB array)
- Larger crosses may hit compilation limits or cause performance issues

**Implementation Location:**
- `V3CoverageFunctional.cpp::generateCrossCode()` - threshold decision logic
- `V3CoverageFunctional.cpp::generateInlineCrossBins()` - inline generation
- `V3CoverageFunctional.cpp::generateSparseCrossBins()` - array generation
- `V3Options.h/cpp` - `--coverage-cross-threshold` option parsing

---

## Runtime Infrastructure

### Header Files

**verilated_cov.h:**
- Defines `VL_COVER_INSERT` macro for registering coverage points
- Provides `VerilatedCovContext` class for coverage database management
- Used by both line/toggle coverage and functional coverage

**verilated_funccov.h:**
- Optional runtime helper classes (`VerilatedCoverBin`, `VerilatedCoverpoint`, etc.)
- Currently **not used** by generated code (pure code-generation approach preferred)
- Kept for potential future runtime-heavy implementations or user extensions

### VL_COVER_INSERT Macro

The macro registers a coverage point with the database:

```cpp
#define VL_COVER_INSERT(covcontextp, name, countp, ...) \
    do { \
        auto const ccontextp = covcontextp; \
        ccontextp->_inserti(countp);          // Register counter pointer
        ccontextp->_insertf(__FILE__, __LINE__); // Source location
        ccontextp->_insertp("hier", name, __VA_ARGS__); // Key-value pairs
    } while (false)
```

**Key-value pairs used for functional coverage:**

| Key | Value | Purpose |
|-----|-------|---------|
| `hier` | `"cg.cp_state.low"` | Hierarchical name for reporting |
| `page` | `"v_funccov/cg"` | Type identifier (prefix `v_funccov` marks functional coverage) |
| `filename` | `"test.v"` | Source file location |
| `lineno` | `"15"` | Source line number |
| `column` | `"10"` | Source column |
| `bin` | `"low"` | Bin name |

### Coverage Database Internals

**Data Structure:**

Coverage points are stored in a deduplicated format:

```cpp
class VerilatedCovImp {
    // Key and value strings are indexed to save memory
    ValueIndexMap m_valueIndexes;  // string -> unique ID
    IndexValueMap m_indexValues;   // unique ID -> string
    
    // Each coverage item stores key-value pairs as integer indices
    ItemList m_items;  // List of VerilatedCovImpItem*
};
```

**Registration Flow:**

1. Constructor calls `VL_COVER_INSERT()`
2. Macro calls `ccontextp->_inserti(countp)` - stores counter pointer
3. Macro calls `ccontextp->_insertf(__FILE__, __LINE__)` - stores source location
4. Macro calls `ccontextp->_insertp("key", "value", ...)` - stores metadata as key-value pairs
5. All strings are deduplicated via `valueIndex()` method

---

## Coverage Database Format

### SystemC::Coverage-3 Format

Verilator uses the `SystemC::Coverage-3` format (also known as SystemC-4 internally) for all coverage output. This is a simple text-based format that is backward compatible with SystemC-3.

**File Structure:**

```
# SystemC::Coverage-3
C 'key1val1key2val2...' count
C 'key1val1key2val2...' count
...
```

**Line Format:**

```
C '<compact_key_value_pairs>' <hit_count>
```

**Key-Value Encoding:**

Keys and values are concatenated without delimiters. Single-letter keys are used:

| Key | Full Name | Purpose |
|-----|-----------|---------|
| `f` | filename | Source file path |
| `l` | lineno | Line number |
| `n` | column | Column number |
| `t` | type | Coverage type |
| `page` | page | Type and hierarchy info |
| `o` | comment | Description |
| `h` | hier | Hierarchical instance path |
| `bin` | bin | Bin name (functional coverage only) |

**Example Functional Coverage Entry:**

```
C 'ftest.vl10n5tlinepagev_funccov/cgocoverpointbin低' 42
```

Decoded:
- `f` = `test.v` (filename)
- `l` = `10` (line number)
- `n` = `5` (column)
- `t` = `line` (type - actually extracted from page)
- `page` = `v_funccov/cg` (functional coverage page)
- `o` = `coverpoint` (comment)
- `bin` = `low` (bin name)
- Count = `42` (hits)

**Functional Coverage Type Extraction:**

The `page` field format `v_funccov/<covergroup>` allows tools to identify functional coverage:
- Prefix `v_` indicates Verilator coverage
- Segment `funccov` identifies functional coverage type
- Remaining path is covergroup name

### Integration with verilator_coverage Tool

The `verilator_coverage` tool processes `.dat` files:

```bash
# Annotate source with coverage
$ verilator_coverage --annotate coverage_report coverage.dat

# Generate merged database
$ verilator_coverage --write merged.dat cov1.dat cov2.dat

# Generate info format for lcov
$ verilator_coverage --write-info coverage.info coverage.dat
```

**Functional coverage entries** are treated as user coverage with type extracted from the `page` field. The tool:
1. Parses the `v_funccov/<name>` prefix
2. Groups bins by covergroup
3. Calculates coverage percentages by counting bins with `count >= at_least`
4. Generates HTML reports with functional coverage sections

---

## Implementation Details by Feature

This section provides detailed implementation notes for each major functional coverage feature.

---

### Feature: Automatic Sampling with Clocking Events

**SystemVerilog:**
```systemverilog
covergroup cg @(posedge clk);
    cp_data: coverpoint data {
        bins low  = {[0:3]};
        bins high = {[4:7]};
    }
endgroup

cg cg_inst = new;  // No manual sample() call needed
```

**Implementation:**

Automatic sampling is **fully supported** in both `--timing` and `--no-timing` modes.

**AST Transformation (V3CoverageFunctional.cpp):**

1. Parser creates `AstCovergroup` node containing the clocking event (`AstSenTree`)
2. V3CoverageFunctional extracts the event and stores it in a global map: `s_covergroupEvents`
3. The event is associated with the covergroup's `AstClass` for later retrieval

**Active Block Injection (V3Active.cpp):**

The `CovergroupSamplingVisitor` runs after the main `ActiveVisitor` to inject automatic sampling:

1. **First pass**: Collects all `sample()` CFuncs from covergroup class scopes
2. **Second pass**: For each covergroup instance variable in module scope:
   - Retrieves the clocking event from `s_covergroupEvents`
   - Creates an `AstCMethodCall` to the covergroup's `sample()` method
   - Injects the call into the appropriate active domain matching the event

**Generated Code:**
```cpp
// In the active block triggered by posedge clk:
void Vt___nba_sequent__TOP__t__0(Vt_t* vlSelf) {
    // Automatic sample() call injected here
    VL_NULL_CHECK(vlSelfRef.__PVT__cg_inst, "file.v", 23)->__VnoInFunc_sample(vlSymsp);
    
    // Rest of user's always block code...
}
```

**Compatibility:**
- **`--no-timing`**: Sample call injected into NBA (non-blocking assignment) region
- **`--timing`**: Sample call injected into appropriate timing domain with coroutine support
- Both modes use the same AST transformation; V3Timing handles the scheduling differences

**Runtime:** O(1) overhead per clock edge - just a method call

---

### Feature: Basic Bins

**SystemVerilog:**
```systemverilog
covergroup cg;
    coverpoint state {
        bins low  = {[0:3]};
        bins high = {[4:7]};
    }
endgroup
```

**AST Transformation:**
1. Create counter variables: `__Vcov_cp_state_low`, `__Vcov_cp_state_high`
2. Generate range check in sample():
   ```cpp
   if ((state >= 0) && (state <= 3)) __Vcov_cp_state_low++;
   if ((state >= 4) && (state <= 7)) __Vcov_cp_state_high++;
   ```
3. Register bins in constructor with VL_COVER_INSERT

**Runtime:** O(1) per sample, 4 bytes per bin

---

### Feature: Array Bins

**SystemVerilog:**
```systemverilog
coverpoint state {
    bins values[] = {[0:7]};  // Creates bins: values[0], values[1], ..., values[7]
}
```

**AST Transformation:**
1. Expand `[]` notation into individual bins during AST transformation
2. Generate 8 counter variables: `__Vcov_cp_state_values_0` through `__Vcov_cp_state_values_7`
3. Generate exact-match checks:
   ```cpp
   if (state == 0) __Vcov_cp_state_values_0++;
   if (state == 1) __Vcov_cp_state_values_1++;
   // ... up to 7
   ```

**Runtime:** O(N) checks per sample where N = number of bins

---

### Feature: Wildcard Bins

**SystemVerilog:**
```systemverilog
coverpoint opcode {
    wildcard bins loads  = {4'b00??};  // Matches 0000, 0001, 0010, 0011
    wildcard bins stores = {4'b01??};
}
```

**AST Transformation:**
1. Convert wildcard pattern to mask and value:
   - Pattern `4'b00??` becomes: value=`0000`, mask=`1100` (1=care, 0=don't care)
2. Generate bitwise check:
   ```cpp
   if ((opcode & 0xC) == 0x0) __Vcov_cp_opcode_loads++;   // Check bits [3:2] == 00
   if ((opcode & 0xC) == 0x4) __Vcov_cp_opcode_stores++;  // Check bits [3:2] == 01
   ```

**Runtime:** O(1) per sample, efficient bit masking

---

### Feature: Default Bins

**SystemVerilog:**
```systemverilog
coverpoint state {
    bins defined = {0, 1, 2};
    bins others = default;  // Catches all other values
}
```

**AST Transformation:**
1. Generate explicit checks for defined bins
2. Generate "catch-all" else clause for default bin:
   ```cpp
   if (state == 0 || state == 1 || state == 2) {
       __Vcov_cp_state_defined++;
   } else {
       __Vcov_cp_state_others++;  // Catches everything else
   }
   ```

**Runtime:** O(1) guaranteed by if-else structure

---

### Feature: Ignore and Illegal Bins

**SystemVerilog:**
```systemverilog
coverpoint value {
    bins valid[] = {[0:10]};
    ignore_bins unused = {11, 12, 13};  // Don't track, don't count
    illegal_bins bad = {[14:15]};       // Error if seen
}
```

**AST Transformation:**

**Ignore bins:**
- No counter variable generated
- No sample code generated
- Not included in coverage percentage denominator

**Illegal bins:**
- Generate check with runtime error:
  ```cpp
  if (value >= 14 && value <= 15) {
      VL_FATAL_MT(__FILE__, __LINE__, "", 
                  "Illegal bin 'bad' hit in coverpoint 'cp_value'");
  }
  ```

**Runtime:** Illegal bins add O(1) check, ignore bins add nothing

---

### Feature: Cross Coverage

**SystemVerilog:**
```systemverilog
covergroup cg;
    cp_a: coverpoint a { bins a0 = {0}; bins a1 = {1}; }
    cp_b: coverpoint b { bins b0 = {0}; bins b1 = {1}; }
    cross_ab: cross cp_a, cp_b;  // 2×2 = 4 bins
endgroup
```

**AST Transformation:**

Verilator uses an **array-based approach** for all cross coverage:

1. Generate a single `VlUnpacked` array to hold counters for all bin combinations
2. At sample time, determine which bin each coverpoint matched (if any)
3. Calculate a linear array index from the bin indices
4. Increment the appropriate array element

```cpp
// Member variable: array for all combinations
VlUnpacked<IData/*31:0*/, 4> __Vcov_cross_ab_bins;

// Sample code
void sample() {
    // Step 1: Determine bin indices for each coverpoint
    IData __Vbin_cp_a = 0xffffffffU;  // No match initially
    if (a == 0) __Vbin_cp_a = 0;      // Matched bin a0
    else if (a == 1) __Vbin_cp_a = 1; // Matched bin a1
    
    IData __Vbin_cp_b = 0xffffffffU;
    if (b == 0) __Vbin_cp_b = 0;      // Matched bin b0
    else if (b == 1) __Vbin_cp_b = 1; // Matched bin b1
    
    // Step 2: Check if all coverpoints matched
    if (__Vbin_cp_a != 0xffffffffU && __Vbin_cp_b != 0xffffffffU) {
        // Step 3: Calculate array index
        IData __Vindex = __Vbin_cp_a + (__Vbin_cp_b * 2);
        
        // Step 4: Increment counter
        this->__Vcov_cross_ab_bins[__Vindex]++;
    }
}
```

**Advantages:** Fast sampling (direct increments), explicit variable tracking  
**Disadvantages:** Large code size for many bins

#### Large Crosses (>64 bins): Array-Based Storage

For a 4-way cross: `cross cp_a, cp_b, cp_c, cp_d;` (256 bins)

1. Generate single unpacked array
2. Compute linear index from bin indices
3. Increment array element

```cpp
// Single array for all cross bins
VlUnpacked<IData, 256> __Vcov_cross_abcd_bins;

// Sample code
void sample() {
    // Determine which bin matched for each coverpoint
    IData __Vbin_cp0 = (a >= 0 && a <= 3) ? 0 :
                       (a >= 4 && a <= 7) ? 1 : 0xFFFFFFFF;
    IData __Vbin_cp1 = /* similar for b */;
    IData __Vbin_cp2 = /* similar for c */;
    IData __Vbin_cp3 = /* similar for d */;
    
    // Calculate array index: bin0 + bin1×4 + bin2×16 + bin3×64
    IData __Vindex = __Vbin_cp0 
                   + (__Vbin_cp1 << 2)   // × 4
                   + (__Vbin_cp2 << 4)   // × 16
                   + (__Vbin_cp3 << 6);  // × 64
    
    // Increment array element
    this->__Vcov_cross_abcd_bins[__Vindex]++;
}

// Coverage computation loops through array
void get_inst_coverage() {
    for (size_t i = 0; i < 256; ++i) {
        if (this->__Vcov_cross_abcd_bins[i] >= 1) covered++;
    }
}
```

**Array Index Calculation:**

For N-way crosses, the index formula is:
```
index = bin[0] + bin[1] × size[0] + bin[2] × size[0] × size[1] + ...
```

**Coverage Calculation:**
```cpp
void get_inst_coverage(...) {
    IData __Vcovered_count = 0;
    for (size_t __Vi = 0; __Vi < 4; ++__Vi) {
        if (this->__Vcov_cross_ab_bins[__Vi] >= 1) {
            __Vcovered_count++;
        }
    }
    // Calculate percentage...
}
```

**Runtime:**
- Sample: O(N) where N = number of coverpoints in cross (bin matching) + O(1) index calc + O(1) increment
- Coverage calc: O(M) where M = total number of cross bins
- Memory: 4 bytes per possible bin combination

---

### Feature: Transition Bins (2-value)

**SystemVerilog:**
```systemverilog
coverpoint state {
    bins trans01 = (0 => 1);  // Transition from 0 to 1
}
```

**AST Transformation:**
1. Generate previous value variable:
   ```cpp
   CData __PVT____Vprev_cp_state;  // Stores previous sample value
   ```
2. Generate transition check:
   ```cpp
   void sample() {
       if ((this->__PVT____Vprev_cp_state == 0) && (current == 1)) {
           this->__PVT____Vcov_cp_state_trans01++;
       }
       this->__PVT____Vprev_cp_state = current;  // Save for next sample
   }
   ```

**Runtime:** O(1) per sample, 1 extra byte per coverpoint with transitions

---

### Feature: Multi-Value Transition Bins

**SystemVerilog:**
```systemverilog
coverpoint state {
    bins trans = (0 => 1 => 2 => 3);  // 4-value sequence
}
```

**AST Transformation:**
1. Generate sequence state variable:
   ```cpp
   CData __PVT____Vseqstate_trans;  // 0=idle, 1=saw 0, 2=saw 0=>1, 3=saw 0=>1=>2
   ```
2. Generate state machine with restart logic:
   ```cpp
   // State 0: Looking for 0
   if ((__PVT____Vseqstate_trans == 0) && (state == 0)) {
       __PVT____Vseqstate_trans = 1;
   }
   // State 1: Looking for 1
   else if ((__PVT____Vseqstate_trans == 1) && (state == 1)) {
       __PVT____Vseqstate_trans = 2;
   }
   // State 2: Looking for 2
   else if ((__PVT____Vseqstate_trans == 2) && (state == 2)) {
       __PVT____Vseqstate_trans = 3;
   }
   // State 3: Looking for 3 (final)
   else if ((__PVT____Vseqstate_trans == 3) && (state == 3)) {
       __PVT____Vcov_trans++;  // Sequence complete!
       __PVT____Vseqstate_trans = 0;  // Reset
   }
   // Restart: If we see 0 at any point, restart from state 1
   else if (state == 0) {
       __PVT____Vseqstate_trans = 1;
   }
   // Reset: Any other value resets to idle
   else {
       __PVT____Vseqstate_trans = 0;
   }
   ```

**Design Decision - Restart Logic:**

Per IEEE 1800-2023, sequences should restart when the first value is seen mid-sequence. For example:
- Sequence: `(0 => 1 => 2 => 3)`
- Input stream: `0, 0, 1, 2, 3` should match
- After first `0`, we're in state 1
- Second `0` triggers restart, staying in state 1
- Then `1, 2, 3` completes the sequence

**Runtime:** O(N) checks where N = sequence length, 1 extra byte per transition bin

---

### Feature: Covergroup Options

**SystemVerilog:**
```systemverilog
covergroup cg;
    option.weight = 2;
    option.goal = 90;
    option.at_least = 5;
    option.comment = "Test coverage";
endgroup
```

**AST Transformation:**
1. Generate option structure:
   ```cpp
   struct vl_covergroup_options_t {
       IData weight;
       IData goal;
       IData at_least;
       // ... other options
   };
   ```
2. Initialize in constructor:
   ```cpp
   this->__PVT__option.__PVT__weight = 2;
   this->__PVT__option.__PVT__goal = 90;
   this->__PVT__option.__PVT__at_least = 5;
   ```
3. Use in coverage computation:
   ```cpp
   if (bin_count >= this->__PVT__option.__PVT__at_least) {
       // Bin is covered
   }
   ```

**Supported Options:**
- `weight` - Used by get_coverage() for weighted averaging
- `goal` - Currently stored but not enforced
- `at_least` - Used in coverage computation
- `comment` - Stored but not used in computation

---

## Performance Considerations

### Compile-Time vs Runtime Trade-offs

| Aspect | Approach | Impact |
|--------|----------|--------|
| Bin matching | Compiled to if/else checks | Fast runtime, larger executable |
| Coverage computation | Inlined in get_coverage() | Fast query, no overhead |
| Cross coverage | All combinations pre-generated | Fast sampling, O(N²) space |
| Transition bins | State machine in sample() | Minimal overhead, 1-2 bytes extra state |

### Memory Usage

**Per covergroup instance:**
- 4 bytes per bin (counter)
- 1-8 bytes per coverpoint with transitions (previous value)
- 1-8 bytes per multi-value transition (state variable)
- ~64 bytes for option structures

**Example:**
- 10 bins = 40 bytes
- 2 transitions = 2 bytes
- Options = 64 bytes
- **Total: ~106 bytes per covergroup instance**

### Sampling Performance

**Micro-benchmark (estimated):**
- Simple bin: ~2-5 CPU cycles (compare + conditional increment)
- Transition bin: ~5-10 cycles (prev check + compare + update)
- Multi-value transition: ~10-20 cycles (state machine)
- Cross (2-way, 4×4 bins): ~64-128 cycles (16 nested checks)

**For typical testbench with 5 covergroups, 50 bins total:**
- Per sample: ~150-300 cycles
- At 1GHz: ~150-300 nanoseconds
- Negligible compared to typical simulation overhead

---

## Supported Features and Test Validation

This section provides a comprehensive mapping of IEEE 1800-2023 Section 19 (Functional Coverage) features to their implementation status and validation tests in Verilator.

### Feature Support Matrix

#### Core Coverpoint Features

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **Basic Coverpoints** | 19.5 | ✅ Full | `t_covergroup_simple.v` | Single-variable coverage with bins |
| **Explicit Value Bins** | 19.5.1 | ✅ Full | `t_covergroup_simple.v`<br>`t_covergroup_bins_advanced.v` | `bins name = {value1, value2, ...}` |
| **Range Bins** | 19.5.1 | ✅ Full | `t_covergroup_bins_advanced.v`<br>`t_covergroup_negative_ranges.v` | `bins name = {[low:high]}` including negative ranges |
| **Array Bins** | 19.5.1 | ✅ Full | `t_covergroup_bins_advanced.v` | `bins name[] = {values}` expands to multiple bins |
| **Auto-Partitioned Bins** | 19.5.3 | ✅ Full | `t_funccov_auto_bins.v` | `bins auto[N]` partitions range into N bins |
| **Wildcard Bins** | 19.5.1 | ✅ Full | `t_covergroup_bins_advanced.v` | `wildcard bins name = {pattern}` with `?` wildcards |
| **Default Bins** | 19.5.1 | ✅ Full | `t_covergroup_bins_default_illegal.v` | `bins name = default` catches unspecified values |
| **Ignore Bins** | 19.5.1 | ✅ Full | `t_covergroup_bins_advanced.v` | `ignore_bins name = {values}` excludes from coverage |
| **Illegal Bins** | 19.5.1 | ✅ Full | `t_covergroup_bins_default_illegal.v` | `illegal_bins name = {values}` triggers runtime error |

#### Transition Coverage

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **2-Value Transitions** | 19.5.2 | ✅ Full | `t_covergroup_trans_simple.v` | `bins trans = (val1 => val2)` |
| **Multi-Value Sequences** | 19.5.2 | ✅ Full | `t_covergroup_trans_3value.v`<br>`t_covergroup_trans_restart.v` | `bins trans = (v0 => v1 => v2 => v3)` with restart logic |
| **Transition with Ranges** | 19.5.2 | ✅ Full | `t_covergroup_trans_ranges.v` | `bins trans = ([lo:hi] => [lo2:hi2])` |
| **Repetition `[*N]`** | 19.5.2 | ❌ Not Supported | N/A | See `REPETITION_ROADMAP.md` |
| **Goto Repetition `[->N]`** | 19.5.2 | ❌ Not Supported | N/A | See `REPETITION_ROADMAP.md` |
| **Nonconsecutive `[=N]`** | 19.5.2 | ❌ Not Supported | N/A | See `REPETITION_ROADMAP.md` |

#### Cross Coverage

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **2-Way Cross** | 19.6 | ✅ Full | `t_covergroup_cross_simple.v`<br>`t_covergroup_cross_small.v` | `cross cp_a, cp_b` generates all combinations |
| **3-Way Cross** | 19.6 | ✅ Full | `t_covergroup_cross_3way.v` | `cross cp_a, cp_b, cp_c` |
| **4-Way Cross** | 19.6 | ✅ Full | `t_covergroup_cross_4way.v` | `cross cp_a, cp_b, cp_c, cp_d` |
| **N-Way Cross** | 19.6 | ✅ Full | `t_covergroup_cross_large.v` | Supports arbitrary N with array-based storage |
| **Cross with `binsof`** | 19.6.3 | ⚠️ Partial | N/A | Basic filtering supported, advanced expressions limited |
| **Cross with `intersect`** | 19.6.3 | ❌ Not Supported | N/A | Not yet implemented |

#### Sampling and Triggers

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **Manual Sampling** | 19.3 | ✅ Full | `t_covergroup_simple.v` | Explicit `cg.sample()` calls |
| **Automatic Sampling** | 19.3.1 | ✅ Full | `t_covergroup_auto_sample.v` | `covergroup cg @(posedge clk)` in both `--timing` and `--no-timing` |
| **Conditional Sampling** | 19.4.1 | ✅ Full | `t_covergroup_iff.v` | `coverpoint expr iff (condition)` |
| **Sample Arguments** | 19.3.2 | ✅ Full | `t_covergroup_with_sample_args.v`<br>`t_covergroup_with_sample_namedargs.v` | `with function sample(args)` with positional and named args |
| **Default Arguments** | 19.3.2 | ✅ Full | `t_covergroup_with_sample_args_default.v` | Sample function parameters with defaults |
| **Zero-Argument Sample** | 19.3.2 | ✅ Full | `t_covergroup_with_sample_zeroargs.v` | `with function sample()` |

#### Options and Configuration

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **`option.name`** | 19.7 | ✅ Full | `t_covergroup_option.v` | Set covergroup/point name |
| **`option.comment`** | 19.7 | ✅ Full | `t_covergroup_option.v` | Add descriptive comment |
| **`option.at_least`** | 19.7 | ✅ Full | `t_covergroup_option.v` | Minimum hits for coverage (default: 1) |
| **`option.auto_bin_max`** | 19.7 | ⚠️ Parsed | N/A | Parsed but auto-creation without bins not implemented |
| **`option.per_instance`** | 19.7 | ✅ Full | `t_covergroup_cross_small.v` | Per-instance vs. type-level coverage |
| **`option.get_inst_coverage`** | 19.7 | ❌ Not Supported | N/A | Use method instead |
| **Coverpoint Options** | 19.7 | ✅ Full | `t_covergroup_option.v` | Same options apply to coverpoints |

#### Instance Management

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **Static Declaration** | 19.3 | ✅ Full | `t_covergroup_simple.v` | `cg cg_inst = new;` |
| **Dynamic Creation** | 19.3 | ✅ Full | `t_covergroup_dynamic.v` | Runtime instantiation with `new` operator |
| **Multiple Instances** | 19.3 | ✅ Full | `t_covergroup_multi_instance.v` | Independent instances of same covergroup |
| **Covergroup in Class** | 19.3 | ✅ Full | `t_covergroup_in_class.v`<br>`t_covergroup_in_class_with_sample.v` | Covergroup as class member |
| **Empty Covergroup** | 19.3 | ✅ Full | `t_covergroup_empty.v` | Covergroup with no coverpoints (100% coverage) |

#### Coverage Query Methods

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **`get_inst_coverage()`** | 19.8.1 | ✅ Full | `t_covergroup_get_coverage.v`<br>`t_covergroup_coverage_pct.v` | Returns instance coverage percentage |
| **`get_coverage()`** | 19.8.1 | ❌ Not Supported | `t_covergroup_static_coverage.v` | Static method blocked by architecture |
| **`start()`** | 19.8.2 | ❌ Not Supported | N/A | Coverage always active |
| **`stop()`** | 19.8.2 | ❌ Not Supported | N/A | Coverage always active |

#### Advanced Features

| Feature | IEEE 1800 Ref | Status | Test File(s) | Notes |
|---------|---------------|--------|--------------|-------|
| **Covergroup Inheritance** | 19.12 | ✅ Full | `t_covergroup_extends.v`<br>`t_covergroup_extends_newfirst.v` | `extends` keyword support |
| **Type Parameters** | 19.3 | ✅ Full | `t_covergroup_args.v` | Parameterized covergroups |
| **Minimal Syntax** | 19.3 | ✅ Full | `t_covergroup_minimal.v` | Simplest valid covergroup |
| **Performance Test** | N/A | ✅ Full | `t_covergroup_perf.v` | Large-scale coverage stress test |

### Legend

- ✅ **Full**: Fully implemented and tested according to IEEE 1800-2023
- ⚠️ **Partial**: Implemented with known limitations or subset support
- ❌ **Not Supported**: Feature not yet implemented

### Test Organization

All functional coverage tests follow these conventions:

1. **File naming**: `t_covergroup_<feature>.v` for pass tests, `*_bad.v` for error tests
2. **Self-checking**: Tests verify their own results with `$display` and `$finish`/$stop`
3. **Coverage validation**: Tests check `get_inst_coverage()` for expected percentages
4. **IEEE compliance**: Tests based on examples from IEEE 1800-2023 Section 19

### Error Validation Tests

These tests verify proper error detection:

| Test File | Validates |
|-----------|-----------|
| `t_covergroup_option_bad.v` | Invalid option usage |
| `t_covergroup_option_bad2.v` | Additional option errors |
| `t_covergroup_method_bad.v` | Invalid method calls |
| `t_covergroup_new_override_bad.v` | Illegal constructor overrides |
| `t_covergroup_func_override_bad.v` | Invalid function overrides |
| `t_covergroup_with_function_foo_bad.v` | Invalid `with function` syntax |
| `t_covergroup_with_sample_args_too_few_bad.v` | Insufficient sample arguments |
| `t_covergroup_with_sample_args_too_many_bad.v` | Excess sample arguments |
| `t_covergroup_in_class_duplicate_bad.v` | Duplicate covergroup definitions |
| `t_covergroup_coverpoints_unsup.v` | Unsupported coverpoint features |
| `t_covergroup_unsup.v` | General unsupported features |

### IEEE 1800-2023 Compliance Summary

**Supported**: ~85% of Section 19 (Functional Coverage) features
- **Full support**: Core bins, transitions, cross coverage, automatic sampling, options
- **Partial support**: Advanced cross filtering, some options parsed but not enforced
- **Not supported**: Repetition operators, static coverage queries, start/stop methods

See `references/sv_functional_coverage.md` for extracted IEEE 1800-2023 specification details.

---

## Known Limitations and Workarounds

### 1. Repetition Operators Not Supported

**Limitation:** Consecutive `[*N]`, goto `[->N]`, and nonconsecutive `[=N]` repetition operators are not implemented.

```systemverilog
bins trans = (1 => 2 [*3] => 3);  // ERROR: Unsupported
```

**Workaround:** Expand manually:
```systemverilog
bins trans = (1 => 2 => 2 => 2 => 3);  // OK
```

**Status:** Flagged with `COVERIGN` warning, see `REPETITION_ROADMAP.md` for implementation plan.

---

### 2. Static get_coverage() Not Implemented

**Limitation:** The static `ClassName::get_coverage()` method (type-level aggregation) is not implemented.

```systemverilog
cg::get_coverage();  // Returns 0.0 (placeholder)
```

**Workaround:** Use instance-level method:
```systemverilog
cg_inst.get_inst_coverage();  // Works correctly
```

**Root Cause:** Verilator's AST/EmitC infrastructure doesn't have established patterns for C++ static members with instance tracking.

---

### 3. Set-Based Bin Selection Not Supported

**Limitation:** Bins with value sets in transitions aren't fully supported:

```systemverilog
bins trans = (0, 1 => 2, 3);  // Limited support
```

**Status:** Basic functionality works for simple cases, complex combinations may not work as expected.

---

## Future Enhancements

### Planned Features

1. **Repetition Operators** - [*N], [->N], [=N] support (see REPETITION_ROADMAP.md)
2. **Static get_coverage()** - Requires EmitC infrastructure improvements
3. **Sparse Cross Storage** - Use std::map for large N-way crosses
4. **Coverage Goals** - Runtime checking and reporting of goal thresholds
5. **Per-Instance Control** - Enable/disable coverage per instance

### Optimization Opportunities

1. **Binary Search for Range Bins** - For coverpoints with many range bins
2. **Bloom Filters** - For wildcard bins with many patterns
3. **Lazy Cross Generation** - Only create cross bins when hit
4. **SIMD Vectorization** - Parallel bin matching for wide coverpoints

---

## Conclusion

Verilator's functional coverage implementation achieves production-ready quality through a pure code-generation approach. By transforming SystemVerilog covergroups into efficient C++ classes at compile time, it minimizes runtime overhead while maintaining compatibility with existing coverage infrastructure.

The SystemC::Coverage-3 database format provides seamless integration with Verilator's coverage analysis tools, enabling unified reporting across line, toggle, and functional coverage metrics.

For implementation questions or contributions, see:
- **Source:** `src/V3CoverageFunctional.cpp`
- **Tests:** `test_regress/t/t_covergroup_*.v`
- **Roadmap:** `docs/functional_coverage_plan.md`
- **Repetitions:** `REPETITION_ROADMAP.md`

---

**Document Version:** 1.0  
**Last Updated:** 2026-02-09  
**Maintainer:** Verilator Development Team
