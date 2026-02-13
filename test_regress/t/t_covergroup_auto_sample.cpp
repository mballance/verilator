// -*- mode: C++; c-file-style: "cc-mode" -*-
// Simple test harness for t_covergroup_auto_sample - provides clock

#include "verilated.h"

#include "Vt_covergroup_auto_sample.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vt_covergroup_auto_sample* top = new Vt_covergroup_auto_sample;

    // Run for 20 cycles
    for (int i = 0; i < 20; i++) {
        top->clk = 0;
        top->eval();
        top->clk = 1;
        top->eval();

        if (Verilated::gotFinish()) break;
    }

    delete top;
    return 0;
}
