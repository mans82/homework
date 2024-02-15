module dec_1_2_tb();

	logic in;
	logic en;
	logic [1:0] out;
	
	Decoder_1_2 dut(in, en, out);
	
	initial begin
		
		en = 1;
		in = 0;
		#10 in = 1;
		#10 en = 0;
		in = 0;
		#10 in = 1;
		#10;
	
	end

endmodule
