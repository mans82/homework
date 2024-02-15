module testbench;
	reg clk;
	reg reset;
	wire [31:0] WriteData;
	wire [31:0] DataAdr;
	wire MemWrite;
	reg [31:0] hash;
	top dut(
		.clk(clk),
		.reset(reset),
		.WriteData(WriteData),
		.DataAdr(DataAdr),
		.MemWrite(MemWrite)
	);
	initial begin
		hash <= 0;
		reset <= 1;
		#(22)
			;
		reset <= 0;
	end
	always begin
		clk <= 1;
		#(5)
			;
		clk <= 0;
		#(5)
			;
	end
	always @(negedge clk)
		if (MemWrite)
			if ((DataAdr === 100) & (WriteData === 25)) begin
				$display("Simulation succeeded");
				$display("hash = %h", hash);
				$stop;
			end
			else if (DataAdr !== 96) begin
				$display("Simulation failed");
				$stop;
			end
	always @(negedge clk)
		if (~reset) begin
			hash = (hash ^ dut.rvmulti.dp.Instr) ^ dut.rvmulti.dp.PC;
			if (MemWrite)
				hash = hash ^ WriteData;
			hash = {hash[30:0], ((hash[9] ^ hash[29]) ^ hash[30]) ^ hash[31]};
		end
endmodule
