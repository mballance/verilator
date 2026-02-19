module t (input clk);
   logic enable = 0;
   int value = 0;

   covergroup cg_iff;
      cp_value: coverpoint value iff (enable) {
         bins low = {[0:5]};
         bins mid = {[6:10]};
      }
   endgroup

   cg_iff cg = new;

   always @(posedge clk) begin
      cg.sample();
   end
endmodule
