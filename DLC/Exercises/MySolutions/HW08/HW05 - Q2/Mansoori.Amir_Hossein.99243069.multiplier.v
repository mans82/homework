// 3-bit multiplier, using only NAND gates.
// Based on schematic from https://circuitverse.org/users/109412/projects/hw05-q2-99243069
// Author: Amir Hossein Mansoori (Student No. 99243069)

module multiplier(p0, p1, p2, p3, p4, p5, a0, a1, a2, b0, b1, b2);
	input a0, a1, a2, b0, b1, b2;
	output p0, p1, p2, p3, p4, p5;

	// Compute p0
	wire a0_nand_b0;
	nand(a0_nand_b0, a0, b0);
	nand(p0, a0_nand_b0, a0_nand_b0); // Acts as invertor gate
	// End of computing p0
	
	// Compute p1
	wire a0_nand_b1;
	wire a1_nand_b0;
	wire a0_and_b1;
	wire a1_and_b0;
	
	nand(a0_nand_b1, a0, b1);
	nand(a1_nand_b0, a1, b0);
	nand(a0_and_b1, a0_nand_b1, a0_nand_b1); // Acts as invertor gate
	nand(a1_and_b0, a1_nand_b0, a1_nand_b0); // Acts as invertor gate
	
	// Half-Adder for adding a0_and_b1 and a1_and_b0
	wire inter0_0, inter0_1, inter0_2; // Intermediary wires
	wire c_out0; // Carry out
	
	nand(inter0_0, a0_and_b1, a1_and_b0);
	nand(inter0_1, inter0_0, a0_and_b1);
	nand(inter0_2, inter0_0, a1_and_b0);
	
	nand(p1, inter0_1, inter0_2); // Output to p1
	nand(c_out0, inter0_0, inter0_0);
	// End of Half-Adder
	// End of computing p1
	
	// Compute p2
	wire a0_nand_b2, a1_nand_b1, a2_nand_b0;
	wire a0_and_b2, a1_and_b1, a2_and_b0;
	
	nand(a0_nand_b2, a0, b2);
	nand(a1_nand_b1, a1, b1);
	
	nand(a0_and_b2, a0_nand_b2, a0_nand_b2); // Acts as invertor gate
	nand(a1_and_b1, a1_nand_b1, a1_nand_b1); // Acts as invertor gate
	
	// Full-Adder for adding a0_and_b2 and a1_and_b1
	wire inter1_0, inter1_1, inter1_2, inter1_3, inter1_4, inter1_5, inter1_6; // Intermediary wires
	wire s_1, c_out1; // Sum, and carry out
	
	nand(inter1_0, a0_and_b2, a1_and_b1);
	nand(inter1_1, a0_and_b2, inter1_0);
	nand(inter1_2, inter1_0, a1_and_b1);
	nand(inter1_3, inter1_1, inter1_2);
	
	nand(inter1_4, inter1_3, c_out0);
	nand(inter1_5, inter1_3, inter1_4);
	nand(inter1_6, inter1_4, c_out0);
	nand(s_1, inter1_5, inter1_6);
	
	nand(c_out1, inter1_0, inter1_4);
	// End of Full-Adder
	
	nand(a2_nand_b0, a2, b0);
	nand(a2_and_b0, a2_nand_b0, a2_nand_b0); // Acts as invertor gate

	// Half-Adder for adding s_1 and a2_and_b0
	wire inter2_0, inter2_1, inter2_2; // Intermediary wires
	wire c_out2; // Carry out

	nand(inter2_0, s_1, a2_and_b0);
	nand(inter2_1, s_1, inter2_0);
	nand(inter2_2, inter2_0, a2_and_b0);
	
	nand(p2, inter2_1, inter2_2);
	nand(c_out2, inter2_0, inter2_0);
	// End of Half-Adder
	// End of computing p2
	
	// Compute p3
	wire a2_nand_b1, a1_nand_b2;
	wire a2_and_b1, a1_and_b2;
	wire c_out1_xor_c_out2;

	nand(a2_nand_b1, a2, b1);
	nand(a1_nand_b2, a1, b2);
	
	nand(a2_and_b1, a2_nand_b1, a2_nand_b1); // Acts as invertor gate
	nand(a1_and_b2, a1_nand_b2, a1_nand_b2); // Acts as invertor gate

	// XOR c_out1 and c_out2
	wire inter3_0, inter3_1, inter3_2;
	nand(inter3_0, c_out1, c_out2);
	nand(inter3_1, c_out1, inter3_0);
	nand(inter3_2, inter3_0, c_out2);
	nand(c_out1_xor_c_out2, inter3_1, inter3_2);
	// End of XOR

	// Full-Adder for adding a2_nand_b1 and a1_nand_b2
	wire inter4_0, inter4_1, inter4_2, inter4_3, inter4_4, inter4_5, inter4_6; // Intermediary wires
	wire c_out3; // Carry out

	nand(inter4_0, a2_and_b1, a1_and_b2);
	nand(inter4_1, a2_and_b1, inter4_0);
	nand(inter4_2, inter4_0, a1_and_b2);
	nand(inter4_3, inter4_1, inter4_2);

	nand(inter4_4, inter4_3, c_out1_xor_c_out2);
	nand(inter4_5, inter4_3, inter4_4);
	nand(inter4_6, inter4_4, c_out1_xor_c_out2);

	nand(p3, inter4_5, inter4_6);
	nand(c_out3, inter4_4, inter4_0);
	// End of Full-Adder
	// End of computing p3
	
	// Compute p4 and p5
	wire a2_nand_b2, c_out1_nand_c_out2;
	wire a2_and_b2, c_out1_and_c_out2;

	nand(a2_nand_b2, a2, b2);
	nand(c_out1_nand_c_out2, c_out1, c_out2);

	nand(a2_and_b2, a2_nand_b2, a2_nand_b2);
	nand(c_out1_and_c_out2, c_out1_nand_c_out2, c_out1_nand_c_out2);

	// Full-Adder for adding a2_nand_b1 and a1_nand_b2
	wire inter5_0, inter5_1, inter5_2, inter5_3, inter5_4, inter5_5, inter5_6; // Intermediary wires

	nand(inter5_0, a2_and_b2, c_out3);
	nand(inter5_1, a2_and_b2, inter5_0);
	nand(inter5_2, inter5_0, c_out3);
	nand(inter5_3, inter5_1, inter5_2);

	nand(inter5_4, inter5_3, c_out1_and_c_out2);
	nand(inter5_5, inter5_3, inter5_4);
	nand(inter5_6, inter5_4, c_out1_and_c_out2);
	
	nand(p4, inter5_5, inter5_6);
	nand(p5, inter5_0, inter5_4);
	// End of Full-Adder
	// End of computing p4 and p5
endmodule
