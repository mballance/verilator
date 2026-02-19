module t (input clk);
   int value = 0;

   covergroup cg;
      cp: coverpoint value {
         bins low = {[0:5]};
      }
   endgroup

   cg my_cg = new;

   always @(posedge clk) begin
      real cov;
      cov = my_cg.get_inst_coverage();
      my_cg.sample();
   end
endmodule
