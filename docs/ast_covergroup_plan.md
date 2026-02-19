# Implementation Plan: AstCovergroup Node Type

**Author**: Implementation plan for Verilator functional coverage enhancement
**Date**: February 2026
**Status**: Planning phase

## Executive Summary

**Objective**: Create dedicated `AstCovergroup` AST node type to replace `AstClass` with `isCovergroup()` flag

**Motivation**:
- Addresses TODO comment in codebase: "TODO perhaps make a new Ast node type for CG?"
- Better type safety (compiler enforces correct usage)
- Cleaner architecture (no covergroup-specific fields in AstClass)
- Easier maintenance (separate concerns)
- Matches SystemVerilog semantics (covergroups are not classes)

**Effort Estimate**: 20 hours (2-3 days)
**Risk Level**: Low-Medium (phased approach with rollback points)
**Breaking Changes**: None user-facing (internal AST only)

## Background

Currently, covergroups are represented as `AstClass` nodes with a boolean flag:
- `bool m_covergroup = false` distinguishes covergroups from classes
- `isCovergroup()` checked in ~6 locations
- Covergroup-specific fields (e.g., `m_autoBinMax`) stored in AstClass
- TODO comment suggests this should be improved

**Why now?** The recent addition of `option.auto_bin_max` support highlighted the architectural issue. Adding more covergroup features will further pollute the AstClass namespace.

---

## Implementation Phases

### Phase 1: Create Node Type (2 hours)
**Status**: Not started
**Risk**: Low
**Can Abort?**: Yes

**Goal**: Define the new node type without changing any behavior

#### Step 1.1: Define AstCovergroup class
**File**: `src/V3AstNodeOther.h`
**Location**: After `AstClassPackage` definition (~line 2660)

```cpp
class AstCovergroup final : public AstNodeModule {
    // A covergroup declaration (functional coverage construct)
    // Unlike AstClass, this is purely for coverage collection, not object orientation
    // @astgen op4 := extendsp : List[AstClassExtends]  // Reserved for future use
    // MEMBERS
    // @astgen ptr := m_classOrPackagep : Optional[AstClassPackage]  // Package to emit with
    uint32_t m_declTokenNum;  // Declaration token number
    int m_autoBinMax = -1;  // option.auto_bin_max (-1 = use global default)
    // Additional covergroup options can be added here as needed:
    // int m_atLeast = 1;      // option.at_least
    // int m_weight = 1;       // option.weight
    // int m_goal = 100;       // option.goal
    // bool m_perInstance = false;  // option.per_instance

public:
    AstCovergroup(FileLine* fl, const string& name, const string& libname)
        : ASTGEN_SUPER_Covergroup(fl, name, libname)
        , m_declTokenNum{fl->tokenNum()} {}
    ASTGEN_MEMBERS_AstCovergroup;

    // Overrides from AstNodeModule
    string verilogKwd() const override { return "covergroup"; }
    bool maybePointedTo() const override VL_MT_SAFE { return true; }
    void dump(std::ostream& str) const override;
    void dumpJson(std::ostream& str) const override;
    bool timescaleMatters() const override { return false; }

    // Accessors matching AstClass interface (for compatibility during migration)
    AstClassPackage* classOrPackagep() const VL_MT_STABLE { return m_classOrPackagep; }
    void classOrPackagep(AstClassPackage* classpackagep) { m_classOrPackagep = classpackagep; }
    AstNode* membersp() const VL_MT_STABLE { return stmtsp(); }
    void addMembersp(AstNode* nodep) { addStmtsp(nodep); }

    // Covergroup-specific accessors
    int autoBinMax() const { return m_autoBinMax; }
    void autoBinMax(int value) { m_autoBinMax = value; }

    uint32_t declTokenNum() const override { return m_declTokenNum; }
    void declTokenNumSetMin(uint32_t tokenNum) override {
        m_declTokenNum = std::min(m_declTokenNum, tokenNum);
    }
};
```

**Rationale**:
- Inherits from `AstNodeModule` (same base as AstClass, AstIface, AstPackage)
- Uses ASTGEN macros for automatic code generation
- Includes only covergroup-specific fields
- Provides compatible interface for gradual migration
- Comments indicate future extensibility

**Validation**: `make -j8` succeeds

#### Step 1.2: Add dump implementations
**File**: `src/V3AstNodes.cpp`
**Location**: After AstClassPackage dump methods (~line 1850)

```cpp
void AstCovergroup::dump(std::ostream& str) const {
    this->AstNodeModule::dump(str);
    if (m_autoBinMax >= 0) str << " [autobinmax:" << m_autoBinMax << "]";
}

void AstCovergroup::dumpJson(std::ostream& str) const {
    AstNodeModule::dumpJson(str);
    if (m_autoBinMax >= 0) dumpJsonInt(str, "autoBinMax", m_autoBinMax);
}
```

**Validation**: `make -j8` succeeds

**Commit**: "Add AstCovergroup node type (infrastructure only)"

---

### Phase 2: Parser Integration (3 hours)
**Status**: Not started
**Risk**: Medium
**Can Abort?**: Yes (revert parser change)

**Goal**: Parse to AstCovergroup but convert to AstClass to keep existing flow working

#### Step 2.1: Update parser
**File**: `src/verilog.y`
**Location**: Find `covergroup_declaration` rule (~line 6902)

**Current pattern** (find and examine):
```yacc
covergroup_declaration:
    yCOVERGROUP idAny/*covergroup_identifier*/ ...
    {
        // Currently creates AstClass
        AstClass* classp = new AstClass(...);
        classp->isCovergroup(true);
        ...
    }
```

**New pattern**:
```yacc
covergroup_declaration:
    yCOVERGROUP idAny/*covergroup_identifier*/ foptional_ports ';'
        { GRAMMARP->m_withinCovergroup = true; }
        coverage_event__ETC
    {
        GRAMMARP->m_withinCovergroup = false;
        // Create AstCovergroup instead of AstClass
        AstCovergroup* cgp = new AstCovergroup{$1, *$2, ""};
        cgp->addMembersp($6);
        // ... rest of setup same as before
        $$ = cgp;
        SYMP->reinsert(cgp);
    }
```

**Validation**:
- `make -j8` succeeds
- `bin/verilator --debug-parse test_regress/t/t_covergroup_autobins.v 2>&1 | grep -i covergroup`
- AST dump shows AstCovergroup nodes created

#### Step 2.2: Add temporary conversion pass
**File**: `src/V3LinkDot.cpp`
**Location**: In `LinkDotFindVisitor` class (add new visitor method)

**Purpose**: Maintain backwards compatibility while new visitors are being written

```cpp
void visit(AstCovergroup* nodep) override {
    // TEMPORARY: Convert AstCovergroup to AstClass to keep existing passes working
    // This will be removed in Phase 4 once all visitors are updated

    AstClass* classp = new AstClass{nodep->fileline(), nodep->name(), nodep->libname()};
    classp->isCovergroup(true);

    // Copy covergroup properties
    if (nodep->autoBinMax() >= 0) {
        classp->autoBinMax(nodep->autoBinMax());
    }
    if (nodep->classOrPackagep()) {
        classp->classOrPackagep(nodep->classOrPackagep());
    }
    classp->declTokenNumSetMin(nodep->declTokenNum());

    // Move members
    if (nodep->membersp()) {
        classp->addMembersp(nodep->membersp()->unlinkFrBackWithNext());
    }

    // Replace in tree
    nodep->replaceWith(classp);
    VL_DO_DANGLING(nodep->deleteTree(), nodep);

    // Continue visiting the replacement
    iterateChildren(classp);
}
```

**Validation**:
- `make -j8` succeeds
- `./test_funccov.sh t_covergroup_autobins` passes
- All covergroup tests pass
- AST dumps show conversion happens early

**Commit**: "Parser: Create AstCovergroup nodes (with temporary conversion)"

**Rollback Point**: Can keep both paths working indefinitely from here

---

### Phase 3: Migrate Visitors (6 hours)
**Status**: Not started
**Risk**: Medium
**Can Abort?**: Yes (comment out new visitors)

**Goal**: Add native AstCovergroup visitors so conversion is no longer needed

#### Step 3.1: Update V3CoverageFunctional.cpp

**Add member variable** (in FunctionalCoverageVisitor class):
```cpp
AstNodeModule* m_covergroupp = nullptr;  // Current covergroup (base type for both)
```

**Add new visitor**:
```cpp
void visit(AstCovergroup* nodep) override {
    UINFO(9, "Visiting covergroup: " << nodep->name() << endl);
    VL_RESTORER(m_covergroupp);
    m_covergroupp = nodep;
    m_sampleFuncp = nullptr;
    m_constructorp = nullptr;
    m_coverpoints.clear();
    m_coverCrosses.clear();

    // Find sample() method and constructor
    for (AstNode* itemp = nodep->membersp(); itemp; itemp = itemp->nextp()) {
        if (AstFunc* const funcp = VN_CAST(itemp, Func)) {
            if (funcp->name() == "sample") {
                m_sampleFuncp = funcp;
            } else if (funcp->name() == "new") {
                m_constructorp = funcp;
            }
        }
    }

    // Process members
    iterateChildren(nodep);
}
```

**Update getCovergroupAutoBinMax** (make it work with both types):
```cpp
int getCovergroupAutoBinMax(AstNodeModule* covergroupp) {
    // Try AstCovergroup first (preferred)
    if (AstCovergroup* cgp = VN_CAST(covergroupp, Covergroup)) {
        const int autoBinMax = cgp->autoBinMax();
        if (autoBinMax >= 0) {
            UINFO(4, "Using option.auto_bin_max=" << autoBinMax
                  << " for " << cgp->name() << endl);
            return autoBinMax;
        }
    }
    // Fallback to AstClass (during transition period)
    else if (AstClass* classp = VN_CAST(covergroupp, Class)) {
        if (classp->isCovergroup()) {
            const int autoBinMax = classp->autoBinMax();
            if (autoBinMax >= 0) {
                UINFO(4, "Using option.auto_bin_max=" << autoBinMax
                      << " for " << classp->name() << " (legacy)" << endl);
                return autoBinMax;
            }
        }
    }

    // Use global default
    UINFO(4, "Using global --coverage-auto-bin-max="
          << v3Global.opt.coverageAutoBinMax() << endl);
    return v3Global.opt.coverageAutoBinMax();
}
```

**Validation**:
- `make -j8` succeeds
- `./test_funccov.sh t_covergroup_autobins` passes with both code paths

#### Step 3.2: Update V3Width.cpp

**Add visitor**:
```cpp
void visit(AstCovergroup* nodep) override {
    // Process covergroup members (same as classes)
    iterateChildren(nodep);
}
```

**Update CgOptionAssign visitor** (handle both types):
```cpp
void visit(AstCgOptionAssign* nodep) override {
    if (!nodep->typeOption() && nodep->name() == "auto_bin_max") {
        if (const AstConst* const constp = VN_CAST(nodep->valuep(), Const)) {
            // Walk up to find parent covergroup or class
            AstNode* parentp = nodep->backp();
            while (parentp && !VN_IS(parentp, NodeFTask)) {
                parentp = parentp->backp();
            }
            if (AstNodeFTask* const ftaskp = VN_CAST(parentp, NodeFTask)) {
                AstNode* classMemberp = ftaskp;
                while (classMemberp &&
                       !VN_IS(classMemberp->backp(), Covergroup) &&
                       !VN_IS(classMemberp->backp(), Class)) {
                    classMemberp = classMemberp->backp();
                }

                // Prefer AstCovergroup
                if (AstCovergroup* const cgp = VN_CAST(classMemberp->backp(), Covergroup)) {
                    cgp->autoBinMax(constp->toSInt());
                }
                // Fallback to AstClass (transition period)
                else if (AstClass* const classp = VN_CAST(classMemberp->backp(), Class)) {
                    if (classp->isCovergroup()) {
                        classp->autoBinMax(constp->toSInt());
                    }
                }
            }
        }
    }
    VL_DO_DANGLING(pushDeletep(nodep->unlinkFrBack()), nodep);
}
```

**Validation**:
- `make -j8` succeeds
- Options correctly extracted for both node types

#### Step 3.3: Update V3Active.cpp

**Widen map type** (from AstClass* to AstNodeModule*):
```cpp
// Support both AstCovergroup and AstClass during transition
std::unordered_map<const AstNodeModule*, AstSenTree*> s_covergroupEvents;
std::unordered_map<const AstNodeModule*, AstCFunc*> s_covergroupSampleFuncs;
```

**Add visitor**:
```cpp
void visit(AstCovergroup* nodep) override {
    // Process automatic sampling (same logic as AstClass covergroups)
    // The base type AstNodeModule* in maps handles both
    // ... existing logic works unchanged
}
```

**Validation**:
- `make -j8` succeeds
- Clocked covergroups work with both types

**Commit**: "Add native AstCovergroup support to core visitors"

**Rollback Point**: Can keep both paths working if needed

---

### Phase 4: Remove Conversion (2 hours)
**Status**: Not started
**Risk**: Low
**Can Abort?**: Yes (restore conversion pass)

**Goal**: Make AstCovergroup the primary path, no conversion to AstClass

#### Step 4.1: Remove conversion pass
**File**: `src/V3LinkDot.cpp`

**Change**:
```cpp
void visit(AstCovergroup* nodep) override {
    // Conversion removed - AstCovergroup now flows natively through pipeline
    iterateChildren(nodep);
}
```

**Validation**:
- `make -j8` succeeds
- All tests pass
- No AstClass with isCovergroup()=true should exist after parsing

#### Step 4.2: Add assertion
**File**: `src/V3CoverageFunctional.cpp`

**Add safety check**:
```cpp
void visit(AstClass* nodep) override {
    // Covergroups should now be AstCovergroup, not AstClass
    UASSERT_OBJ(!nodep->isCovergroup(), nodep,
                "Covergroups should use AstCovergroup node type");
    // Regular class handling
    ...
}
```

**Validation**:
- No assertions trigger
- AST dumps show pure AstCovergroup flow

**Commit**: "Remove AstCovergroup to AstClass conversion"

**Rollback Point**: Last safe stopping point before cleanup

---

### Phase 5: Clean Up AstClass (3 hours)
**Status**: Not started
**Risk**: Low
**Must Complete**: Once started, should finish

**Goal**: Remove covergroup-specific code from AstClass

#### Step 5.1: Remove fields from AstClass
**File**: `src/V3AstNodeOther.h`

**Remove from AstClass member variables**:
```cpp
// DELETE these lines:
- int m_autoBinMax = -1;  // Covergroup option.auto_bin_max
- bool m_covergroup = false;  // Is covergroup
```

**Remove from AstClass methods**:
```cpp
// DELETE these methods:
- bool isCovergroup() const { return m_covergroup; }
- void isCovergroup(bool flag) { m_covergroup = flag; }
- int autoBinMax() const { return m_autoBinMax; }
- void autoBinMax(int value) { m_autoBinMax = value; }
```

**Update verilogKwd**:
```cpp
// CHANGE:
- string verilogKwd() const override { return isCovergroup() ? "covergroup" : "class"; }
+ string verilogKwd() const override { return "class"; }
```

**Validation**: `make -j8` succeeds

#### Step 5.2: Remove isCovergroup() calls
**Action**: Find and update all calls

```bash
grep -rn "isCovergroup()" src/*.cpp
```

**Expected locations** (~6 total):
1. `src/V3Active.cpp` - Remove check or use VN_IS(nodep, Covergroup)
2. `src/V3AstNodes.cpp` - Update dump methods
3. `src/V3CoverageFunctional.cpp` - Already has assertion
4. `src/V3Width.cpp` - Remove check

**For each location**: Either remove or replace with:
```cpp
// OLD:
if (classp->isCovergroup()) { ... }

// NEW (if needed):
if (VN_IS(nodep, Covergroup)) { ... }
```

**Validation**:
- `make -j8` succeeds
- No grep hits for `isCovergroup()`
- All tests pass

**Commit**: "Remove covergroup-specific code from AstClass"

---

### Phase 6: Final Testing & Documentation (4 hours)
**Status**: Not started
**Risk**: Low

**Goal**: Comprehensive validation and documentation

#### Step 6.1: Run full test suite
```bash
cd test_regress
perl driver.pl --scenarios --coverage
```

**Expected**: All tests pass

#### Step 6.2: Test covergroup features
```bash
./test_funccov.sh all
```

**Validate**:
- Autobins with options
- Clocked sampling
- Cross coverage
- Ignore bins
- Illegal bins

#### Step 6.3: Performance check
Compare compilation times before/after on large designs

#### Step 6.4: Update documentation

**Remove TODO comment**:
**File**: `src/V3AstNodeOther.h` (line ~2552)
```cpp
// DELETE:
- bool m_covergroup = false;  // Is covergroup (TODO perhaps make a new Ast node type for CG?)
```

**Add explanation comment**:
**File**: `src/V3AstNodeOther.h` (before AstCovergroup definition)
```cpp
// AstCovergroup - SystemVerilog covergroup construct
// Separate from AstClass because covergroups have different semantics:
// - Cannot be extended (except by SystemVerilog's "extend" feature)
// - Have coverage-specific options (auto_bin_max, at_least, etc.)
// - Generate different code (coverage collection, not object instantiation)
// Previously represented as AstClass with m_covergroup flag (pre-2026)
```

**Update internal documentation** (if exists):
- docs/internals/ast.rst or similar
- Mention separation of concerns
- Document migration history

**Commit**: "Document AstCovergroup node type"

---

## Key Files Modified

| File | Phase | Changes |
|------|-------|---------|
| `src/V3AstNodeOther.h` | 1, 5 | Add AstCovergroup, remove from AstClass |
| `src/V3AstNodes.cpp` | 1, 5 | Add dumps, update AstClass dumps |
| `src/verilog.y` | 2 | Create AstCovergroup in parser |
| `src/V3LinkDot.cpp` | 2, 4 | Add conversion, then remove |
| `src/V3CoverageFunctional.cpp` | 3, 5 | Add visitor, remove checks |
| `src/V3Width.cpp` | 3, 5 | Add visitor, update CgOptionAssign |
| `src/V3Active.cpp` | 3, 5 | Widen types, add visitor |
| Various emit files | 3 | May need visitors (TBD) |

---

## Success Criteria

All must pass:

- [x] Build succeeds (`make clean && make -j8`)
- [ ] All regression tests pass
- [ ] Covergroup tests pass (`./test_funccov.sh all`)
- [ ] `t_covergroup_autobins` passes with full assertions
- [ ] No `AstClass` with `isCovergroup()=true` in pipeline
- [ ] No `grep -rn "isCovergroup()" src/*.cpp` hits
- [ ] Generated C++ code unchanged (compare before/after)
- [ ] Coverage data format unchanged
- [ ] No performance regression (compare build times)
- [ ] AST dumps show `AstCovergroup` nodes
- [ ] Clean git history with logical commits

---

## Risk Analysis

### Low Risk Items
- Phase 1: Just adding a class definition
- Phase 4: Removing conversion (easily reverted)
- Phase 5: Cleanup (well-defined changes)
- Phase 6: Testing and docs

### Medium Risk Items
- Phase 2: Parser changes (mitigated by conversion pass)
- Phase 3: Visitor updates (mitigated by supporting both types)

### Mitigation Strategies
1. **Phased approach**: Can stop after any phase
2. **Parallel paths**: Both node types work during transition
3. **Assertions**: Catch mistakes early
4. **Grep patterns**: Find all uses systematically
5. **Rollback points**: Clear points to revert to

---

## Rollback Procedure

### If issues in Phase 1-2
```bash
git revert <commit>
make clean && make -j8
```
**Impact**: Minimal, just removes new code

### If issues in Phase 3
```bash
# Comment out new visitors
# Keep conversion pass
```
**Impact**: Return to Phase 2 state

### If issues in Phase 4
```bash
# Re-enable conversion pass in V3LinkDot.cpp
```
**Impact**: Return to Phase 3 state

### If issues in Phase 5
**Cannot rollback easily** - must complete or restore fields
**Prevention**: Don't start Phase 5 until Phase 4 is solid

---

## Timeline Estimate

### Conservative (thorough testing)
- Phase 1: 2 hours
- Phase 2: 3 hours (parser debugging)
- Phase 3: 6 hours (multiple files, testing)
- Phase 4: 2 hours (validation)
- Phase 5: 3 hours (careful cleanup)
- Phase 6: 4 hours (comprehensive testing)
**Total: 20 hours (~3 working days)**

### Optimistic (smooth implementation)
- All phases: 12-15 hours (~2 days)

### Realistic
- Expect 15-18 hours (~2-2.5 days)

---

## Commit Strategy

One commit per major phase:

1. **"Add AstCovergroup node type (infrastructure)"**
   - Defines class, adds dumps
   - No behavior change
   - ~150 lines added

2. **"Parser: Create AstCovergroup nodes (with conversion)"**
   - Updates parser
   - Adds temporary conversion
   - Tests still pass
   - ~100 lines changed

3. **"Add native AstCovergroup support to visitors"**
   - Adds visitors to core passes
   - Both paths work
   - ~300 lines changed

4. **"Remove AstCovergroup conversion, use native flow"**
   - Removes conversion
   - Adds assertions
   - Pure AstCovergroup flow
   - ~50 lines changed

5. **"Remove covergroup code from AstClass"**
   - Cleans up AstClass
   - Removes flags and methods
   - ~100 lines removed

6. **"Document AstCovergroup node type"**
   - Updates comments
   - Removes TODO
   - ~50 lines changed

**Total code change**: ~+400/-100 lines (net +300)

---

## Questions for Reviewers

1. **Should we add more covergroup options now?** (at_least, weight, goal, per_instance)
   - **Recommendation**: Start with just auto_bin_max, add others incrementally

2. **Should AstCovergroup support extension?** (op4 := extendsp)
   - **Recommendation**: Reserve op4 but don't implement until needed

3. **Should we update verilated code format?** (to distinguish covergroups)
   - **Recommendation**: No, keep generated code unchanged

4. **Backport to stable branch?**
   - **Recommendation**: No, this is an internal refactoring (next major release)

---

## Benefits Summary

### Type Safety
- Compiler catches covergroup/class confusion
- No more runtime checks needed
- Clearer code intent

### Maintainability
- Separate concerns (coverage vs objects)
- Easier to add covergroup features
- Smaller, focused classes

### Performance
- Slightly smaller AstClass (two fields removed)
- No performance regression expected
- May enable future optimizations

### Code Quality
- Removes TODO debt
- Matches semantic reality
- Better self-documenting code

---

## Conclusion

This plan provides a **safe, incremental approach** to creating `AstCovergroup`. The phased implementation with rollback points minimizes risk while improving code quality.

**Recommendation**: Proceed with implementation, following the phase structure strictly.

**Next Step**: Begin Phase 1, Step 1.1 (define AstCovergroup class)
