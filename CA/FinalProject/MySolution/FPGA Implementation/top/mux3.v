module mux3 (
	a0,
	a1,
	a2,
	s,
	result
);
	parameter WIDTH = 8;
	input wire [WIDTH - 1:0] a0;
	input wire [WIDTH - 1:0] a1;
	input wire [WIDTH - 1:0] a2;
	input wire [1:0] s;
	output wire [WIDTH - 1:0] result;
	assign result = (s[1] ? a2 : (s[0] ? a1 : a0));
endmodule
