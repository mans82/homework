module controller (
	clk,
	reset,
	op,
	funct3,
	funct7b5,
	funct7b0,
	Zero,
	ImmSrc,
	ALUSrcA,
	ALUSrcB,
	ResultSrc,
	AdrSrc,
	ALUControl,
	IRWrite,
	PCWrite,
	RegWrite,
	MemWrite
);
	input wire clk;
	input wire reset;
	input wire [6:0] op;
	input wire [2:0] funct3;
	input wire funct7b5;
	input wire funct7b0;
	input wire Zero;
	output wire [1:0] ImmSrc;
	output wire [1:0] ALUSrcA;
	output wire [1:0] ALUSrcB;
	output wire [1:0] ResultSrc;
	output wire AdrSrc;
	output wire [2:0] ALUControl;
	output wire IRWrite;
	output wire PCWrite;
	output wire RegWrite;
	output wire MemWrite;
	wire Branch;
	wire PCUpdate;
	wire [1:0] ALUOp;
	assign PCWrite = (Zero & Branch) | PCUpdate;
	mainfsm fsm(
		.clk(clk),
		.reset(reset),
		.op(op),
		.Branch(Branch),
		.PCUpdate(PCUpdate),
		.RegWrite(RegWrite),
		.MemWrite(MemWrite),
		.IRWrite(IRWrite),
		.ResultSrc(ResultSrc),
		.ALUSrcA(ALUSrcA),
		.ALUSrcB(ALUSrcB),
		.AdrSrc(AdrSrc),
		.ALUOp(ALUOp)
	);
	aludec dec(
		.opb5(op[5]),
		.funct3(funct3),
		.funct7b5(funct7b5),
		.funct7b0(funct7b0),
		.ALUOp(ALUOp),
		.ALUControl(ALUControl)
	);
	instrdec idec(
		.op(op),
		.ImmSrc(ImmSrc)
	);
endmodule
