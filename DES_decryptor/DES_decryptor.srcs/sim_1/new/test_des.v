`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/11 22:38:06
// Design Name: 
// Module Name: test_des
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


module test_des(

    );
	reg clk=1;
	reg rst=0;
	reg en=0;
	reg [11:0] key1=12'b101000110111;
	reg [11:0] key2=12'b001111101001;
	reg [15:0] dIn=0;
    reg [15:0] dIn2=0;
	wire [15:0] dOut;
	wire [15:0] dOut2;
	wire [15:0] dOut3;
	wire valid;
	wire [63:0] urn;
	
	initial
	begin
	   rst=1;
	   #20
	   rst=0;
	   en=1;
	   // dIn=16'b1010101010101010;
	   // #2
	   // dIn=16'b1111111111111111;
	   // #2
	   // dIn=16'b1111000011110000;
	   // #2
	   // dIn=16'b0000111100001111;
	   // #2
	   dIn=0;
	   #40;
	   en=0;
	end
	
	
	always #1 clk=~clk;
	
	DES_de des
	(
		// .key1(key1),
		// .key2(key2),
		.dIn(dIn),
		.dOut(dOut),
		
		.clk(clk),
		.rst(rst),
		.en(en),
		.valid(valid)

    );
	DES_de des2
	(
		// .key1(key1),
		// .key2(key2),
		.dIn(16'b1010101010101010),
		.dOut(dOut2),
		
		.clk(clk),
		.rst(rst),
		.en(en)
		//.valid(valid)

    );
	DES_de des3
	(
		// .key1(key1),
		// .key2(key2),
		.dIn(dIn2),
		.dOut(dOut3),
		
		.clk(clk),
		.rst(rst),
		.en(en)
		//.valid(valid)

    );
    
    urn_gen keyGen
    (
        .clk(clk),
        .rst(rst),
        .urn(urn)
    );
	
endmodule
