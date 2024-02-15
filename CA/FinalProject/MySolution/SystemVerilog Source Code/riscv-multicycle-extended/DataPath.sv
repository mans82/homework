module DataPath(input  logic clk, rst,
					 input  logic [1:0] ResultSrc,
					 input  logic [3:0] ALUControl,
					 input  logic [1:0] ALUSrcA,
					 input  logic [1:0] ALUSrcB,
					 input  logic [1:0] ImmSrc, 
					 input  logic RegWrite,
					 input  logic AdrSrc,
                input  logic IRWrite, PCWrite, 
					 input  logic [31:0] Instr,
					 input  logic [31:0] Data, 
                output logic zero,
					 output logic [31:0] Adr, WriteData
					 );
					 
	logic [31:0] Result;
	logic [31:0] rd1,rd2;
	logic [31:0] A_a; //rd1
	logic [31:0] immExt;
	// logic [31:0] four = 4;
	logic [31:0] SrcB;
	logic [31:0] SrcA;
	logic [31:0] ALUOut;
	logic [31:0] PC,oldPc;
	logic [31:0] ALUResult;
	
	flopenr#(32) pcSaver(clk,rst,IRWrite, PC,oldPc);
	flopenr#(32) nextPcReg(clk,rst,PCWrite,Result, PC);
	
	// flopr #(32) dataSaver(clk, rst, Data, DataReg);
	
	mux3#(32) resultChoser(ALUOut, Data ,ALUResult, ResultSrc ,Result); //kinda wierd
	
	regFile rf(clk, RegWrite, Instr[19:15], Instr[24:20], Instr[11:7], Result, rd1,rd2);
	flopr#(32) 	rd1Saver(clk,rst, rd1, A_a);
	flopr#(32) 	rd2Saver(clk,rst, rd2, WriteData);
	
	extend extendUnit(Instr[31:7], ImmSrc, immExt);
	
	mux3#(32) muxSrcB(WriteData, immExt, 'd4, ALUSrcB,SrcB ); //srcb chooser
	mux3#(32) muxsrcA(PC,oldPc,A_a ,ALUSrcA,SrcA);
	alu mainAlu(SrcA,SrcB, ALUControl, ALUResult, zero);
	flopr#(32)  aluSaver(clk,rst, ALUResult, ALUOut);
	
	mux2#(32) address(PC,Result, AdrSrc, Adr);
endmodule