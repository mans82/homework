module alu(input logic [31:0] a, b,
				input logic [2:0] control,
				output logic [31:0] z,
				output logic zero);
				
	always_comb
		case (control)
			3'b000: z = a + b;
			3'b001: z = a - b;
			3'b010: z = a & b;
			3'b011: z = a | b;
			3'b101: z = a < b ? 1 : 0;
			default: z = 32'bx;
		endcase
	
	assign zero = z == 0;
				
endmodule 