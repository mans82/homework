module riscvmulti (
	clk,
	reset,
	MemWrite,
	Adr,
	WriteData,
	ReadData
);
	input wire clk;
	input wire reset;
	output wire MemWrite;
	output wire [31:0] Adr;
	output wire [31:0] WriteData;
	input wire [31:0] ReadData;
	wire [1:0] ResultSrc;
	wire [2:0] ALUControl;
	wire [1:0] ALUSrcA;
	wire [1:0] ALUSrcB;
	wire [1:0] ImmSrc;
	wire RegWrite;
	wire AdrSrc;
	wire IRWrite;
	wire PCWrite;
	wire Zero;
	wire [31:0] instruction;
	wire [31:0] Data;
	flopenr #(.WIDTH(32)) nextPcReg(
		.clk(clk),
		.rst(reset),
		.enb(IRWrite),
		.d(ReadData),
		.q(instruction)
	);
	flopr #(.WIDTH(32)) dataSaver(
		.clk(clk),
		.rst(reset),
		.d(ReadData),
		.q(Data)
	);
	DataPath dp(
		.clk(clk),
		.rst(reset),
		.ResultSrc(ResultSrc),
		.ALUControl(ALUControl),
		.ALUSrcA(ALUSrcA),
		.ALUSrcB(ALUSrcB),
		.ImmSrc(ImmSrc),
		.RegWrite(RegWrite),
		.AdrSrc(AdrSrc),
		.IRWrite(IRWrite),
		.PCWrite(PCWrite),
		.Instr(instruction),
		.Data(Data),
		.zero(Zero),
		.Adr(Adr),
		.WriteData(WriteData)
	);
	controller c(
		.clk(clk),
		.reset(reset),
		.op(instruction[6:0]),
		.funct3(instruction[14:12]),
		.funct7b5(instruction[30]),
		.funct7b0(instruction[25]),
		.Zero(Zero),
		.ImmSrc(ImmSrc),
		.ALUSrcA(ALUSrcA),
		.ALUSrcB(ALUSrcB),
		.ResultSrc(ResultSrc),
		.AdrSrc(AdrSrc),
		.ALUControl(ALUControl),
		.IRWrite(IRWrite),
		.PCWrite(PCWrite),
		.RegWrite(RegWrite),
		.MemWrite(MemWrite)
	);
endmodule
