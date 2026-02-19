//      // verilator_coverage annotation
        module t;
           logic [1:0] data;

           covergroup cg;
              cp: coverpoint data {
 000005          bins low  = {2'b00};
+000005  point: comment= hier=cg.cp.low
 000003          bins mid  = {2'b01};
+000003  point: comment= hier=cg.cp.mid
 000010          bins high = {2'b11};
+000010  point: comment= hier=cg.cp.high
              }
           endgroup

           cg cg_inst = new;

           initial begin
              // Hit low bin 5 times
              repeat (5) begin
                 data = 2'b00;
                 cg_inst.sample();
              end

              // Hit mid bin 3 times
              repeat (3) begin
                 data = 2'b01;
                 cg_inst.sample();
              end

              // Hit high bin 10 times
              repeat (10) begin
                 data = 2'b11;
                 cg_inst.sample();
              end

              $write("*-* All Finished *-*\n");
              $finish;
           end
        endmodule
