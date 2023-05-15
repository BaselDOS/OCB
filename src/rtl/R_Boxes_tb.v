`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/01/2023 03:51:01 PM
// Design Name: 
// Module Name: R_Boxes_tb
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


module R_Boxes_tb();

reg [7:0] word;
reg [2:0] func;
wire [7:0] result;

R_Boxes uut(.word(word),.func(func),.result(result));
initial begin
word=8'h00;
func=3'h0;
end

initial begin
func=0;
#5;
func=1;
#5;
func=2;
#5;
func=3;
#5;
func=4;
#5;
func=5;
#5;
func=6;
#5;
func=7;
#5;
word=8'b01;
func=0;
#5;
func=1;
#5;
func=2;
#5;
func=3;
#5;
func=4;
#5;
func=5;
#5;
func=6;
#5;
func=7;
#5;
word=8'hff;
func=0;
#5;
func=1;
#5;
func=2;
#5;
func=3;
#5;
func=4;
#5;
func=5;
#5;
func=6;
#5;
func=7;
#5;

$finish;
end
endmodule
