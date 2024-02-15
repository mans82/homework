module mainfsm(input logic clk,
	input logic reset,
	input logic [6:0] op,
	output logic Branch,
	output logic PCUpdate,
	output logic RegWrite, MemWrite,
	output logic IRWrite,
	output logic [1:0] ResultSrc,
	output logic [1:0] ALUSrcA, ALUSrcB,
	output logic AdrSrc,
	output logic [1:0] ALUOp);

typedef enum logic[4:0] {Fetch, Decode, MemAdr, MemRead, MemWB, MemW, ExecuteR, ALUWB, ExecuteI, JAL, BEQ, Invalid = 5'bx} stateType;

stateType curState, nextState;

always_ff @(posedge clk or posedge reset) begin
	if (reset) curState <= Fetch;
	else curState <= nextState;
end

always_comb begin
	case (curState)
		Fetch: nextState = Decode;
		Decode: case(op)
			'b0000011: nextState = MemAdr;
			'b0100011: nextState = MemAdr;
			'b0110011: nextState = ExecuteR;
			'b0010011: nextState = ExecuteI;
			'b1101111: nextState = JAL;
			'b1100011: nextState = BEQ;
			default: nextState = Invalid;
		endcase
		MemAdr: case(op)
			'b0000011: nextState = MemRead;
			'b0100011: nextState = MemW;
			default: nextState = Invalid;
		endcase
		MemRead: nextState = MemWB;
		MemWB: nextState = Fetch;
		MemW: nextState = Fetch;
		ExecuteR: nextState = ALUWB;
		ALUWB: nextState = Fetch;
		ExecuteI: nextState = ALUWB;
		JAL: nextState = ALUWB;
		BEQ: nextState = Fetch;
		default: nextState = Invalid;
	endcase
end

always_comb begin
	Branch = 0;
	PCUpdate = 0;
	ALUSrcA = 0;
	ALUSrcB = 0;
	ResultSrc = 0;
	AdrSrc = 0;
	IRWrite = 0;
	RegWrite = 0;
	MemWrite = 0;
	ALUOp = 0;

	case (curState)
		Fetch: begin
			AdrSrc = 0;
			IRWrite = 1;
			ALUSrcA = 'b00;
			ALUSrcB = 'b10;
			ALUOp = 'b00;
			ResultSrc = 'b10;
			PCUpdate = 1;
		end
		Decode: begin
			ALUSrcA = 'b01;
			ALUSrcB = 'b01;
			ALUOp = 'b00;
		end
		MemAdr: begin
			ALUSrcA = 'b10;
			ALUSrcB = 'b01;
			ALUOp = 'b00;
		end
		MemRead: begin
			ResultSrc = 'b00;
			AdrSrc = 1;
		end
		MemWB: begin
			ResultSrc = 'b01;
			RegWrite = 1;
		end
		MemW: begin
			ResultSrc = 'b00;
			AdrSrc = 1;
			MemWrite = 1;
		end
		ExecuteR: begin
			ALUSrcA = 'b10;
			ALUSrcB = 'b00;
			ALUOp = 'b10;
		end
		ALUWB: begin
			ResultSrc = 'b00;
			RegWrite = 1;
		end
		ExecuteI: begin
			ALUSrcA = 'b10;
			ALUSrcB = 'b01;
			ALUOp = 'b10;
		end
		JAL: begin
			ALUSrcA = 'b01;
			ALUSrcB = 'b10;
			ALUOp = 'b00;
			ResultSrc = 'b00;
			PCUpdate = 1;
		end
		BEQ: begin
			ALUSrcA = 'b10;
			ALUSrcB = 'b00;
			ALUOp = 'b01;
			ResultSrc = 'b00;
			Branch = 1;
		end
		default: begin
			Branch = 1'bx;
			PCUpdate = 1'bx;
			ALUSrcA = 2'bx;
			ALUSrcB = 2'bx;
			ResultSrc = 2'bx;
			AdrSrc = 1'bx;
			IRWrite = 1'bx;
			RegWrite = 1'bx;
			MemWrite = 1'bx;
			ALUOp = 2'bx;
		end
	endcase
end

endmodule
