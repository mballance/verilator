// DESCRIPTION: Simple test harness for transition bins
// Manual clock driver

#include "Vt_covergroup_trans_simple.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vt_covergroup_trans_simple* top = new Vt_covergroup_trans_simple;

    // Run for several clock cycles
    top->clk = 0;
    for (int i = 0; i < 20 && !Verilated::gotFinish(); i++) {
        top->clk = !top->clk;
        top->eval();

        if (i % 2 == 1) {  // After posedge
            std::cout << "Cycle " << (i/2) << std::endl;
        }
    }

    delete top;
    return 0;
}
