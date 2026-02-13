#!/bin/bash
export VERILATOR_ROOT=$(pwd)

PASS=0
FAIL_V=0
FAIL_C=0
FAIL_R=0

for test in t_covergroup_minimal t_covergroup_simple t_covergroup_bins_advanced \
    t_covergroup_bins_default_illegal t_covergroup_cross_simple t_covergroup_cross_3way \
    t_covergroup_cross_4way t_covergroup_dynamic t_covergroup_iff t_covergroup_empty \
    t_covergroup_auto_sample t_covergroup_get_coverage t_funccov_basic t_funccov_bin_counts \
    t_funccov_auto_bins t_funccov_cross_basic t_funccov_iff t_funccov_illegal_bins \
    t_funccov_ignore_bins t_funccov_default_bins; do
  
  rm -rf obj_dir 2>/dev/null
  
  # Try without timing, then with --no-timing if fails
  ./bin/verilator --cc --coverage --exe --main test_regress/t/${test}.v -Wno-UNSIGNED >/tmp/v.log 2>&1
  if [ $? -ne 0 ]; then
    # Try with --no-timing
    ./bin/verilator --cc --coverage --exe --main --no-timing test_regress/t/${test}.v -Wno-UNSIGNED >/tmp/v.log 2>&1
    if [ $? -ne 0 ]; then
      echo "$test: V_FAIL"
      ((FAIL_V++))
      continue
    fi
  fi
  
  # Compile
  make -C obj_dir -f V${test}.mk -j4 >/tmp/c.log 2>&1
  if [ $? -ne 0 ]; then
    echo "$test: C_FAIL"
    ((FAIL_C++))
    continue
  fi
  
  # Run
  timeout 5 ./obj_dir/V${test} >/tmp/r.log 2>&1
  if [ $? -ne 0 ]; then
    echo "$test: R_FAIL"
    ((FAIL_R++))
    continue
  fi
  
  echo "$test: PASS"
  ((PASS++))
done

echo ""
echo "PASS: $PASS, V_FAIL: $FAIL_V, C_FAIL: $FAIL_C, R_FAIL: $FAIL_R"
