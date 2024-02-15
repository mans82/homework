module dec_3_8_tb();

	logic [2:0] in;
	logic en;
	logic [7:0] out;
	
	Decoder_3_8 dut(in, en, out);
	
	initial begin
		
		en = 1;
		in = 0;
		#10 in = 1;
		#10 in = 2;
		#10 in = 3;
		#10 in = 4;
		#10 in = 5;
		#10 in = 6;
		#10 in = 7;
		#10 en = 0;
		in = 2;
		#10 in = 4;
		#10;
		
	end

endmodule
