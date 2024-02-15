// A 2 to 1 decoder.
module Decoder_1_2(
	input logic in,
	input logic en,
	output logic [1:0] out
);
	
	// out[0] is HIGH, only if in is 0.
	// out[1] is HIGH, only if in is 1.
	// if en is LOW, out is LOW.
	assign out[0] = en & ~in;
	assign out[1] = en & in;

endmodule
