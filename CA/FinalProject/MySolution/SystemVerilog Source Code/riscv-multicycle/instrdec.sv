module instrdec(
	input logic [6:0] op,
	output logic [1:0] ImmSrc);

always_comb begin
	case (op)
		'b0000011: ImmSrc = 2'b00;
		'b0100011: ImmSrc = 2'b01;
		'b0110011: ImmSrc = 2'bxx;
		'b1100011: ImmSrc = 2'b10;
		'b0010011: ImmSrc = 2'b00;
		'b1101111: ImmSrc = 2'b11;
		default: ImmSrc = 2'bxx;
	endcase
end

endmodule
