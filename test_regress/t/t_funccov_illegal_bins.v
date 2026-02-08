// DESCRIPTION: Verilator: Functional coverage - illegal_bins test
//
// Test that illegal_bins are excluded from coverage calculations

module t;
    logic [1:0] data;

    covergroup cg;
        coverpoint data {
            bins low = {0};
            bins mid = {1};
            bins high = {2};
            illegal_bins forbidden = {3};
        }
    endgroup

    initial begin
        cg cg_inst = new;
        
        // Sample legal values only
        data = 0;
        cg_inst.sample();
        $display("Coverage after low: %f%% (expected ~33.33%%)", cg_inst.get_inst_coverage());
        
        data = 1;
        cg_inst.sample();
        $display("Coverage after mid: %f%% (expected ~66.67%%)", cg_inst.get_inst_coverage());
        
        data = 2;
        cg_inst.sample();
        $display("Coverage complete: %f%% (expected ~100.00%%)", cg_inst.get_inst_coverage());
        
        $write("*-* All Finished *-*\n");
        $finish;
    end
endmodule
