module mainfsm (
	clk,
	reset,
	op,
	Branch,
	PCUpdate,
	RegWrite,
	MemWrite,
	IRWrite,
	ResultSrc,
	ALUSrcA,
	ALUSrcB,
	AdrSrc,
	ALUOp
);
	input wire clk;
	input wire reset;
	input wire [6:0] op;
	output reg Branch;
	output reg PCUpdate;
	output reg RegWrite;
	output reg MemWrite;
	output reg IRWrite;
	output reg [1:0] ResultSrc;
	output reg [1:0] ALUSrcA;
	output reg [1:0] ALUSrcB;
	output reg AdrSrc;
	output reg [1:0] ALUOp;
	reg [4:0] curState;
	reg [4:0] nextState;
	always @(posedge clk or posedge reset)
		if (reset)
			curState <= 5'd0;
		else
			curState <= nextState;
	always @(*)
		case (curState)
			5'd0: nextState = 5'd1;
			5'd1:
				case (op)
					'b11: nextState = 5'd2;
					'b100011: nextState = 5'd2;
					'b110011: nextState = 5'd6;
					'b10011: nextState = 5'd8;
					'b1101111: nextState = 5'd9;
					'b1100011: nextState = 5'd10;
					default: nextState = 5'bxxxxx;
				endcase
			5'd2:
				case (op)
					'b11: nextState = 5'd3;
					'b100011: nextState = 5'd5;
					default: nextState = 5'bxxxxx;
				endcase
			5'd3: nextState = 5'd4;
			5'd4: nextState = 5'd0;
			5'd5: nextState = 5'd0;
			5'd6: nextState = 5'd7;
			5'd7: nextState = 5'd0;
			5'd8: nextState = 5'd7;
			5'd9: nextState = 5'd7;
			5'd10: nextState = 5'd0;
			default: nextState = 5'bxxxxx;
		endcase
	always @(*) begin
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
			5'd0: begin
				AdrSrc = 0;
				IRWrite = 1;
				ALUSrcA = 'b0;
				ALUSrcB = 'b10;
				ALUOp = 'b0;
				ResultSrc = 'b10;
				PCUpdate = 1;
			end
			5'd1: begin
				ALUSrcA = 'b1;
				ALUSrcB = 'b1;
				ALUOp = 'b0;
			end
			5'd2: begin
				ALUSrcA = 'b10;
				ALUSrcB = 'b1;
				ALUOp = 'b0;
			end
			5'd3: begin
				ResultSrc = 'b0;
				AdrSrc = 1;
			end
			5'd4: begin
				ResultSrc = 'b1;
				RegWrite = 1;
			end
			5'd5: begin
				ResultSrc = 'b0;
				AdrSrc = 1;
				MemWrite = 1;
			end
			5'd6: begin
				ALUSrcA = 'b10;
				ALUSrcB = 'b0;
				ALUOp = 'b10;
			end
			5'd7: begin
				ResultSrc = 'b0;
				RegWrite = 1;
			end
			5'd8: begin
				ALUSrcA = 'b10;
				ALUSrcB = 'b1;
				ALUOp = 'b10;
			end
			5'd9: begin
				ALUSrcA = 'b1;
				ALUSrcB = 'b10;
				ALUOp = 'b0;
				ResultSrc = 'b0;
				PCUpdate = 1;
			end
			5'd10: begin
				ALUSrcA = 'b10;
				ALUSrcB = 'b0;
				ALUOp = 'b1;
				ResultSrc = 'b0;
				Branch = 1;
			end
			default: begin
				Branch = 1'bx;
				PCUpdate = 1'bx;
				ALUSrcA = 2'bxx;
				ALUSrcB = 2'bxx;
				ResultSrc = 2'bxx;
				AdrSrc = 1'bx;
				IRWrite = 1'bx;
				RegWrite = 1'bx;
				MemWrite = 1'bx;
				ALUOp = 2'bxx;
			end
		endcase
	end
endmodule
