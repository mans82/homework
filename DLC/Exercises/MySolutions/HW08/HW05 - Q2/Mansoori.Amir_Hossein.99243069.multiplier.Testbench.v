`include "Mansoori.Amir_Hossein.99243069.multiplier.v"

module multiplier_tb();

	reg [2:0] a;
	reg [2:0] b;
	wire [5:0] out;

	multiplier my_multiplier(out[0], out[1], out[2], out[3], out[4], out[5], a[0], a[1], a[2], b[0], b[1], b[2]); 

	initial begin
		a = 0;

		b = 0;
		#100;
		b = 1;
		#100;
		b = 3;
		#100;
		b = 7;
		#100;

		b = 0;

		a = 3;
		#100;
		a = 7;
		#100;

		a = 1;

		b = 2;
		#100;
		b = 6;
		#100;

		b = 1;

		a = 4;
		#100;
		a = 5;
		#100;

		b = 2;

		a = 3;
		#100;
		b = 5;
		#100;
		b = 7;
		#100;

		b = 3;

		a = 3;
		#100;
		a = 6;
		#100;

		b = 5;
		
		a = 3;
		#100;
		a = 7;
		#100;

		b = 7;
		
		a = 4;
		#100;
		a = 7;
		#100;
	end

	
endmodule
