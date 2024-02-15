// A 3 to 8 decoder.
module Decoder_3_8(
	input logic [2:0] in,
	input logic en,
	output logic [7:0] out
);
	// The design is similar to a 2-to-4 decoder.
	// The MSB of in (in[2]) determines what decoder to use.
	// If in[2] is LOW, the 2-to-4 decoder connected to lower part of output (out[3:0]) is enabled.
	// Otherwise, the 2-to-4 decoder connected to upper part of output (out[7:4]) is enabled.
	// The output of each decoder is determined by two LSBs of in (in[1:0]).
	// // if en is LOW, both decoders must be disabled.

	Decoder_2_4 dec_lower(in[1:0], en & ~in[2], out[3:0]);
	Decoder_2_4 dec_upper(in[1:0], en & in[2], out[7:4]);

endmodule
