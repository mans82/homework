module mux2 #(parameter WIDTH = 8)(
					input logic [WIDTH-1:0] a0,a1,
					input logic S,
					output [WIDTH-1:0] result);
					
	assign result  = S? a1 : a0;
endmodule