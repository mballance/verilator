
module top;
  covergroup cg with function sample(int a, int b);
    cp_a : coverpoint a;
    cp_b : coverpoint b;

  endgroup

  cg cg_i;

  initial begin
	  cg_i = new();
	  cg_i.sample(1, 2);
	  cg_i.sample(100, 20);
  end

endmodule

