//`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 17.04.2023 15:36:15
// Design Name: 
// Module Name: Xor
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Xor#(parameter DATA_WIDTH=128)
(input [DATA_WIDTH-1:0] a,input [DATA_WIDTH-1:0] b,output reg [DATA_WIDTH-1:0] c);

    always @(*) begin
        c = a ^ b;
    end
    
endmodule

