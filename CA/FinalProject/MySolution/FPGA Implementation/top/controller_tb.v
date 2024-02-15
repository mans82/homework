module controller_tb;
	reg clk;
	reg reset;
	reg [6:0] op;
	reg [2:0] funct3;
	reg funct7b5;
	reg Zero;
	wire [1:0] ImmSrc;
	wire [1:0] ALUSrcA;
	wire [1:0] ALUSrcB;
	wire [1:0] ResultSrc;
	wire AdrSrc;
	wire [2:0] ALUControl;
	wire IRWrite;
	wire PCWrite;
	wire RegWrite;
	wire MemWrite;
	reg [31:0] vectornum;
	reg [31:0] errors;
	reg [39:0] testvectors [10000:0];
	reg new_error;
	reg [15:0] expected;
	reg [6:0] hash;
	controller dut(
		.clk(clk),
		.reset(reset),
		.op(op),
		.funct3(funct3),
		.funct7b5(funct7b5),
		.funct7b0(Zero),
		.Zero(ImmSrc),
		.ImmSrc(ALUSrcA),
		.ALUSrcA(ALUSrcB),
		.ALUSrcB(ResultSrc),
		.ResultSrc(AdrSrc),
		.AdrSrc(ALUControl),
		.ALUControl(IRWrite),
		.IRWrite(PCWrite),
		.PCWrite(RegWrite),
		.RegWrite(MemWrite)
	);
	always begin
		clk = 1;
		#(5)
			;
		clk = 0;
		#(5)
			;
	end
	initial begin
		$readmemb("../../controller.tv", testvectors);
		vectornum = 0;
		errors = 0;
		hash = 0;
		reset = 1;
		#(22)
			;
		reset = 0;
	end
	always @(posedge clk) begin
		#(1)
			;
		{op, funct3, funct7b5, Zero, expected} = testvectors[vectornum];
	end
	always @(negedge clk)
		if (~reset) begin
			new_error = 0;
			if ((ImmSrc !== expected[15:14]) && (expected[15:14] !== 2'bxx)) begin
				$display("   ImmSrc = %b      Expected %b", ImmSrc, expected[15:14]);
				new_error = 1;
			end
			if ((ALUSrcA !== expected[13:12]) && (expected[13:12] !== 2'bxx)) begin
				$display("   ALUSrcA = %b     Expected %b", ALUSrcA, expected[13:12]);
				new_error = 1;
			end
			if ((ALUSrcB !== expected[11:10]) && (expected[11:10] !== 2'bxx)) begin
				$display("   ALUSrcB = %b     Expected %b", ALUSrcB, expected[11:10]);
				new_error = 1;
			end
			if ((ResultSrc !== expected[9:8]) && (expected[9:8] !== 2'bxx)) begin
				$display("   ResultSrc = %b   Expected %b", ResultSrc, expected[9:8]);
				new_error = 1;
			end
			if ((AdrSrc !== expected[7]) && (expected[7] !== 1'bx)) begin
				$display("   AdrSrc = %b       Expected %b", AdrSrc, expected[7]);
				new_error = 1;
			end
			if ((ALUControl !== expected[6:4]) && (expected[6:4] !== 3'bxxx)) begin
				$display("   ALUControl = %b Expected %b", ALUControl, expected[6:4]);
				new_error = 1;
			end
			if ((IRWrite !== expected[3]) && (expected[3] !== 1'bx)) begin
				$display("   IRWrite = %b      Expected %b", IRWrite, expected[3]);
				new_error = 1;
			end
			if ((PCWrite !== expected[2]) && (expected[2] !== 1'bx)) begin
				$display("   PCWrite = %b      Expected %b", PCWrite, expected[2]);
				new_error = 1;
			end
			if ((RegWrite !== expected[1]) && (expected[1] !== 1'bx)) begin
				$display("   RegWrite = %b     Expected %b", RegWrite, expected[1]);
				new_error = 1;
			end
			if ((MemWrite !== expected[0]) && (expected[0] !== 1'bx)) begin
				$display("   MemWrite = %b     Expected %b", MemWrite, expected[0]);
				new_error = 1;
			end
			if (new_error) begin
				$display("Error on vector %d: inputs: op = %h funct3 = %h funct7b5 = %h", vectornum, op, funct3, funct7b5);
				errors = errors + 1;
			end
			vectornum = vectornum + 1;
			hash = (((hash ^ {ImmSrc & {2 {expected[15:14] !== 2'bxx}}, ALUSrcA & {2 {expected[13:12] !== 2'bxx}}}) ^ {ALUSrcB & {2 {expected[11:10] !== 2'bxx}}, ResultSrc & {2 {expected[9:8] !== 2'bxx}}}) ^ {AdrSrc & {expected[7] !== 1'bx}, ALUControl & {3 {expected[6:4] !== 3'bxxx}}}) ^ {IRWrite & {expected[3] !== 1'bx}, PCWrite & {expected[2] !== 1'bx}, RegWrite & {expected[1] !== 1'bx}, MemWrite & {expected[0] !== 1'bx}};
			hash = {hash[5:0], hash[6] ^ hash[5]};
			if (testvectors[vectornum] === 40'bxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx) begin
				$display("%d tests completed with %d errors", vectornum, errors);
				$display("hash = %h", hash);
				$stop;
			end
		end
endmodule
