// Simple test to verify functional coverage database output
#include "Vt_funccov_bin_counts.h"
#include "verilated.h"
#include "verilated_cov.h"
#include <iostream>

int main(int argc, char** argv) {
    // Create context
    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};
    contextp->commandArgs(argc, argv);
    
    // Enable coverage
    Verilated::mkdir("coverage_test");
    contextp->coveragep()->write("coverage_test/coverage.dat");
    
    // Create model
    const std::unique_ptr<Vt_funccov_bin_counts> topp{new Vt_funccov_bin_counts{contextp.get()}};
    
    // Evaluate once to initialize
    topp->eval();
    
    // Write coverage
    contextp->coveragep()->write("coverage_test/coverage.dat");
    std::cout << "Wrote coverage" << std::endl;
    
    topp->final();
    
    std::cout << "Coverage test complete!" << std::endl;
    return 0;
}
