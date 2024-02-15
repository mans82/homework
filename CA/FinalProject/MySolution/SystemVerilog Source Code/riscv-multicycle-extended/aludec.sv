module aludec(input logic opb5,
	input logic [2:0] funct3,
	input logic funct7b5,
	input logic funct7b0,
	input logic [1:0] ALUOp,
	output logic [3:0] ALUControl);
	
	
	logic RtypeSub;
	assign RtypeSub = funct7b5 & opb5; // TRUE for Rtype subtrac
	
always_comb begin	
		case(ALUOp)
			2'b00: ALUControl = 4'b000; // addition
			2'b01: ALUControl = 4'b001; // subtraction
			default: if (funct7b0) begin
				case(funct3)
					3'b000: ALUControl = 4'b1001; //mul ==>extra
					3'b001: ALUControl = 4'b1010; //mulh ==>extra
					3'b010: ALUControl = 4'b1011; //mulhsu ==>extra
					3'b011: ALUControl = 4'b1100; //muluu ==>extra
					3'b100: ALUControl = 4'b1101; //div ==>extra
					3'b110: ALUControl = 4'b1110; //rem ==>extra
					default: ALUControl = 4'bxxxx;
				endcase 
			end
			else case(funct3) // Rtype or Itype ALU
						3'b000: if (RtypeSub)
							ALUControl = 4'b0001; // sub
							else
							ALUControl = 4'b0000; // add, addi
						3'b010: ALUControl = 4'b0101; // slt, slti
						3'b110: ALUControl = 4'b0011; // or, ori
						3'b111: ALUControl = 4'b0010; // and, andi
						3'b100: ALUControl = 4'b0100; //xor - xori ====> extra
						3'b001: ALUControl = 4'b0110; //shift left left logical / immediate ===> extra
						3'b101: if(funct7b5)
										ALUControl = 4'b1000; //shift right arithmetic==>extra
									else 
										ALUControl = 4'b0111; //shift right logical ==> extra
						 default: ALUControl = 4'bxxxx; // ???
					endcase
		endcase
	end
endmodule 


