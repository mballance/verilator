#!/bin/bash
# Comprehensive coverage test runner

export VERILATOR_ROOT=$(pwd)
TOTAL=0
PASSED=0
V_FAIL=0
C_FAIL=0
R_FAIL=0
BAD_TESTS=0

echo "Running all functional coverage tests..."
echo ""

# Get list of all coverage tests
TESTS=$(ls test_regress/t/t_covergroup_*.v test_regress/t/t_funccov_*.v 2>/dev/null | sed 's|test_regress/t/||' | sed 's|\.v$||' | sort)

for test in $TESTS; do
    ((TOTAL++))
    
    # Check if it's a _bad test (expected to fail)
    if [[ $test =~ _bad ]]; then
        ((BAD_TESTS++))
        continue
    fi
    
    # Clean up
    rm -rf obj_dir /tmp/v_${test}.log 2>/dev/null
    
    # Verilate
    ./bin/verilator --cc --coverage --exe --main test_regress/t/${test}.v -Wno-UNSIGNED > /tmp/v_${test}.log 2>&1
    if [ $? -ne 0 ]; then
        echo "$test: VERILATOR FAIL"
        ((V_FAIL++))
        continue
    fi
    
    # Find makefile
    MAKEFILE=$(ls obj_dir/V${test}.mk 2>/dev/null | head -1)
    if [ -z "$MAKEFILE" ]; then
        echo "$test: NO MAKEFILE"
        ((V_FAIL++))
        continue
    fi
    
    # Compile
    make -C obj_dir -f $(basename $MAKEFILE) > /tmp/c_${test}.log 2>&1
    if [ $? -ne 0 ]; then
        echo "$test: COMPILE FAIL"
        ((C_FAIL++))
        continue
    fi
    
    # Run
    ./obj_dir/V${test} > /tmp/r_${test}.log 2>&1
    if [ $? -ne 0 ]; then
        echo "$test: RUNTIME FAIL"
        ((R_FAIL++))
        continue
    fi
    
    echo "$test: PASS"
    ((PASSED++))
done

echo ""
echo "========================================="
echo "Total tests: $TOTAL"
echo "Bad tests (skipped): $BAD_TESTS"
echo "Actual tests: $((TOTAL - BAD_TESTS))"
echo "Passed: $PASSED"
echo "Verilator failures: $V_FAIL"
echo "Compile failures: $C_FAIL"
echo "Runtime failures: $R_FAIL"
echo "Success rate: $(echo "scale=1; $PASSED * 100 / ($TOTAL - $BAD_TESTS)" | bc)%"
echo "========================================="
