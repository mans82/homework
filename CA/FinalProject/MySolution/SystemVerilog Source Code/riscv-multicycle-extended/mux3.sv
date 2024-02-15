module mux3 #(parameter WIDTH = 8)(
				input logic [WIDTH-1:0] a0,a1,a2,
				input logic [1:0] s,
				output logic [WIDTH-1:0] result);
				
	assign result = s[1] ? a2 : (s[0] ? a1 : a0);
endmodule