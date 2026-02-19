//      // verilator_coverage annotation
        module t;
           logic [1:0] data;

           covergroup cg;
              cp: coverpoint data {
%000001          bins low  = {2'b00};
%000001          bins high = {2'b11};
              }
           endgroup

           cg cg_inst = new;

           initial begin
              data = 2'b00;
              cg_inst.sample();
              data = 2'b11;
              cg_inst.sample();
              $write("*-* All Finished *-*\n");
              $finish;
           end
        endmodule
