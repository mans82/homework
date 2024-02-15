module aludec (
	opb5,
	funct3,
	funct7b5,
	funct7b0,
	ALUOp,
	ALUControl
);
	input wire opb5;
	input wire [2:0] funct3;
	input wire funct7b5;
	input wire funct7b0;
	input wire [1:0] ALUOp;
	output reg [3:0] ALUControl;
	wire RtypeSub;
	assign RtypeSub = funct7b5 & opb5;
	always @(*)
		if (funct7b0)
			case (funct3)
				3'b000: ALUControl = 4'b1001;
				3'b001: ALUControl = 4'b1010;
				3'b010: ALUControl = 4'b1011;
				3'b011: ALUControl = 4'b1100;
				3'b100: ALUControl = 4'b1101;
				3'b110: ALUControl = 4'b1110;
				default: ALUControl = 4'bxxxx;
			endcase
		else
			case (ALUOp)
				2'b00: ALUControl = 4'b0000;
				2'b01: ALUControl = 4'b0001;
				default:
					case (funct3)
						3'b000:
							if (RtypeSub)
								ALUControl = 4'b0001;
							else
								ALUControl = 4'b0000;
						3'b010: ALUControl = 4'b0101;
						3'b110: ALUControl = 4'b0011;
						3'b111: ALUControl = 4'b0010;
						3'b100: ALUControl = 4'b0100;
						3'b001: ALUControl = 4'b0110;
						3'b101:
							if (funct7b5)
								ALUControl = 4'b1000;
							else
								ALUControl = 4'b0111;
						default: ALUControl = 4'bxxxx;
					endcase
			endcase
endmodule
