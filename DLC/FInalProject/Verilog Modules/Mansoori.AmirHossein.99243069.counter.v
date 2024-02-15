module counter (out, clk, reset);
	parameter COUNT = 1000;
	
	input clk;
	input reset;
	output reg out;
	
	reg [15:0] ctr = 0;
	
	always @ (posedge clk) begin
		if (reset) begin
			ctr <= 1;
			out <= 0;
		end
		else if (ctr == COUNT - 1) begin
			out <= 1;
			ctr <= 0;
		end
		else begin
			ctr <= ctr + 1;
			out <= 0;
		end
	end
endmodule