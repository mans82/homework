///////////////////////////////////////////////////////////////
// testbench
//
// Expect simulator to print "Simulation succeeded"
// when the value 25 (0x19) is written to address 100 (0x64)
///////////////////////////////////////////////////////////////

module testbench();

  logic        clk;
  logic        reset;

  logic [31:0] WriteData, DataAdr;
  logic        MemWrite;
  
  //logic [31:0] ReadData;

  // instantiate device to be tested
  top dut(clk, reset, WriteData, DataAdr, MemWrite);
  
  // initialize
  initial begin
		clk = 1;
		reset = 1;
		
		#22;
		reset = 0;
  end
  

  // generate clock to sequence tests
  always
    begin
      clk <= 1; # 5; clk <= 0; # 5;
    end


endmodule
