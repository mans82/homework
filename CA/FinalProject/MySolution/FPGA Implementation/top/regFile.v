module regFile (
	clk,
	RegWrite,
	a1,
	a2,
	a3,
	result,
	Rd1,
	Rd2
);
	input wire clk;
	input wire RegWrite;
	input wire [4:0] a1;
	input wire [4:0] a2;
	input wire [4:0] a3;
	input wire [31:0] result;
	output wire [31:0] Rd1;
	output wire [31:0] Rd2;
	reg [31:0] rf [31:0];
	always @(posedge clk)
		if (RegWrite)
			rf[a3] <= result;
	assign Rd1 = (a1 == 0 ? 0 : rf[a1]);
	assign Rd2 = (a2 == 0 ? 0 : rf[a2]);
endmodule
