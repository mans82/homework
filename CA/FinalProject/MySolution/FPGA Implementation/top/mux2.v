module mux2 (
	a0,
	a1,
	S,
	result
);
	parameter WIDTH = 8;
	input wire [WIDTH - 1:0] a0;
	input wire [WIDTH - 1:0] a1;
	input wire S;
	output wire [WIDTH - 1:0] result;
	assign result = (S ? a1 : a0);
endmodule
