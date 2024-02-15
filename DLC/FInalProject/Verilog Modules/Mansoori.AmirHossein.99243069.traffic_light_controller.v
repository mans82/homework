`include "counter.v"

module traffic_light_controller (light_a, light_b, clk, rst);
	input clk;
	input rst;
	
	output reg [2:0] light_a; // West-East
	output reg [2:0] light_b; // North-South
	
	/* The module has these states:
	   State    State code
	   S0       000
	   s1       001
	   s2       010
	   s3       011
	   s4       100
	   s5       101
	   sN  110
	*/ 

	reg [2:0] state = 3'b000;
	reg [2:0] next_state = 3'b000;
	
	wire ctr6;
	wire ctr1;
	reg ctr1_reset = 0;
	reg ctr6_reset = 0;
	
	counter #(.COUNT(6000)) ctr6_module(out6, clk, ctr6_reset);
	counter #(.COUNT(1000)) ctr1_module(out1, clk, ctr1_reset);
	
	always @ (posedge clk or posedge rst) begin
		if (rst) begin
			state <= 3'b110;
		end
		else state <= next_state;
	end
	
	always @ (state, rst, out6, out1) begin
		// Determine next state
		next_state = state;
		if (state == 3'b110 && ~rst) next_state = 3'b000;
		else if (state == 3'b000 && !out6) begin
			next_state = 3'b000;
		end
		else if (state == 3'b000 && out6) begin
			next_state = 3'b001;
		end
		else if (state == 3'b001 && !out1) begin
			next_state = 3'b001;
		end
		else if (state == 3'b001 && out1) begin
			next_state = 3'b010;
		end
		else if (state == 3'b010 && !out1) begin
			next_state = 3'b010;
		end
		else if (state == 3'b010 && out1) begin
			next_state = 3'b011;
		end
		else if (state == 3'b011 && !out6) begin
			next_state = 3'b011;
		end
		else if (state == 3'b011 && out6) begin
			next_state = 3'b100;
		end
		else if (state == 3'b100 && !out1) begin
			next_state = 3'b100;
		end
		else if (state == 3'b100 && out1) begin
			next_state = 3'b101;
		end
		else if (state == 3'b101 && !out1) begin
			next_state = 3'b101;
		end
		else if (state == 3'b101 && out1) begin
			next_state = 3'b000;
		end
	end
	
		
	always @ (state) begin
		// Determine output from state
		case (state)
			3'b000: begin
				light_a <= 3'b100;
				light_b <= 3'b001;
				ctr1_reset <= 1'b0;
				ctr6_reset <= 1'b0;
			end
			3'b001: begin
				light_a <= 3'b010;
				light_b <= 3'b001;
				ctr1_reset <= 1'b0;
				ctr6_reset <= 1'b1;
			end
			3'b010: begin
				light_a <= 3'b001;
				light_b <= 3'b001;
				ctr1_reset <= 1'b0;
				ctr6_reset <= 1'b1;
			end
			3'b011: begin
				light_a <= 3'b001;
				light_b <= 3'b100;
				ctr1_reset <= 1'b0;
				ctr6_reset <= 1'b0;
			end
			3'b100: begin
				light_a <= 3'b001;
				light_b <= 3'b010;
				ctr1_reset <= 1'b0;
				ctr6_reset <= 1'b1;
			end
			3'b101: begin
				light_a <= 3'b001;
				light_b <= 3'b001;
				ctr1_reset <= 1'b0;
				ctr6_reset <= 1'b1;
			end
			3'b110: begin // Reset state
				light_a <= 3'b000;
				light_b <= 3'b000;
				ctr1_reset <= 1;
				ctr6_reset <= 1;
			end
		endcase
	end
endmodule