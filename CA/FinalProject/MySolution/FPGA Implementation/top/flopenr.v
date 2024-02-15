module flopenr (
	clk,
	rst,
	enb,
	d,
	q
);
	parameter WIDTH = 8;
	input wire clk;
	input wire rst;
	input wire enb;
	input wire [WIDTH - 1:0] d;
	output reg [WIDTH - 1:0] q;
	always @(posedge clk or posedge rst)
		if (rst)
			q <= 0;
		else if (enb)
			q <= d;
endmodule
