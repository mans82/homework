module regfile(input logic clk,
	input logic WE3,
	input logic [4:0] A1, A2, A3,
	input logic [31:0] WD3,
	output logic [31:0] RD1,
	output logic [31:0] RD2);
	
	logic [31:0] regMem [31:0];
	
	assign RD1 = A1 == 0 ? 0 : regMem[A1[4:0]];
	assign RD2 = A2 == 0 ? 0 : regMem[A2[4:0]];
	
	always_ff @ (posedge clk) begin
		if (WE3) regMem[A3[4:0]] <= WD3;
	end
	
endmodule
	