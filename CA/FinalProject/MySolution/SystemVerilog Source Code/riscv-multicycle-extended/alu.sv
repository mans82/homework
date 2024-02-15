module alu(input logic [31:0] a, b,
				input logic [3:0] control,
				output logic [31:0] z,
				output logic zero);
				
	logic [63:0] s_mul;
	logic [63:0] u_mul;
	logic [63:0] s_u_mul;
	always_comb begin
		s_mul = a * b;
		u_mul = $unsigned(a) * $unsigned(b);
		s_u_mul = $signed(a) * $unsigned(b);
	end 
	always_comb
		case (control)
			4'b0000: z = a + b;
			4'b0001: z = a - b;
			4'b0010: z = a & b;
			4'b0011: z = a | b;
			4'b0101: z = a < b ? 1 : 0;
			4'b0100: z = a ^ b ; //xor-xori --> added
			4'b0110: z = a << b[4:0]; //sll--slli ---> added
			4'b0111: z = a >> b[4:0]; //srl--srli ---> added
			4'b1000: z = a >>> b[4:0]; //sla---> added
			4'b1001: z = s_mul[31:0]; //mul
			4'b1010: z = s_mul[63:32];//mulhss
			4'b1011: z = s_u_mul[63:32]; //mulhsu
			4'b1100: z = u_mul[63:32]; //mulhuu
			4'b1101:if (b == 0)
                    z = 32'b1;
                else if ((a == 32'h80000000) && (b == 32'b1))
                    z = 32'h80000000;
                else
                    z  = a / b; //division
			4'b1110: if (b == 0)
                    z = a;
                else if ((a == 32'h80000000) && (b == 32'b1))
                    z = 0;
                else
                    z =a % b; //rem
			default: z = 32'bx;
		endcase
	
	assign zero = z == 0;
				
endmodule 
