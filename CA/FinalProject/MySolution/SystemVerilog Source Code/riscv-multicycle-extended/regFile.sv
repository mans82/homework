module regFile( input logic clk,
					input logic RegWrite,
					input logic [4:0] a1,
					input logic [4:0] a2,
					input logic [4:0] a3,
					input logic [31:0] result,
					output logic [31:0] Rd1,
					output logic [31:0] Rd2);
 //creating array of registers
	logic [31:0] rf[31:0];
	always @(posedge clk)
		if(RegWrite) rf[a3] <= result;
		
	assign Rd1 =  a1 == 0 ? 0 : rf[a1];
	assign Rd2 =  a2 == 0 ? 0 : rf[a2]; 
	
endmodule 