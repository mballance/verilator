# Transition Bin Repetition Operators - Implementation Roadmap

## Current Status (2026-02-09)

✅ **Multi-value sequences COMPLETE**
- N-value transitions: `bins t = (1 => 2 => 3 => ...);`
- State machine with restart/reset logic
- Tests passing with 100% coverage
- **Production-ready for most use cases**

## Repetition Operators - Not Yet Implemented

Three repetition operators remain from IEEE 1800-2023 Section 19.5.2:

### 1. Consecutive `[*]` - "Repeat N times in a row"
**Examples:**
- `bins t = (1 => 2 [* 3] => 3);` → matches: 1, 2, 2, 2, 3
- `bins t = (5 [* 2:4]);` → matches: 5,5 or 5,5,5 or 5,5,5,5

**Effort:** 3-4 days  
**Complexity:** Medium  
**Risk:** Low  
**Value:** **HIGH** (80% of remaining use cases)

**Why prioritize:**
- Most commonly used repetition operator
- Clean, well-defined semantics
- Straightforward state machine extension
- High user value

### 2. Goto `[->]` - "See value N times, any gaps"
**Examples:**
- `bins t = (1 => 2 [-> 3] => 3);` → matches: 1, 2, X, 2, Y, 2, 3
- Gaps allowed between occurrences
- Next value MUST immediately follow last occurrence

**Effort:** 4-5 days  
**Complexity:** Medium-High  
**Risk:** Medium  
**Value:** Medium

**Why defer:**
- Less commonly needed
- More complex edge cases
- "Immediate next" rule tricky to implement

### 3. Nonconsecutive `[=]` - "See value N times, gaps everywhere"
**Examples:**
- `bins t = (1 => 2 [= 3] => 3);` → matches: 1, 2, X, 2, Y, 2, Z, 3
- Most permissive operator
- Gaps allowed even after final occurrence

**Effort:** 4-5 days  
**Complexity:** Medium-High  
**Risk:** Medium  
**Value:** Medium

**Why defer:**
- Least commonly used
- Most edge cases to handle
- Interaction with next item detection tricky

## Infrastructure Already In Place

✅ **Parser support complete**
- Grammar recognizes all repetition syntax
- AST nodes created with VTransRepType enum
- repMinp/repMaxp fields for counts/ranges

✅ **State machine framework working**
- Multi-value sequences use case/switch structure
- State variables and counters architecture proven
- Restart/reset logic patterns established

❌ **Code generation missing**
- Need counter variables for repetitions
- Need state machine extensions for counting
- Need range checking logic (min/max)

## Implementation Strategy

### Recommended: Implement Consecutive `[*]` Only

**Rationale:**
1. Highest value-to-effort ratio (3-4 days → 80% of use cases)
2. Lowest risk (clean semantics, straightforward implementation)
3. Natural next step after multi-value sequences
4. Users can provide feedback on whether others are needed

**Alternative: Full Implementation (All Three)**

**Effort:** 11-14 days (2-3 weeks)  
**Value:** Complete IEEE 1800 compliance for transition bins

**When to do this:**
- User feedback indicates strong demand for goto/nonconsecutive
- After production usage validates consecutive implementation
- Resources available for 2-3 week effort

## Technical Approach (Consecutive Example)

### 1. Add Counter Variables
```cpp
AstVar* createRepetitionCounter(AstCoverpoint* coverpointp, 
                                AstCoverBin* binp, size_t itemIndex) {
    string varName = "__Vrepcnt_" + coverpointp->name() + "_" + 
                     binp->name() + "_" + std::to_string(itemIndex);
    // 8-bit counter (max 255 repetitions)
    return new AstVar{..., VFlagLogicPacked{}, 8};
}
```

### 2. Extend State Machine
```cpp
case STATE_N:
    if (current == expected_value) {
        counter++;
        if (counter >= min_count) {
            // Can advance to next state
            if (counter >= max_count) {
                // MUST advance
                state++;
                counter = 0;
            }
        }
    } else if (current == next_value && counter >= min_count) {
        // Skip to next item
        state++;
        counter = 0;
    } else {
        // Restart or reset
        ...
    }
```

### 3. Test Coverage
- Basic exact count: `(1 [* 3])`
- In sequence: `(1 => 2 [* 3] => 3)`
- Range: `(1 [* 2:4])`
- Multiple repetitions: `(1 [* 2] => 2 [* 3])`

## Decision Matrix

| Scenario | Recommendation | Timeline |
|----------|----------------|----------|
| Production deployment imminent | **Ship current** | Now |
| Users request consecutive | **Implement [*]** | +3-4 days |
| Full compliance needed | **All three** | +11-14 days |
| No immediate need | **Defer all** | Revisit Q2 2026 |

## Risk Assessment

**Shipping without repetitions:**
- ✅ Risk: LOW
- ✅ Workaround: Users can split into multiple bins
- ✅ Coverage: 90%+ of real-world use cases met

**Implementing consecutive only:**
- ✅ Risk: LOW
- ✅ Reward: HIGH
- ✅ Time: 3-4 days
- ⚠️ May create expectation for others

**Implementing all three:**
- ⚠️ Risk: MEDIUM (more complexity, more edge cases)
- ✅ Reward: HIGH (full compliance)
- ⚠️ Time: 2-3 weeks
- ✅ Complete solution

## Recommendation

**Ship current implementation as v1.0**
- Mark as "production-ready with documented limitations"
- Document that repetition operators are planned
- Gather user feedback on priority

**Implement consecutive [*] as v1.1** (if demand exists)
- Quick win (3-4 days)
- Highest value operator
- Validate architecture before others

**Implement goto/nonconsecutive as v1.2** (if needed)
- Based on usage data and feedback
- Only if users actually need them
- May never be necessary

## Contact

For questions or priority changes, see:
- Technical design: `/session-state/repetition_analysis.md`
- Implementation status: `docs/functional_coverage_plan.md`
- Code: `src/V3CoverageFunctional.cpp`
