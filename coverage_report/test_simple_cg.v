//      // verilator_coverage annotation
        module t;
%000001    logic [1:0] data;
           
%000002    covergroup cg;
%000001       cp: coverpoint data {
%000001          bins low  = {2'b00};
%000001          bins high = {2'b11};
              }
           endgroup
           
%000001    cg cg_inst = new;
           
%000001    initial begin
%000001       data = 2'b00;
%000001       cg_inst.sample();
%000001       data = 2'b11;
%000001       cg_inst.sample();
%000001       $write("*-* All Finished *-*\n");
%000001       $finish;
           end
        endmodule
        
