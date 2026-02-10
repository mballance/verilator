#!/bin/bash
# Script to test functional coverage implementation
# Run individual tests and collect results

set -e

VERILATOR_ROOT=$(pwd)
export VERILATOR_ROOT

echo "========================================="
echo "Functional Coverage Test Suite"
echo "========================================="
echo ""

# Find all functional coverage tests
TESTS=(
    "t_covergroup_minimal"
    "t_covergroup_simple"
    "t_covergroup_iff"
    "t_covergroup_bins_default_illegal"
    "t_covergroup_bins_advanced"
    "t_covergroup_coverage_pct"
    "t_covergroup_cross_simple"
    "t_covergroup_cross_3way"
    "t_covergroup_cross_4way"
    "t_covergroup_dynamic"
    "t_covergroup_trans_simple"
)

PASSED=0
FAILED=0
FAILED_TESTS=()

for test in "${TESTS[@]}"; do
    echo -n "Testing $test... "
    
    # Run just this one test
    if cd test_regress && python3 driver.py --vlt --quiet --stop t/${test}.v >/dev/null 2>&1; then
        echo "✅ PASS"
        ((PASSED++))
    else
        echo "❌ FAIL"
        ((FAILED++))
        FAILED_TESTS+=("$test")
    fi
    cd "$VERILATOR_ROOT"
done

echo ""
echo "========================================="
echo "Results: $PASSED passed, $FAILED failed"
echo "========================================="

if [ $FAILED -gt 0 ]; then
    echo ""
    echo "Failed tests:"
    for test in "${FAILED_TESTS[@]}"; do
        echo "  - $test"
    done
    exit 1
fi

exit 0
