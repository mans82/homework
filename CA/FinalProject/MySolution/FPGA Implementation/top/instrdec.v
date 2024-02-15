module instrdec (
	op,
	ImmSrc
);
	input wire [6:0] op;
	output reg [1:0] ImmSrc;
	always @(*)
		case (op)
			'b11: ImmSrc = 2'b00;
			'b100011: ImmSrc = 2'b01;
			'b110011: ImmSrc = 2'bxx;
			'b1100011: ImmSrc = 2'b10;
			'b10011: ImmSrc = 2'b00;
			'b1101111: ImmSrc = 2'b11;
			default: ImmSrc = 2'bxx;
		endcase
endmodule
