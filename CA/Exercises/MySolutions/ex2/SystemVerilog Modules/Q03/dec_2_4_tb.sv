module dec_2_4_tb();

	logic [1:0] in;
	logic en;
	logic [3:0] out;
	
	Decoder_2_4 dut(in, en, out);
	
	initial begin
		
		en = 1;
		in = 0;
		#10 in = 1;
		#10 in = 2;
		#10 in = 3;
		#10 en = 0;
		in = 0;
		#10 in = 2;
		#10;
	
	end

endmodule
