`include "traffic_light_controller.v"

`timescale 1ms/1us

module traffic_light_controller_tb;

	reg clk;
	reg rst;
	wire [2:0] light_a;
	wire [2:0] light_b;
	
	traffic_light_controller ctrl(light_a, light_b, clk, rst);
	
	always #0.5 clk = ~clk; // toggle every 0.5ms, for a clock period of 1ms
	
	initial begin
		clk <= 1;
		rst <= 0;
		
		#17_000 rst <= 1; // 17 sec
		#0_9999 rst <= 0; 
		#1_0001 rst <= 1;
		#0_9999 rst <= 0;
	end

endmodule