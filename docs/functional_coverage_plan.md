# SystemVerilog Functional Coverage Implementation Plan for Verilator

## Executive Summary

This document outlines a comprehensive plan for implementing SystemVerilog functional coverage in Verilator. The goal is to extend Verilator's existing code coverage infrastructure to support user-defined functional coverage as specified in IEEE 1800-2023 Section 19.

## Current State Analysis

## Current State Analysis

### Implementation Status (as of 2026-02-08 00:01 UTC)

**Phase 2: Parser & Code Generation - COMPLETE** ✅
- Parser successfully creates AstCovergroup, AstCoverpoint, AstCoverBin nodes
- **CRITICAL BUG FIXED:** Circular reference in bin lists causing infinite loops
  - Root cause: Bins were being moved to coverpoint while still linked in parser list
  - Fix: Create temporary parent, unlink all bins, then add to coverpoint
- Code generation working correctly:
  - Generates C++ class for each covergroup
  - Creates member variables for bin counters (__Vcov_*)
  - Generates sample() method with bin matching logic
  - Generates get_inst_coverage() method with coverage computation
  - Successfully compiles and runs test cases

**Phase 5: Coverage Computation - COMPLETE** ✅
- Basic coverage computation implemented and working
- get_inst_coverage() calculates percentage correctly (0-100%)
- Multi-value bins supported (OR logic)
- iff conditions working correctly
- 7 comprehensive tests passing

**Phase 6: Special Bin Types - COMPLETE** ✅
- ignore_bins: Parser ✅, AST ✅, Code generation ✅, Coverage filtering ✅
- illegal_bins: Parser ✅, AST ✅, Error generation ✅, Coverage filtering ✅
- **BUG FIXED:** Parser was not setting bin types correctly
  - Root cause: bins_keyword grammar rule couldn't distinguish ignore/illegal from regular bins
  - Fix: Expanded grammar to use explicit yBINS/yIGNORE_BINS/yILLEGAL_BINS tokens
  - Result: Bins now correctly typed, filtered from coverage computation, error on illegal hit
- 10 comprehensive tests passing

**Phase 7: Cross Coverage - COMPLETE** ✅
- Cross coverage (2-way, 3-way, N-way) fully implemented and working
- Parser: ✅ Already had full cross support with coverpoint references
- Code generation: ✅ Cartesian product bin generation working
- Coverage computation: ✅ Cross bins counted correctly in get_inst_coverage()
- Verified with comprehensive tests:
  - 2-way cross (2×2 = 4 bins)
  - 3-way cross (2×2×2 = 8 bins)
- N-way cross supported via recursive Cartesian product algorithm

**Phase 8: Wildcard Bins - COMPLETE** ✅
- Wildcard bins with don't-care matching fully implemented
- Parser: ✅ Already recognized `wildcard bins` keyword
- AST: ✅ Added VCoverBinsType::WILDCARD enum value
- Code generation: ✅ Bit-mask matching implemented
  - Generates `(expr & mask) == (value & mask)` conditions
  - Properly handles X/Z bits as don't-cares
- Test verified: 8-bit patterns with ? wildcards work correctly
- Examples: `8'b0000_????`, `8'b1111_????`, `8'b10?0_11??`

**Phase 9: Bin Options - COMPLETE** ✅
- Bin options parsing and enforcement implemented
- Parser: ✅ Converts `AstCgOptionAssign` to `AstCoverOption` nodes
- Options supported:
  - `option.at_least = N` ✅ - Enforced in coverage computation
  - `option.weight = N` - Parsed (not yet used)
  - `option.goal = N` - Parsed (not yet used)
  - `option.comment = "string"` - Parsed
  - `option.auto_bin_max = N` - Parsed
  - `option.per_instance = 0/1` - Parsed
- Coverage computation updated to check `bin_count >= at_least`
- Test verified: at_least=2 requires 2+ hits for coverage

**Phase 10: get_coverage() Method - PARTIAL** ⚠️
- Static/type-level get_coverage() method implemented
- Currently returns 0.0 (placeholder for full implementation)
- Full implementation requires instance tracking infrastructure:
  - Need to track all instances globally
  - Aggregate coverage across all instances
  - This requires static counters or instance registry
- Test verified: Method exists and is callable
- Future: Implement proper instance aggregation

**Phase 11: Default Bins - COMPLETE** ✅
- Default bins implementation fully working
- Parser: ✅ Creates AstCoverBin with VCoverBinsType::DEFAULT
- Code generation: ✅ Two-pass approach:
  1. First pass: Generate code for all explicit bins
  2. Second pass: Generate default bins with NOT(all_explicit_bins) condition
- Default bins match values not covered by any other explicit bin
- Properly excludes ignore_bins and illegal_bins from negation condition
- Test verified: Default bin catches uncovered values correctly
- Coverage computation treats default bins as regular bins

**Phase 12: Coverage Database Output - ANALYSIS COMPLETE** 📋
- Analyzed integration requirements with Verilator's coverage system
- **Current Status**: Bins are counted but not registered with coverage database
- **Requirements identified**:
  1. Access to `VerilatedCovContext` in class constructors
  2. `VL_COVER_INSERT()` macro calls for each bin
  3. Hierarchical naming scheme for functional coverage bins
  4. New coverage type identifier (e.g., "funccov" beyond line/block/toggle)
  5. Updates to verilator_coverage tool to parse functional coverage
- **Challenges**:
  - Functional coverage lives in class instances, not modules
  - Coverage context must be threaded through class instantiation
  - Requires changes to class code generation infrastructure
  - Each bin needs globally unique hierarchical identifier
- **Recommendation**: Defer to future work - requires architectural changes beyond current scope

**Next Steps (Priority Order):**
1. Implement coverage database integration (requires infrastructure work)
2. Implement instance tracking for full get_coverage() aggregation
3. Implement cross coverage bin filtering (binsof, intersect)
4. Add array bins support (bins name[] = {...})
5. Weight-based coverage aggregation

**Current Test Status:**
- ✅ 17 tests passing (11 original + 2 cross + 1 wildcard + 1 bin options + 1 get_coverage + 1 default bins)
- All core functional coverage features working
- Coverage computation correct, but not yet integrated with coverage database

### Existing Code Coverage Infrastructure

Verilator has a mature code coverage implementation with the following components:

**Coverage Collection:**
- `src/V3Coverage.cpp/h` - Transforms AST to insert coverage instrumentation
- `src/V3CoverageJoin.cpp/h` - Optimizes and deduplicates coverage points
- Coverage types supported: line, block, toggle, FSM, expression

**Runtime Support:**
- `include/verilated_cov.h/cpp` - Runtime coverage collection API
- Thread-safe coverage counter management with `VerilatedMutex`
- `VL_COVER_INSERT()` macro for registering coverage points
- Storage in both 32-bit and 64-bit counter arrays

**Output Format:**
- Text-based `SystemC::Coverage-3` format
- Key-value pairs with single-letter shortcodes:
  - `f` = filename, `l` = lineno, `n` = column
  - `t` = type (block/line/fsm/toggle)
  - `h` = hierarchy, `o` = comment
  - `P` = per_instance flag, `s` = threshold
- Format: `C 'key1=val1 key2=val2...' count`
- Hierarchical aggregation with wildcards when `per_instance=false`

**Post-Processing:**
- `bin/verilator_coverage` (Perl) - Coverage database manipulation
- `src/VlcTop.cpp` - C++ coverage analysis tool
- Outputs: `.dat` (binary), `.info` (LCOV format)

**Parser Status:**
- `src/*.y` - Grammar recognizes `covergroup` keyword
- Currently issues `COVERIGN` warning: "Ignoring unsupported: covergroup"
- Grammar has placeholder rules but no semantic actions

### Key Architectural Patterns

1. **AST-based transformation**: Coverage instrumentation via AST visitors
2. **Compile-time registration**: Coverage points registered during C++ initialization
3. **Key-value metadata**: Extensible format for coverage attributes
4. **Separate compilation**: Coverage data structures generated per module
5. **Post-simulation merging**: Coverage aggregation via external tool

## SystemVerilog Functional Coverage Requirements

Based on IEEE 1800-2023 Section 19, the following features must be supported:

### Core Constructs (Priority 1 - Essential)

1. **Covergroup Declaration**
   - Basic syntax: `covergroup <name> @(<event>); ... endgroup`
   - Instantiation with `new` operator
   - Formal arguments (ref and input)
   - Embedded covergroups in classes
   - Explicit sample method: `with function sample(...)`

2. **Coverage Points**
   - `coverpoint <expression>` syntax
   - Automatic bin creation
   - User-defined bins: `bins <name> = { values }`
   - Value ranges: `[min:max]`
   - Transition bins: `bins <name> = ( seq => seq )`
   - Conditional coverage: `iff (<condition>)`

3. **Cross Coverage**
   - `cross <cp1>, <cp2>, ...` syntax
   - Automatic cross product generation
   - User-defined cross bins with `binsof()` and `intersect`

4. **Coverage Options**
   - Instance options: `option.<member> = <value>`
     - `weight`, `goal`, `at_least`, `comment`
     - `auto_bin_max`, `per_instance`
   - Type options: `type_option.<member> = <constant>`
     - `weight`, `goal`, `comment`
     - `strobe`, `merge_instances`

5. **Predefined Methods**
   - `sample()` - Trigger coverage sampling
   - `get_coverage()` - Return type coverage (0-100)
   - `get_inst_coverage()` - Return instance coverage
   - `start()`, `stop()` - Enable/disable collection

6. **System Tasks**
   - `$get_coverage()` - Overall coverage across all types
   - `$set_coverage_db_name(filename)` - Set output file
   - `$load_coverage_db(filename)` - Load previous coverage

### Advanced Features (Priority 2 - Important)

7. **Bin Specifications**
   - `ignore_bins` - Exclude values from coverage
   - `illegal_bins` - Trigger error on match
   - `wildcard bins` - Don't care bits in value matching
   - `default bins` - Catch-all for unspecified values
   - Array bins: `bins <name>[] = {...}` for separate bins per value

8. **Coverage Events**
   - Clocking events: `@(posedge clk)`
   - Block events: `@@(begin task_name)`, `@@(end task_name)`
   - Multiple sampling per time step

9. **Advanced Cross Features**
   - `binsof(<coverpoint>)` select expressions
   - `intersect` operator for bin filtering
   - Logical operators: `&&`, `||`, `!`
   - `cross_retain_auto_bins` option

10. **Covergroup Inheritance**
    - `covergroup extends <base>` (within classes only)
    - Bin overriding in derived covergroups

### Optional/Future Features (Priority 3)

11. **Real-Valued Coverage**
    - `real_interval` option for floating-point bins

12. **Advanced Options**
    - `detect_overlap` - Warn on overlapping bins
    - `cross_num_print_missing` - Control reporting

## Proposed Architecture

### Output Format Extension

**Option A: Extend SystemC::Coverage Format (RECOMMENDED)**

Extend the existing `SystemC::Coverage-3` format with new type codes and keys:

```
# SystemC::Coverage-4  (increment version)

# Covergroup declaration metadata
G 't=covergroup n=cg1 h=top.dut c=Coverage for feature X w=10 g=100'

# Coverpoint with bins
C 't=coverpoint n=cg1.cp1 b=auto[0] r=0:15 h=top.dut' 42
C 't=coverpoint n=cg1.cp1 b=auto[1] r=16:31 h=top.dut' 17

# Cross coverage bins
C 't=cross n=cg1.cross_ab b=<a[0],b[1]> h=top.dut' 8

# Transition bins
C 't=transition n=cg1.state b=IDLE=>BUSY h=top.dut' 5
```

**New key codes:**
- `t=covergroup|coverpoint|cross|transition` - Coverage type
- `b=<binname>` - Bin identifier
- `r=<range>` - Value range for bin
- `g=<goal>` - Coverage goal percentage
- `w=<weight>` - Weight for aggregation
- `a=<at_least>` - Minimum hit count for coverage
- `m=<max>` - Auto bin max

**Advantages:**
- Reuses existing infrastructure
- Backward compatible (different version)
- Leverages verilator_coverage tool
- Unified coverage database

**Option B: Separate Functional Coverage Format**

Create a new format specifically for functional coverage:

```
# Verilator::FunctionalCoverage-1

COVERGROUP cg1 top.dut weight=10 goal=100
  COVERPOINT cp1 auto_bin_max=256
    BIN auto[0] range=0:15 count=42
    BIN auto[1] range=16:31 count=17
  CROSS cross_ab
    BIN <a[0],b[1]> count=8
```

**Advantages:**
- Clean separation of concerns
- More readable for functional coverage users
- Easier to implement covergroup-specific features

**Disadvantages:**
- Requires separate tool chain
- Duplicate infrastructure
- Harder to get unified coverage reports

**RECOMMENDATION: Option A** - Extend the existing format to version 4, adding functional coverage as a new coverage type alongside line/block/toggle. This provides the best balance of reuse and functionality.

### Implementation Phases

#### Phase 1: Foundation (Milestone: Basic Covergroup Support)

**1.1 Parser and AST Enhancement**
- Extend parser grammar for full covergroup syntax
- Create new AST node types:
  - `AstCovergroup` - Covergroup declaration
  - `AstCoverpoint` - Coverage point
  - `AstCoverBins` - Bin specification
  - `AstCoverCross` - Cross coverage
  - `AstCoverSample` - Sample method call
- Add coverage options storage structures
- Extend symbol tables for covergroup namespace

**Files to modify:**
- `src/*.y` - Parser grammar
- `src/V3Ast*.h` - AST node definitions
- `src/V3AstNodes.h` - Node type registration

**1.2 Coverage Type Infrastructure**
- Define runtime data structures for functional coverage
- Extend `verilated_cov_key.h` with new key types
- Create `verilated_funccov.h/cpp` for functional coverage runtime
  - `VerilatedCovergroup` class
  - `VerilatedCoverpoint` class
  - `VerilatedCoverBin` class
  - `VerilatedCoverCross` class

**Files to create/modify:**
- `include/verilated_funccov.h` (new)
- `include/verilated_funccov.cpp` (new)
- `include/verilated_cov_key.h` (extend)

**1.3 Basic Code Generation**
- Generate C++ class for each covergroup
- Implement constructor with formal arguments
- Generate member variables for coverage points
- Implement basic `sample()` method
- Register coverage bins with `VerilatedCovContext`

**Files to modify:**
- `src/V3EmitCFunc.cpp` - Function emission
- `src/V3EmitCImp.cpp` - Implementation emission
- Create new `src/V3EmitFuncCov.cpp` for covergroup emission

#### Phase 2: Coverage Point Implementation (Milestone: Basic Sampling Works)

**2.1 Automatic Bin Creation**
- Analyze coverpoint expression type
- Generate bins based on `auto_bin_max` option
- Handle integral types: create bins for value ranges
- Handle enum types: one bin per enum value
- Implement bin hit counting

**2.2 User-Defined Bins**
- Parse and validate bin specifications
- Generate bin range checking logic
- Support value sets: `bins b = {1, 2, 5}`
- Support ranges: `bins b = {[0:10]}`
- Support multiple ranges: `bins b = {[0:5], [10:15]}`

**2.3 Sampling Logic** ✅ **COMPLETED**
- ✅ Generate sampling code in `sample()` method (pre-existing)
- ✅ Evaluate coverpoint expressions (pre-existing)
- ✅ Match values to bins and increment counters (pre-existing)
- ✅ Support `iff` conditions for selective sampling **[NEWLY IMPLEMENTED]**
  - Coverpoint `iff` expressions are now evaluated and ANDed with bin match conditions
  - Sample only occurs when iff condition evaluates to true
  - Test: `test_regress/t/t_covergroup_iff.v`
- ⏸️ Handle clocking event triggers (deferred - requires event infrastructure)

**Implementation Notes:**
- Modified `V3CoverageFunctional.cpp::generateBinMatchCode()` to incorporate `iffp` expression
- When an `iff` condition exists on a coverpoint, it is cloned and ANDed with each bin's match condition
- This ensures sampling only occurs when both the iff condition is true AND the value matches a bin

**Files modified:**
- `src/V3CoverageFunctional.cpp` - Added iff condition support to bin matching logic


#### Phase 3: Cross Coverage (Milestone: Cross Coverage Works)

**3.1 Basic Cross Coverage**
- Generate cross product of coverpoint bins
- Create combined bin identifiers
- Track cross product hit counts

**3.2 Cross Bin Selection**
- Implement `binsof()` operator
- Implement `intersect` filtering
- Support logical operators: `&&`, `||`, `!`
- Implement `cross_retain_auto_bins` option

#### Phase 4: Advanced Bins (Milestone: All Bin Types Supported)

**4.1 Transition Bins**
- Parse transition syntax: `(val1 => val2 => val3)`
- Track state history per coverpoint
- Match transition sequences
- Generate appropriate metadata

**4.2 Special Bins**
- Implement `ignore_bins` (exclude from coverage)
- Implement `illegal_bins` (runtime error on match)
- Implement `default bins` (catch-all)
- Implement `wildcard bins` (don't care matching)

#### Phase 5: Coverage Computation (Milestone: Get_Coverage Works) 🚧 **IN PROGRESS**

**5.1 Coverage Metrics** 🚧 **IN PROGRESS**
- ⚠️ Implementing coverage computation algorithms
  - Basic algorithm implemented: count covered bins (count > 0) / total bins * 100
  - Generated code computes coverage in get_coverage() and get_inst_coverage()
  - **Issues to resolve:**
    - Need to use correct Verilated runtime function for double division
    - get_coverage() is static but needs access to instance data - need to aggregate across instances
    - get_inst_coverage() works for single instance
- ⏸️ Cross coverage formula per IEEE spec (deferred)
- ⏸️ Weight-based aggregation (deferred)
- ⏸️ Support `at_least` threshold (deferred)

**5.2 Predefined Methods** 🚧 **IN PROGRESS** 
- ⚠️ Implement `get_coverage()` (type coverage) - basic implementation done, needs fixes
- ⚠️ Implement `get_inst_coverage()` (instance coverage) - basic implementation done, needs fixes
- ⏸️ Implement `start()` and `stop()` (stubs exist, no functionality yet)
- ⏸️ Implement `set_inst_name()` (stub exists, no functionality yet)

**Implementation Notes:**
- Added `generateCoverageComputationCode()` method to V3CoverageFunctional.cpp
- Code generation creates local variable to count covered bins
- Iterates through all bin counter variables (__Vcov_*)
- Increments covered count for each bin with count > 0
- Computes percentage: (covered / total) * 100
- **Current blockers:**
  - C++ compilation fails due to VL_DIV_DDD not existing  
  - Static get_coverage() cannot access instance member variables
  
**Files modified:**
- `src/V3CoverageFunctional.cpp` - Added coverage computation code generation

**5.3 System Functions** ⏸️ **DEFERRED**
- ⏸️ Implement `$get_coverage()`
- ⏸️ Implement `$set_coverage_db_name()`
- ⏸️ Implement `$load_coverage_db()`

#### Phase 6: Output and Reporting (Milestone: Coverage Reports Generated)

**6.1 Coverage Database Format**
- Extend SystemC::Coverage format to version 4
- Output covergroup metadata
- Output bin-level coverage data
- Support hierarchical naming
- Implement `per_instance` handling

**6.2 Tool Enhancement**
- Extend `verilator_coverage` Perl tool
- Support functional coverage merging
- Generate functional coverage reports
- Compute coverage percentages
- Support filtering by covergroup/coverpoint

**6.3 Report Formats**
- Text report with coverage percentages
- Bin-level detail reports
- Cross coverage matrices
- UCIS export (optional)

#### Phase 7: Advanced Features (Future Enhancements)

**7.1 Class Integration**
- Embedded covergroups in classes
- Access to class members from coverpoints
- Covergroup inheritance
- Polymorphic coverage

**7.2 Performance Optimization**
- Optimize bin matching algorithms
- Reduce memory footprint
- Lazy bin creation
- Coverage sampling throttling

**7.3 Additional Features**
- Block event expressions `@@(begin/end)`
- Real-valued coverage with `real_interval`
- Coverage-driven generation hints
- Integration with constrained random

## Technical Challenges and Open Issues

### Challenge 1: Static vs. Dynamic Elaboration

**Issue:** SystemVerilog allows covergroups to be instantiated dynamically (via `new`), potentially multiple times with different arguments. Verilator typically elaborates everything at compile time.

**Impact:** HIGH - Affects fundamental architecture

**Proposed Solutions:**
1. **Static instantiation only** (Phase 1 approach)
   - Require all covergroups to be instantiated in module initial blocks
   - Analyze and count instances at compile time
   - Generate fixed arrays for each instance
   - **Pros:** Fits Verilator model, no runtime overhead
   - **Cons:** Limits dynamic instantiation

2. **Dynamic instance tracking** (Future enhancement)
   - Generate covergroup constructors with runtime registration
   - Use `std::vector` or linked lists for instance storage
   - Allow unlimited instances
   - **Pros:** Full SystemVerilog compliance
   - **Cons:** Runtime overhead, complex implementation

**Recommendation:** Start with static instantiation, add dynamic support in Phase 7.

### Challenge 2: Bin Matching Performance

**Issue:** Matching sampled values against potentially hundreds of bins every clock cycle could be expensive.

**Impact:** MEDIUM - Performance concern for large covergroups

**Proposed Solutions:**
1. **Linear search** (Phase 1)
   - Simple if-else chain
   - Acceptable for small number of bins
   
2. **Binary search tree**
   - Sort bins by range at compile time
   - O(log n) lookup
   
3. **Hash table**
   - Direct value-to-bin mapping
   - O(1) for exact matches
   - Harder for range bins

4. **Range tree / Interval tree**
   - Efficient for overlapping ranges
   - Complex to implement

**Recommendation:** Start with linear search, profile, then optimize if needed.

### Challenge 3: Cross Coverage Explosion

**Issue:** Cross coverage of N coverpoints with M bins each creates M^N cross products. This can explode quickly (10 coverpoints × 10 bins = 10 billion combinations).

**Impact:** HIGH - Memory and runtime concern

**Proposed Solutions:**
1. **Sparse storage** (REQUIRED)
   - Only allocate bins when hit
   - Use hash map: `<bin_tuple> -> count`
   - **Essential for practical use**

2. **Cross bin limits**
   - Add option to limit cross product generation
   - Warn when exceeding threshold
   - Allow user override

3. **Lazy cross bin creation**
   - Generate cross bins on-demand as values are sampled
   - Reduces compile-time overhead

**Recommendation:** Implement sparse storage from the start (Phase 3).

### Challenge 4: Expression Coverage vs. Functional Coverage

**Issue:** Verilator already has "expression coverage" for conditionals. How does this relate to functional coverage of expressions?

**Impact:** MEDIUM - User confusion, implementation overlap

**Clarification:**
- **Code coverage (expression):** Automatic, structural, measures which terms in `if (a && b)` were true/false
- **Functional coverage:** User-defined, intentional, measures specific values or sequences

**Recommendation:** Keep them separate but allow cross-referencing in reports.

### Challenge 5: Sampling Event Handling

**Issue:** Covergroups can be triggered by:
- Clocking events: `@(posedge clk)`
- Explicit calls: `cg.sample()`
- Block events: `@@(begin task_name)`

**Impact:** MEDIUM - Affects code generation

**Proposed Solutions:**
1. **Clocking events** - Generate sensitivity list, call `sample()` in procedural block
2. **Explicit calls** - Direct method call, straightforward
3. **Block events** - Insert `sample()` calls at entry/exit of named blocks (complex)

**Recommendation:** Phase 1 supports explicit calls and clocking events only. Block events in Phase 7.

### Challenge 6: Coverage Database Merging

**Issue:** Running multiple tests produces multiple coverage databases. They need to be merged intelligently based on:
- `per_instance` setting
- `merge_instances` type option
- Hierarchical wildcarding

**Impact:** MEDIUM - Post-processing complexity

**Recommendation:** Extend existing `verilator_coverage` tool merge logic to handle functional coverage bins. The key-value format already supports this.

### Challenge 7: Two-State vs. Four-State

**Issue:** SystemVerilog supports X and Z in signals, but bins are typically defined for 0/1 values only.

**Impact:** LOW - Edge case handling

**Proposed Solution:**
- X and Z values don't match any bins by default
- Provide option to treat X/Z as don't-care or as separate values
- Document the behavior clearly

### Challenge 8: Coverage in Assertions

**Issue:** IEEE allows `cg.sample()` to be called from within properties/sequences. Verilator's assertion support is limited.

**Impact:** LOW - Rare use case

**Recommendation:** Defer to future. Document limitation.

## Opportunities and Extensions

### Opportunity 1: UCIS Export

**Description:** Universal Coverage Interoperability Standard (Accellera UCIS) is a standard format for coverage interchange.

**Benefits:**
- Integration with commercial tools (DVT, Verdi, etc.)
- Standardized coverage merging
- Industry-standard reporting

**Implementation:** Add UCIS XML export option to `verilator_coverage` tool (Phase 6 or 7).

### Opportunity 2: Coverage-Driven Random Testing

**Description:** Use coverage feedback to guide constrained-random stimulus generation.

**Benefits:**
- Automated test generation
- Faster convergence to coverage goals
- Discover corner cases

**Implementation:** Complex - requires constrained-random solver integration. Phase 7 or separate project.

### Opportunity 3: Coverage Closure Analysis

**Description:** Analyze which bins are hardest to hit, suggest stimulus strategies.

**Benefits:**
- Helps users understand coverage gaps
- Suggests focused testing areas

**Implementation:** Add analysis mode to `verilator_coverage` tool. Low effort, high value.

### Opportunity 4: Incremental Coverage

**Description:** Only re-compile modules with changed coverage models.

**Benefits:**
- Faster iteration during verification
- Scales to large designs

**Implementation:** Leverage Verilator's existing incremental compilation. Ensure coverage data structures are compatible.

### Opportunity 5: Coverage-Guided Fuzzing

**Description:** Integrate with fuzzing tools (e.g., AFL, libFuzzer) using coverage feedback.

**Benefits:**
- Find bugs faster
- Systematic exploration of state space

**Implementation:** Export coverage data in fuzzer-compatible format. Research project.

## Resource Requirements

### Development Effort Estimates

| Phase | Description | Estimated Effort | Dependencies |
|-------|-------------|------------------|--------------|
| 1 | Foundation | 4-6 weeks | None |
| 2 | Coverage Points | 6-8 weeks | Phase 1 |
| 3 | Cross Coverage | 4-6 weeks | Phase 2 |
| 4 | Advanced Bins | 3-4 weeks | Phase 2 |
| 5 | Coverage Computation | 3-4 weeks | Phases 2-4 |
| 6 | Output & Reporting | 4-5 weeks | Phase 5 |
| 7 | Advanced Features | 8-12 weeks | All previous |
| **Total** | **Core (1-6)** | **24-33 weeks** | |
| **Total** | **With Advanced** | **32-45 weeks** | |

**Note:** Estimates assume experienced C++ developer familiar with Verilator internals. First-time contributors may need 50-100% more time.

### Testing Requirements

- **Unit tests:** Each AST node type, each transformation pass
- **Regression tests:** ~50-100 test cases covering all features
- **Benchmark suite:** Performance tests for large covergroups
- **Compliance tests:** Match commercial simulator behavior
- **Integration tests:** Multi-module designs, coverage merging

### Documentation Requirements

- User guide: How to write covergroups in Verilator
- Reference manual: Supported features and limitations
- Migration guide: Differences from IEEE spec
- Example designs: Common coverage patterns
- Tool documentation: verilator_coverage updates

## Success Criteria

### Phase 1-2 Success (Minimum Viable Product)
- [ ] Parse covergroup syntax without errors
- [ ] Generate compilable C++ for simple covergroups
- [ ] Sample coverage points with automatic bins
- [ ] Output coverage data to file
- [ ] Basic coverage report showing bin hits

### Phase 3-6 Success (Production Ready)
- [ ] Cross coverage working correctly
- [ ] All bin types supported (user, auto, transition, ignore, illegal)
- [ ] `get_coverage()` returns correct percentages
- [ ] Coverage database merging works
- [ ] Performance acceptable (< 10% overhead vs. no coverage)
- [ ] Pass 90%+ of functional coverage regression tests

### Phase 7 Success (Feature Complete)
- [ ] Class-embedded covergroups
- [ ] Covergroup inheritance
- [ ] Dynamic instantiation
- [ ] Block event expressions
- [ ] UCIS export (optional)
- [ ] 100% IEEE compliance (or documented exceptions)

## Risk Assessment

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| Parser complexity too high | Medium | High | Start with subset, iterate |
| Performance unacceptable | Medium | High | Profile early, optimize incrementally |
| Memory overhead too large | Low | Medium | Use sparse storage, lazy allocation |
| Cross coverage explosion | Medium | High | Implement limits and warnings |
| User adoption low | Low | Medium | Good documentation, examples |
| IEEE compliance gaps | Medium | Low | Document limitations clearly |
| Integration issues | Low | High | Continuous integration testing |

## Next Steps and Decision Points

### Immediate Next Steps (Before Implementation)

1. **DECISION: Output format choice - APPROVED**
   - **Decision:** Extend SystemC::Coverage to version 4
   - Alternative considered: Create separate format
   - **Status:** Approved by stakeholder (MSB)

2. **DECISION: Static vs. dynamic instantiation - APPROVED**
   - **Decision:** Start with static instantiation, add dynamic support in Phase 7
   - **Rationale:** Static instantiation fits Verilator's compilation model and provides working functionality quickly. Dynamic instantiation will be required for the full feature to be useful to users, but can be deferred to a later phase.
   - **Status:** Approved by stakeholder (MSB)

3. **Prototype proof-of-concept (1-2 weeks)**
   - Simple covergroup with one coverpoint
   - Manual C++ generation (no parser)
   - Validate runtime infrastructure design
   - Measure performance baseline

4. **Create detailed Phase 1 design document**
   - AST node specifications
   - Code generation templates
   - Test plan

### Key Decision Points During Implementation

- **After Phase 1:** Continue with current architecture or pivot based on POC results?
- **After Phase 2:** Is performance acceptable? Need optimization?
- **After Phase 4:** Sufficient features for early adopters? Consider alpha release?
- **After Phase 6:** Ready for beta release?

## Compatibility and Limitations

### Known Limitations (Documented)

- **Initial release:**
  - No dynamic covergroup instantiation
  - No covergroup inheritance
  - No block event expressions `@@(begin/end)`
  - No coverage of real-valued expressions (only integral)
  - Limited support for covergroups in classes
  - No assertion-embedded sampling

- **By design (may never support):**
  - Covergroups in interfaces (low priority)
  - Coverage of virtual interface expressions (complex)
  - Some edge cases with X/Z handling

### Backward Compatibility

- Existing code coverage features unaffected
- Old coverage databases remain readable
- New format version allows graceful upgrade
- Command-line options remain compatible

## Conclusion

Implementing SystemVerilog functional coverage in Verilator is a significant undertaking that will greatly enhance its verification capabilities. By following a phased approach and leveraging existing infrastructure, we can deliver a robust implementation that meets the needs of the open-source verification community while maintaining Verilator's performance and usability standards.

The proposed architecture extends the existing coverage system rather than replacing it, minimizing risk and development effort. The key innovation is treating functional coverage as a new coverage type within the existing framework, using the same runtime infrastructure and output format.

**Recommended Path Forward:**
1. Validate architectural decisions via prototype (2 weeks)
2. Implement Phase 1-2 for MVP (10-14 weeks)
3. Alpha release for early feedback
4. Complete Phase 3-6 for production release (14-19 weeks)
5. Phase 7 advanced features based on user demand (8-12 weeks)

**Total estimated time to production-ready functional coverage: 6-8 months of focused development.**

---

## Appendix A: Example Coverage Output

### Example: Simple Covergroup

**SystemVerilog:**
```systemverilog
covergroup cg @(posedge clk);
  cp_addr: coverpoint addr {
    bins low = {[0:127]};
    bins high = {[128:255]};
  }
  cp_cmd: coverpoint cmd {
    bins read = {0};
    bins write = {1};
  }
  cross_cmd_addr: cross cp_cmd, cp_addr;
endgroup

cg cg_inst = new;
```

**Generated Coverage Output (SystemC::Coverage-4):**
```
# SystemC::Coverage-4
G 't=covergroup n=cg h=top.m_inst w=1 g=100'
C 't=coverpoint n=cg.cp_addr b=low r=0:127 h=top.m_inst' 450
C 't=coverpoint n=cg.cp_addr b=high r=128:255 h=top.m_inst' 320
C 't=coverpoint n=cg.cp_cmd b=read r=0 h=top.m_inst' 380
C 't=coverpoint n=cg.cp_cmd b=write r=1 h=top.m_inst' 390
C 't=cross n=cg.cross_cmd_addr b=<read,low> h=top.m_inst' 200
C 't=cross n=cg.cross_cmd_addr b=<read,high> h=top.m_inst' 180
C 't=cross n=cg.cross_cmd_addr b=<write,low> h=top.m_inst' 250
C 't=cross n=cg.cross_cmd_addr b=<write,high> h=top.m_inst' 140
```

## Appendix B: Generated C++ Structure (Conceptual)

**For covergroup above, generated C++ might look like:**

```cpp
class Vcg_cg {
  private:
    uint32_t m_cp_addr_low = 0;
    uint32_t m_cp_addr_high = 0;
    uint32_t m_cp_cmd_read = 0;
    uint32_t m_cp_cmd_write = 0;
    std::unordered_map<std::string, uint32_t> m_cross_cmd_addr;
    
  public:
    Vcg_cg() {
        // Register bins with VerilatedCovContext
        VL_COVER_INSERT(&m_cp_addr_low, "t", "coverpoint", "n", "cg.cp_addr", 
                        "b", "low", "r", "0:127", ...);
        VL_COVER_INSERT(&m_cp_addr_high, "t", "coverpoint", "n", "cg.cp_addr",
                        "b", "high", "r", "128:255", ...);
        // ... etc
    }
    
    void sample() {
        // Evaluate coverpoint expressions
        uint8_t addr_val = /* evaluate addr expression */;
        uint8_t cmd_val = /* evaluate cmd expression */;
        
        // Match bins and increment
        if (addr_val >= 0 && addr_val <= 127) m_cp_addr_low++;
        if (addr_val >= 128 && addr_val <= 255) m_cp_addr_high++;
        if (cmd_val == 0) m_cp_cmd_read++;
        if (cmd_val == 1) m_cp_cmd_write++;
        
        // Cross coverage
        std::string cross_key = /* format cross bin */;
        m_cross_cmd_addr[cross_key]++;
    }
    
    double get_coverage() { /* compute coverage % */ }
    double get_inst_coverage() { /* compute coverage % */ }
    void start() { /* enable sampling */ }
    void stop() { /* disable sampling */ }
};
```

## Appendix C: Phase 2 Detailed Design - Code Generation

### Overview

Phase 2 connects the runtime infrastructure (completed in Phase 1.2) with the parser and AST. The goal is to generate C++ code that instantiates and uses the `VerilatedCovergroup` classes.

### AST Node Design

Based on IEEE 1800-2023 Section 19.3, we need these AST node types:

```cpp
// Base covergroup node
class AstCovergroup final : public AstNode {
    // @astgen op1 := coveritemsp : List[AstCoverItem]
    // @astgen op2 := optionsp : Optional[List[AstCoverOption]]
    string m_name;         // Covergroup name
    bool m_hasEvent;       // Has clocking event
    AstSenTree* m_eventp;  // Clocking event (if any)
    
public:
    AstCovergroup(FileLine* fl, const string& name, 
                  AstNode* itemsp, AstSenTree* eventp)
        : AstNode{fl}, m_name{name}, m_eventp{eventp},
          m_hasEvent{eventp != nullptr} {}
    
    string name() const { return m_name; }
    bool hasEvent() const { return m_hasEvent; }
    // ... methods
};

// Coverage point
class AstCoverpoint final : public AstCoverItem {
    // @astgen op1 := exprp : AstNodeExpr       // Expression to cover
    // @astgen op2 := binsp : List[AstCoverBins] // Bin specifications
    // @astgen op3 := iffp : Optional[AstNodeExpr] // iff condition
    string m_name;         // Coverpoint name (optional)
    
public:
    AstCoverpoint(FileLine* fl, const string& name, 
                  AstNodeExpr* exprp, AstNode* binsp)
        : AstCoverItem{fl}, m_name{name} {}
};

// Bin specification
class AstCoverBins final : public AstNode {
    // @astgen op1 := rangesp : List[AstRange]  // Value ranges
    string m_name;         // Bin name
    VCoverBinsType m_type; // USER, AUTO, IGNORE, ILLEGAL, DEFAULT
    bool m_isArray;        // bins name[] vs bins name
    
public:
    AstCoverBins(FileLine* fl, VCoverBinsType type,
                 const string& name, AstNode* rangesp)
        : AstNode{fl}, m_name{name}, m_type{type}, m_isArray{false} {}
};

// Cross coverage
class AstCoverCross final : public AstCoverItem {
    // @astgen op1 := refsp : List[AstCoverpointRef]  // Coverpoints to cross
    // @astgen op2 := binsp : Optional[List[AstCoverCrossBins]]
    string m_name;
    
public:
    AstCoverCross(FileLine* fl, const string& name, AstNode* refsp)
        : AstCoverItem{fl}, m_name{name} {}
};
```

### Code Generation Strategy

**Location:** New file `src/V3EmitCFuncCov.cpp`

The code generator walks the AST and emits:
1. A C++ class for each covergroup type
2. Member variables for each coverpoint and bin
3. Constructor that registers bins with VerilatedCovContext
4. `sample()` method that evaluates expressions and updates bins
5. Coverage query methods

### Code Generation Templates

**Template 1: Covergroup Class Declaration**

```cpp
// In generated .h file
class V{module}_covergroup_{cgname} {
private:
    // Coverage infrastructure
    VerilatedCovergroup m_cg;
    
    // Coverage points
    {for each coverpoint}
    VerilatedCoverpoint m_cp_{cpname};
    {end}
    
    // Cross coverage
    {for each cross}
    VerilatedCoverCross m_cross_{crossname};
    {end}
    
    // Module context for expression evaluation
    V{module}* m_modp;
    
    // Enable/disable flag
    bool m_enabled = true;
    
public:
    V{module}_covergroup_{cgname}(V{module}* modp);
    ~V{module}_covergroup_{cgname}() = default;
    
    void sample();
    double get_coverage();
    double get_inst_coverage();
    void start() { m_enabled = true; }
    void stop() { m_enabled = false; }
    void set_inst_name(const char* name);
};
```

**Template 2: Constructor Implementation**

```cpp
V{module}_covergroup_{cgname}::V{module}_covergroup_{cgname}(V{module}* modp)
    : m_modp{modp}
    , m_cg{"cg", "{hierarchy}.{cgname}", {weight}, {goal}}
{
    // Create coverpoints
    {for each coverpoint cp}
    m_cp_{cpname}.init("{cpname}", "{hierarchy}.{cgname}.{cpname}");
    
    // Create bins for this coverpoint
    {for each bin in cp}
    m_cp_{cpname}.addBin("{binname}", {at_least}, 
                         {range_start}, {range_end});
    {end}
    
    m_cg.addCoverpoint(&m_cp_{cpname});
    {end}
    
    // Create cross coverage
    {for each cross}
    m_cross_{crossname}.init("{crossname}", 
                             "{hierarchy}.{cgname}.{crossname}");
    {for each coverpoint reference}
    m_cross_{crossname}.addCoverpoint(&m_cp_{cpref});
    {end}
    m_cg.addCross(&m_cross_{crossname});
    {end}
}
```

**Template 3: Sample Method**

```cpp
void V{module}_covergroup_{cgname}::sample() {
    if (!m_enabled) return;
    
    // Sample each coverpoint
    {for each coverpoint cp}
    {
        // Evaluate iff condition if present
        {if has_iff}
        if (!({iff_expression})) goto skip_{cpname};
        {endif}
        
        // Evaluate coverpoint expression
        {eval_type} {cpname}_val = {expression};
        
        // Sample the coverpoint
        m_cp_{cpname}.sample({cpname}_val);
        
        skip_{cpname}: ;
    }
    {end}
    
    // Sample cross coverage (automatically handled by crosses)
    {for each cross}
    m_cross_{crossname}.sample();
    {end}
}
```

### Example: From IEEE 1800-2023 Section 19.4

**SystemVerilog Input:**
```systemverilog
module mem_coverage(input clk, input [7:0] addr, input [1:0] cmd);
  covergroup cg_mem @(posedge clk);
    coverpoint addr {
      bins low = {[0:63]};
      bins mid = {[64:191]};
      bins high = {[192:255]};
    }
    coverpoint cmd {
      bins read = {0};
      bins write = {1};
      bins idle = {2,3};
    }
    cross addr, cmd;
  endgroup
  
  cg_mem cg_inst = new;
endmodule
```

**Generated C++ (conceptual):**
```cpp
// In Vmem_coverage.h
class Vmem_coverage_covergroup_cg_mem {
private:
    VerilatedCovergroup m_cg;
    VerilatedCoverpoint m_cp_addr;
    VerilatedCoverpoint m_cp_cmd;
    VerilatedCoverCross m_cross_addr_cmd;
    Vmem_coverage* m_modp;
    bool m_enabled = true;
    
public:
    Vmem_coverage_covergroup_cg_mem(Vmem_coverage* modp);
    void sample();
    double get_coverage() { return m_cg.get_coverage(); }
    // ...
};

// In Vmem_coverage.cpp
Vmem_coverage_covergroup_cg_mem::Vmem_coverage_covergroup_cg_mem(
    Vmem_coverage* modp)
    : m_modp{modp}
    , m_cg{"cg_mem", "mem_coverage.cg_inst", 1, 100}
{
    // Setup addr coverpoint
    m_cp_addr.init("addr", "mem_coverage.cg_inst.addr");
    m_cp_addr.addBin("low", 1, 0, 63);
    m_cp_addr.addBin("mid", 1, 64, 191);
    m_cp_addr.addBin("high", 1, 192, 255);
    m_cg.addCoverpoint(&m_cp_addr);
    
    // Setup cmd coverpoint
    m_cp_cmd.init("cmd", "mem_coverage.cg_inst.cmd");
    m_cp_cmd.addBin("read", 1, 0, 0);
    m_cp_cmd.addBin("write", 1, 1, 1);
    m_cp_cmd.addBin("idle", 1, 2, 3);  // Multiple values
    m_cg.addCoverpoint(&m_cp_cmd);
    
    // Setup cross
    m_cross_addr_cmd.init("addr_cmd", "mem_coverage.cg_inst.addr_cmd");
    m_cross_addr_cmd.addCoverpoint(&m_cp_addr);
    m_cross_addr_cmd.addCoverpoint(&m_cp_cmd);
    m_cg.addCross(&m_cross_addr_cmd);
}

void Vmem_coverage_covergroup_cg_mem::sample() {
    if (!m_enabled) return;
    
    // Sample addr
    uint8_t addr_val = m_modp->addr;
    m_cp_addr.sample(addr_val);
    
    // Sample cmd
    uint8_t cmd_val = m_modp->cmd;
    m_cp_cmd.sample(cmd_val);
    
    // Cross sampling happens automatically
    m_cross_addr_cmd.sample();
}
```

**In module class:**
```cpp
class Vmem_coverage {
    // ... other members
    Vmem_coverage_covergroup_cg_mem* m_cg_inst;
    
    Vmem_coverage() {
        m_cg_inst = new Vmem_coverage_covergroup_cg_mem(this);
    }
    
    void _eval_settle() {
        // ... existing code
        // Call sample on clocking event
        if (clk_posedge_triggered) {
            m_cg_inst->sample();
        }
    }
};
```

### Integration with V3Emit

The code generation will be integrated as follows:

1. **V3Coverage.cpp** - Identify covergroup nodes during coverage pass
2. **V3EmitCFuncCov.cpp** (NEW) - Generate covergroup C++ code
3. **V3EmitC.cpp** - Call covergroup emission for each module
4. **V3EmitCFunc.cpp** - Integrate sampling calls

### Key Implementation Decisions

**Q: Where to place sampling calls for clocking events?**
A: In the module's `_eval_settle()` or `_sequent()` methods, triggered by the appropriate edge detection.

**Q: How to handle covergroup instantiation?**
A: Generate constructor calls in module constructor. For now, support only static instantiation.

**Q: How to access module signals from covergroup?**
A: Pass module pointer (`this`) to covergroup constructor, allowing direct access to public members.

**Q: How to handle hierarchical names?**
A: Build hierarchy path during AST traversal, store in AstCovergroup node.

## Appendix D: IEEE 1800-2023 Key Excerpts

### Section 19.5: Defining coverage points

From IEEE 1800-2023:

> A coverage point defines a specific variable or expression to cover. The value sampled from a coverage
> point is associated with bins. Bins can be explicitly defined by the user or automatically created by the
> tool.

**Syntax (simplified):**
```systemverilog
coverpoint expression [ iff (condition) ] bins_or_options
```

**Key concepts:**
- **Expression**: Any valid SystemVerilog expression (integral types primarily)
- **iff condition**: Optional condition that must be true for sampling to occur
- **Bins**: User-defined or automatic buckets for values

### Section 19.6: Defining coverage bins

From IEEE 1800-2023:

> Bins represent a set of values or transitions for a coverage point. Each bin has an associated counter
> that is incremented every time the sampled value matches the bin's specification.

**Types of bins:**
- `bins`: Normal user-defined bins
- `bins[]`: Array of bins (one per value)
- `ignore_bins`: Values to exclude from coverage
- `illegal_bins`: Values that should never occur (error if hit)

**Example from IEEE spec:**
```systemverilog
coverpoint addr {
  bins low[] = {[0:7]};        // 8 separate bins
  bins med = {[8:127]};        // Single bin
  bins high = {[128:255]};     // Single bin
  ignore_bins invalid = {256}; // Excluded
}
```

### Section 19.7: Defining cross coverage

From IEEE 1800-2023:

> Cross coverage measures the cross product of bins of multiple coverage points. It is specified using
> the cross keyword followed by a list of coverage points and/or variables.

**Formula for cross coverage (from IEEE spec):**

Cross coverage = (# of covered cross bins) / (# of valid cross bins) × 100%

**Example:**
```systemverilog
cross cp_addr, cp_cmd;  // All combinations
```

If `cp_addr` has 3 bins and `cp_cmd` has 3 bins, the cross has 3×3 = 9 bins.

### Section 19.11: Coverage computation

From IEEE 1800-2023:

**Coverpoint coverage formula:**
```
coverpoint_coverage = (# bins hit >= at_least) / (total # bins) × 100%
```

**Covergroup instance coverage:**
```
instance_coverage = Σ(weight_i × coveritem_coverage_i) / Σ(weight_i)
```

Where coveritem includes both coverpoints and crosses.

**Covergroup type coverage:**
```
type_coverage = Σ(instance_weight_j × instance_coverage_j) / Σ(instance_weight_j)
```

## Appendix E: References

1. IEEE Std 1800-2023, Section 19 "Functional Coverage"
   - Available in: `references/sv_functional_coverage.md` and `.pdf`
2. Verilator source code documentation
   - `docs/internals.rst` - Comprehensive internal documentation
   - `references/verilator_developer_guide.md` - Developer best practices
3. Accellera UCIS 1.0 specification (for future UCIS export)
4. SystemVerilog LRM examples

## Appendix F: Glossary

- **Bin:** A bucket that counts how many times a particular value or set of values is sampled
- **Coverage point:** An expression whose values are tracked and binned
- **Covergroup:** A container that holds coverage points and cross coverage
- **Cross coverage:** Coverage of combinations of values from multiple coverage points
- **Type coverage:** Cumulative coverage across all instances of a covergroup type
- **Instance coverage:** Coverage of a specific covergroup instance
- **Transition bin:** A bin that matches sequences of values rather than individual values
- **at_least:** Minimum number of hits required for a bin to be considered covered
- **auto_bin_max:** Maximum number of automatically generated bins
- **per_instance:** Whether coverage is tracked separately for each instance
- **binsof:** Operator to reference bins from a coverpoint in cross coverage
- **iff condition:** Optional condition that gates sampling of a coverage point

## Appendix G: Development Workflow

### Daily Development Cycle

1. **Make changes** to AST, visitors, or code generation
2. **Build:**
   ```bash
   make -j$(nproc)
   ```
3. **Run targeted test:**
   ```bash
   test_regress/t/t_funccov_basic.py --debug
   ```
4. **Check generated code:**
   ```bash
   ls obj_dir/
   view obj_dir/Vt_funccov_basic__funccov.cpp
   ```
5. **Debug if needed:**
   ```bash
   test_regress/t/t_funccov_basic.py --debug --gdb
   ```

### Adding a New Feature

1. **Update AST nodes** if needed (src/V3Ast*.h)
2. **Update parser** if syntax changes (src/verilog.y)
3. **Create/modify visitor pass** (src/V3*.cpp)
4. **Update code generation** (src/V3EmitC*.cpp)
5. **Add test case** (test_regress/t/t_funccov_<feature>.v/.py)
6. **Run test:**
   ```bash
   test_regress/t/t_funccov_<feature>.py
   ```
7. **Format code:**
   ```bash
   make format
   ```
8. **Run full regression:**
   ```bash
   make test -j$(nproc)
   ```

### Debugging Techniques

**1. AST Dumps:**
```bash
verilator --debug --coverage test.v
# Check obj_dir/Vtest_*.tree files
```

**2. Coverage Database Inspection:**
```bash
# After test runs, examine coverage data
cat test_dir/coverage.dat
verilator_coverage --annotate output test_dir/coverage.dat
```

**3. GDB Session:**
```bash
test_regress/t/t_funccov_basic.py --gdb
# In GDB:
break V3EmitCFuncCov.cpp:123
run
pn nodep  # Print node
```

**4. Enable Verbose Output:**
```bash
verilator --debug-check --dump-tree --coverage test.v
```

## Appendix H: Testing Strategy

### Test Categories

**Unit Tests:**
- Individual bin matching
- Coverage computation algorithms
- Cross product generation
- Sparse storage operations

**Integration Tests:**
- Simple covergroup with automatic bins (t_funccov_basic)
- User-defined bins with ranges (t_funccov_bins)
- Cross coverage (t_funccov_cross)
- iff conditions (t_funccov_iff)
- Clocking events (t_funccov_event)
- Multiple instances (t_funccov_multi)

**Compliance Tests:**
- Compare against commercial simulator output
- IEEE 1800-2023 example code from Section 19
- Edge cases from specification

**Performance Tests:**
- Large number of bins (1000+)
- Deep cross coverage (4+ dimensions)
- High sampling rate (every cycle)
- Memory usage measurement

### Test Plan for Phase 2

| Test Name | Description | Expected Result | Status |
|-----------|-------------|-----------------|--------|
| t_funccov_basic | Simple covergroup, auto bins | PASS, coverage output | ✅ |
| t_funccov_user_bins | User-defined bins | PASS, correct bin hits | TODO |
| t_funccov_ranges | Bins with ranges [0:255] | PASS, range matching | TODO |
| t_funccov_iff | iff condition filtering | PASS, conditional sampling | TODO |
| t_funccov_event | @(posedge clk) sampling | PASS, event-driven | TODO |
| t_funccov_cross_simple | 2-way cross | PASS, cross bins | TODO |
| t_funccov_ignore | ignore_bins directive | PASS, bins excluded | TODO |
| t_funccov_illegal | illegal_bins with error | FAIL at runtime | TODO |
| t_funccov_get_coverage | Query coverage % | PASS, correct calculation | TODO |
| t_funccov_multi_inst | Multiple instances | PASS, separate tracking | TODO |

### Continuous Integration

**Pre-commit checks:**
- `make format` (clang-format)
- Basic compilation
- Quick smoke tests

**Full CI pipeline:**
- Build on Linux/macOS/Windows
- Full regression suite
- Coverage analysis (code coverage of Verilator itself)
- Performance benchmarks
- Documentation build

---

**Document Version:** 1.1  
**Date:** 2026-02-07  
**Status:** LIVING DOCUMENT - Updated with Phase 2 details and implementation guidance
