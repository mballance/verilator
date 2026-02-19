#!/bin/bash
# Comprehensive coverage test runner
export VERILATOR_ROOT=$(pwd)

TOTAL=0
PASS=0
V_FAIL=0
C_FAIL=0
R_FAIL=0
BAD=0

# Get all coverage tests
TESTS=$(ls test_regress/t/t_covergroup_*.v test_regress/t/t_funccov_*.v 2>/dev/null | sed 's|test_regress/t/||' | sed 's|\.v$||' | sort)

for test in $TESTS; do
    ((TOTAL++))

    # Skip _bad tests
    if [[ $test =~ _bad ]]; then
        ((BAD++))
        continue
    fi

    rm -rf obj_dir 2>/dev/null

    # Check if test has .cpp harness
    HARNESS=""
    if [ -f "test_regress/t/${test}.cpp" ]; then
        HARNESS="--exe test_regress/t/${test}.cpp"
    else
        HARNESS="--exe --main"
    fi

    # Verilate
    ./bin/verilator --cc --coverage $HARNESS test_regress/t/${test}.v -Wno-UNSIGNED -Wno-CMPCONST --no-timing >/tmp/v_${test}.log 2>&1
    if [ $? -ne 0 ]; then
        echo "$test: V_FAIL"
        ((V_FAIL++))
        continue
    fi

    # Compile
    make -C obj_dir -f V${test}.mk -j4 >/tmp/c_${test}.log 2>&1
    if [ $? -ne 0 ]; then
        echo "$test: C_FAIL"
        ((C_FAIL++))
        continue
    fi

    # Check if it's compile-only (no execution in .py)
    if [ -f "test_regress/t/${test}.py" ]; then
        if ! grep -q "execute()" "test_regress/t/${test}.py"; then
            # Compile-only test
            echo "$test: PASS (compile-only)"
            ((PASS++))
            continue
        fi
    fi

    # Run (with timeout)
    timeout 5 ./obj_dir/V${test} >/tmp/r_${test}.log 2>&1
    RET=$?
    if [ $RET -eq 0 ]; then
        echo "$test: PASS"
        ((PASS++))
    elif [ $RET -eq 124 ]; then
        echo "$test: R_FAIL (timeout)"
        ((R_FAIL++))
    else
        echo "$test: R_FAIL"
        ((R_FAIL++))
    fi
done

echo ""
echo "========================================"
echo "Total tests: $TOTAL"
echo "Bad tests (skipped): $BAD"
echo "Tests run: $((TOTAL - BAD))"
echo "Passed: $PASS"
echo "Verilator failures: $V_FAIL"
echo "Compile failures: $C_FAIL"
echo "Runtime failures: $R_FAIL"
echo "Success rate: $(echo "scale=1; $PASS * 100 / ($TOTAL - $BAD)" | bc)%"
echo "========================================"
