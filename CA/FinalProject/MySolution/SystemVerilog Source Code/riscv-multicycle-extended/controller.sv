module controller(input  logic       clk,
                  input  logic       reset,  
                  input  logic [6:0] op,
                  input  logic [2:0] funct3,
                  input  logic       funct7b5,
						input logic        funct7b0,
                  input  logic       Zero,
                  output logic [1:0] ImmSrc,
                  output logic [1:0] ALUSrcA, ALUSrcB,
                  output logic [1:0] ResultSrc, 
                  output logic       AdrSrc,
                  output logic [3:0] ALUControl,
                  output logic       IRWrite, PCWrite, 
                  output logic       RegWrite, MemWrite);

logic Branch, PCUpdate;
logic [1:0] ALUOp; 

assign PCWrite = (Zero & Branch) | PCUpdate;

mainfsm fsm (clk, reset, op, Branch, PCUpdate, RegWrite, MemWrite, IRWrite, ResultSrc, ALUSrcA, ALUSrcB, AdrSrc, ALUOp);

aludec dec (op[5], funct3, funct7b5, funct7b0, ALUOp, ALUControl);

instrdec idec (op, ImmSrc);

endmodule
