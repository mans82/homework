module maindec(input logic [6:0] op,
	output logic [1:0] ResultSrc,
	output logic MemWrite,
	output logic Branch, ALUSrc,
	output logic RegWrite, Jump,
	output logic [2:0] ImmSrc,
	output logic [1:0] ALUOp);
	
	logic [11:0] controls;
	
	assign {RegWrite, ImmSrc, ALUSrc, MemWrite,
		ResultSrc, Branch, ALUOp, Jump} = controls;
	always_comb
		case(op)
			// RegWrite_ImmSrc_ALUSrc_MemWrite_ResultSrc_Branch_ALUOp_Jump
			7'b0000011: controls = 12'b1_000_1_0_01_0_00_0; // lw
			7'b0100011: controls = 12'b0_001_1_1_00_0_00_0; // sw
			7'b0110011: controls = 12'b1_xxx_0_0_00_0_10_0; // Rtype
			7'b1100011: controls = 12'b0_010_0_0_00_1_01_0; // beq
			7'b0010011: controls = 12'b1_000_1_0_00_0_10_0; // Itype ALU
			7'b1101111: controls = 12'b1_011_0_0_10_0_00_1; // jal
			7'b0010111: controls = 12'b1_100_x_0_11_0_xx_0; // auipc
			default: controls = 12'bx_xxx_x_x_xx_x_xx_x; // ???
		endcase
endmodule
