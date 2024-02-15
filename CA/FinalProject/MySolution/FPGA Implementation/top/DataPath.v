module DataPath (
	clk,
	rst,
	ResultSrc,
	ALUControl,
	ALUSrcA,
	ALUSrcB,
	ImmSrc,
	RegWrite,
	AdrSrc,
	IRWrite,
	PCWrite,
	Instr,
	Data,
	zero,
	Adr,
	WriteData
);
	input wire clk;
	input wire rst;
	input wire [1:0] ResultSrc;
	input wire [3:0] ALUControl;
	input wire [1:0] ALUSrcA;
	input wire [1:0] ALUSrcB;
	input wire [1:0] ImmSrc;
	input wire RegWrite;
	input wire AdrSrc;
	input wire IRWrite;
	input wire PCWrite;
	input wire [31:0] Instr;
	input wire [31:0] Data;
	output wire zero;
	output wire [31:0] Adr;
	output wire [31:0] WriteData;
	wire [31:0] Result;
	wire [31:0] rd1;
	wire [31:0] rd2;
	wire [31:0] A_a;
	wire [31:0] immExt;
	wire [31:0] SrcB;
	wire [31:0] SrcA;
	wire [31:0] ALUOut;
	wire [31:0] PC;
	wire [31:0] oldPc;
	wire [31:0] ALUResult;
	flopenr #(.WIDTH(32)) pcSaver(
		.clk(clk),
		.rst(rst),
		.enb(IRWrite),
		.d(PC),
		.q(oldPc)
	);
	flopenr #(.WIDTH(32)) nextPcReg(
		.clk(clk),
		.rst(rst),
		.enb(PCWrite),
		.d(Result),
		.q(PC)
	);
	mux3 #(.WIDTH(32)) resultChoser(
		.a0(ALUOut),
		.a1(Data),
		.a2(ALUResult),
		.s(ResultSrc),
		.result(Result)
	);
	regFile rf(
		.clk(clk),
		.RegWrite(RegWrite),
		.a1(Instr[19:15]),
		.a2(Instr[24:20]),
		.a3(Instr[11:7]),
		.result(Result),
		.Rd1(rd1),
		.Rd2(rd2)
	);
	flopr #(.WIDTH(32)) rd1Saver(
		.clk(clk),
		.rst(rst),
		.d(rd1),
		.q(A_a)
	);
	flopr #(.WIDTH(32)) rd2Saver(
		.clk(clk),
		.rst(rst),
		.d(rd2),
		.q(WriteData)
	);
	extend extendUnit(
		.instr(Instr[31:7]),
		.immsrc(ImmSrc),
		.immext(immExt)
	);
	mux3 #(.WIDTH(32)) muxSrcB(
		.a0(WriteData),
		.a1(immExt),
		.a2('d4),
		.s(ALUSrcB),
		.result(SrcB)
	);
	mux3 #(.WIDTH(32)) muxsrcA(
		.a0(PC),
		.a1(oldPc),
		.a2(A_a),
		.s(ALUSrcA),
		.result(SrcA)
	);
	alu mainAlu(
		.a(SrcA),
		.b(SrcB),
		.control(ALUControl),
		.z(ALUResult),
		.zero(zero)
	);
	flopr #(.WIDTH(32)) aluSaver(
		.clk(clk),
		.rst(rst),
		.d(ALUResult),
		.q(ALUOut)
	);
	mux2 #(.WIDTH(32)) address(
		.a0(PC),
		.a1(Result),
		.S(AdrSrc),
		.result(Adr)
	);
endmodule
