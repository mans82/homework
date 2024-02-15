// A 2 to 4 decoder.
module Decoder_2_4(
	input logic [1:0] in,
	input logic en,
	output logic [3:0] out
);

	// MSB of in (in[1]) determines what decoder to use.
	// If in[1] is LOW, the 1-to-2 decoder connected to lower part of output (out[1:0]) is enabled.
	// Otherwise, the 1-to-2 decoder connected to upper part of output (out[3:2]) is enabled.
	// The output of each decoder is determined by LSB of in (in[0]).
	// if en is LOW, both decoders must be disabled.
	Decoder_1_2 dec_lower(in[0], en & ~in[1], out[1:0]);
	Decoder_1_2 dec_upper(in[0], en & in[1], out[3:2]);

endmodule
