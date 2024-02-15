`include "counter.v"

module counter_tb;
	
	reg clk;
	reg reset;
	wire out10, out20;
	
	always #5 clk = ~clk;
	
	counter #(.COUNT(10)) ctr10(out10, clk, reset);
	counter #(.COUNT(20)) ctr20(out20, clk, reset);
	
	initial begin
		clk = 1;
		reset = 0;
		
		#560 reset = 1;
		#140 reset = 0;
	end
	
endmodule