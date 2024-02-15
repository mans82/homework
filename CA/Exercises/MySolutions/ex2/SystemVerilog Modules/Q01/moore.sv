module moore(input logic clk,rst , input logic [1:0] num , output logic y);

    typedef enum logic [1:0] {S0, S1, S2, S3} statetype;

    statetype state, nextstate;
    always_ff@(posedge clk , posedge rst)
     if(rst) state <= S2;
     else state <= nextstate;

    always_comb
        case(state)
        S0: if (num == 2'b11) nextstate = S1;
            else nextstate = S2;
        S1: if (num == 2'b11 | num==2'b10) nextstate = S0;
            else nextstate = S3;
        S2: if (num == 2'b00) nextstate = S3;
            else nextstate = S1;
        S3: if (num == 2'b11 | num==2'b01) nextstate = S0;
            else nextstate	= S2;
			endcase
			
    assign y = (state == S0) | (state == S3);
endmodule
