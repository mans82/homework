module top (
	clk,
	reset,
	WriteData,
	DataAdr,
	MemWrite
);
	input wire clk;
	input wire reset;
	output wire [31:0] WriteData;
	output wire [31:0] DataAdr;
	output wire MemWrite;
	wire [31:0] ReadData;
	
	wire rst_n = ~reset;
	riscvmulti rvmulti(
		.clk(clk),
		.reset(rst_n),
		.MemWrite(MemWrite),
		.Adr(DataAdr),
		.WriteData(WriteData),
		.ReadData(ReadData)
	);
	mem mem(
		.clk(clk),
		.we(MemWrite),
		.a(DataAdr),
		.wd(WriteData),
		.rd(ReadData)
	);
endmodule
