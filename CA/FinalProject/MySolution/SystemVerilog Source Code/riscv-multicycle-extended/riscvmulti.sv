module riscvmulti(input  logic        clk, reset,
                  output logic        MemWrite,
                  output logic [31:0] Adr, WriteData,
                  input  logic [31:0] ReadData);
						
	logic [1:0] ResultSrc;
	logic [3:0] ALUControl;
	logic [1:0] ALUSrcA;
	logic [1:0] ALUSrcB;
	logic [1:0] ImmSrc;
	logic RegWrite, AdrSrc;
	logic IRWrite, PCWrite;
	logic Zero;
	logic [31:0] instruction; 
	logic [31:0] Data;
	
	
	flopenr#(32) nextPcReg(clk,reset,IRWrite,ReadData,instruction);
	flopr#(32) dataSaver(clk, reset, ReadData, Data);
	
	DataPath dp(clk, reset, ResultSrc, ALUControl,ALUSrcA,ALUSrcB,ImmSrc, RegWrite, 
					AdrSrc, IRWrite, PCWrite, instruction, Data, Zero, Adr, WriteData);
					
	controller c(clk,reset, instruction[6:0],instruction[14:12],instruction[30], instruction[25],Zero,ImmSrc,ALUSrcA,
					ALUSrcB,ResultSrc, AdrSrc,ALUControl,IRWrite, PCWrite, RegWrite, MemWrite);
endmodule