module alu (
	a,
	b,
	control,
	z,
	zero
);
	input wire [31:0] a;
	input wire [31:0] b;
	input wire [3:0] control;
	output reg [31:0] z;
	output wire zero;
	reg [63:0] s_mul;
	reg [63:0] u_mul;
	reg [63:0] s_u_mul;
	always @(*) begin
		s_mul = a * b;
		u_mul = $unsigned(a) * $unsigned(b);
		s_u_mul = $signed(a) * $unsigned(b)  ;
	end
	always @(*)
		case (control)
			4'b0000: z = a + b;
			4'b0001: z = a - b;
			4'b0010: z = a & b;
			4'b0011: z = a | b;
			4'b0101: z = (a < b ? 1 : 0);
			4'b0100: z = a ^ b;
			4'b0110: z = a << b[4:0];
			4'b0111: z = a >> b[4:0];
			4'b1000: z = a >>> b[4:0];
			4'b1001: z = s_mul[31:0];
			4'b1010: z = s_mul[63:32];
			4'b1011: z = s_u_mul[63:32];
			4'b1100: z = u_mul[63:32];
			4'b1101:
				if (b == 0)
					z = 32'b00000000000000000000000000000001;
				else if ((a == 32'h80000000) && (b == 32'b00000000000000000000000000000001))
					z = 32'h80000000;
				else
					z = a / b;
			4'b1110:
				if (b == 0)
					z = a;
				else if ((a == 32'h80000000) && (b == 32'b00000000000000000000000000000001))
					z = 0;
				else
					z = a % b;
			default: z = 32'bxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
		endcase
	assign zero = z == 0;
endmodule
