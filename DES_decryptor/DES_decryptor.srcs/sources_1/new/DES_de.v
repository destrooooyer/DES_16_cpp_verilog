`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/11 19:35:03
// Design Name: 
// Module Name: DES_de
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


module DES_de(
	// input [11:0] key1,
	// input [11:0] key2,
	input [15:0] dIn,
	output [15:0] dOut,
	
	input clk,
	input rst,
	input en,
	output valid

    );
	
	// key generator
	wire [63:0] urn;
	wire [11:0] key1;
	wire [11:0] key2;
	urn_gen keyGen
    (
        .clk(clk),
        .rst(rst),
        .urn(urn)
    );
	assign key1=urn[23:12];
	assign key2=urn[11:0];
	
	// shift regs
	reg [11:0] key2Shift[0:2];
	reg [15:0] dInShift[0:1];
	
	// stage 0: IP, regs shift
	reg [15:0] ip;
	// reg [11:0] key1Shift0;
	// reg [11:0] key2Shift0;
	always @(posedge clk)
	begin
		ip<=
		{
			dIn[10],dIn[15],dIn[4],dIn[13],dIn[0],dIn[9],dIn[2],dIn[1],
			dIn[6],dIn[14],dIn[5],dIn[11],dIn[7],dIn[12],dIn[3],dIn[8]
		};
	end
	// assign ip=
	// {
		// dIn[10],dIn[15],dIn[4],dIn[13],dIn[0],dIn[9],dIn[2],dIn[1],
		// dIn[6],dIn[14],dIn[5],dIn[11],dIn[7],dIn[12],dIn[3],dIn[8]
	// };
	
	// always @(posedge clk)
	// begin
		// key2Shift0<=key2;
		// key1Shift0<=key1;
	// end
	
	//////////////////////////////////////////////
	//	iteration 1
	//////////////////////////////////////////////
	
	// E/P
	wire [11:0] ep0;
	assign ep0=
	{
		ip[0],ip[7],ip[6],ip[5],ip[4],ip[3],
		ip[4],ip[3],ip[2],ip[1],ip[0],ip[7]
	};
	
	// stage 1: ep0 xor key1, regs shift
	reg [11:0] s0;
	
	always @(posedge clk)
	begin
		s0<=ep0^key1;
	end
	
	always @(posedge clk)
	begin
		key2Shift[0]<=key2;
		dInShift[0]<=ip;
	end
	
	// stage 2: S box, regs shift
	reg [3:0] x01;
	reg [3:0] x02;
	
	always @(posedge clk) begin
		case ({s0[11], s0[6], s0[10:7]})
			 0: x01 = 14;   1: x01 =  4;   2: x01 = 13;   3: x01 =  1;
			 4: x01 =  2;   5: x01 = 15;   6: x01 = 11;   7: x01 =  8;
			 8: x01 =  3;   9: x01 = 10;  10: x01 =  6;  11: x01 = 12;
			12: x01 =  5;  13: x01 =  9;  14: x01 =  0;  15: x01 =  7;
			16: x01 =  0;  17: x01 = 15;  18: x01 =  7;  19: x01 =  4;
			20: x01 = 14;  21: x01 =  2;  22: x01 = 13;  23: x01 =  1;
			24: x01 = 10;  25: x01 =  6;  26: x01 = 12;  27: x01 = 11;
			28: x01 =  9;  29: x01 =  5;  30: x01 =  3;  31: x01 =  8;
			32: x01 =  4;  33: x01 =  1;  34: x01 = 14;  35: x01 =  8;
			36: x01 = 13;  37: x01 =  6;  38: x01 =  2;  39: x01 = 11;
			40: x01 = 15;  41: x01 = 12;  42: x01 =  9;  43: x01 =  7;
			44: x01 =  3;  45: x01 = 10;  46: x01 =  5;  47: x01 =  0;
			48: x01 = 15;  49: x01 = 12;  50: x01 =  8;  51: x01 =  2;
			52: x01 =  4;  53: x01 =  9;  54: x01 =  1;  55: x01 =  7;
			56: x01 =  5;  57: x01 = 11;  58: x01 =  3;  59: x01 = 14;
			60: x01 = 10;  61: x01 =  0;  62: x01 =  6;  63: x01 = 13;
		endcase
	end
	
	always @(posedge clk) begin
		case ({s0[5], s0[0], s0[4:1]})
			 0: x02 = 15;   1: x02 =  1;   2: x02 =  8;   3: x02 = 14;
			 4: x02 =  6;   5: x02 = 11;   6: x02 =  3;   7: x02 =  4;
			 8: x02 =  9;   9: x02 =  7;  10: x02 =  2;  11: x02 = 13;
			12: x02 = 12;  13: x02 =  0;  14: x02 =  5;  15: x02 = 10;
			16: x02 =  3;  17: x02 = 13;  18: x02 =  4;  19: x02 =  7;
			20: x02 = 15;  21: x02 =  2;  22: x02 =  8;  23: x02 = 14;
			24: x02 = 12;  25: x02 =  0;  26: x02 =  1;  27: x02 = 10;
			28: x02 =  6;  29: x02 =  9;  30: x02 = 11;  31: x02 =  5;
			32: x02 =  0;  33: x02 = 14;  34: x02 =  7;  35: x02 = 11;
			36: x02 = 10;  37: x02 =  4;  38: x02 = 13;  39: x02 =  1;
			40: x02 =  5;  41: x02 =  8;  42: x02 = 12;  43: x02 =  6;
			44: x02 =  9;  45: x02 =  3;  46: x02 =  2;  47: x02 = 15;
			48: x02 = 13;  49: x02 =  8;  50: x02 = 10;  51: x02 =  1;
			52: x02 =  3;  53: x02 = 15;  54: x02 =  4;  55: x02 =  2;
			56: x02 = 11;  57: x02 =  6;  58: x02 =  7;  59: x02 = 12;
			60: x02 =  0;  61: x02 =  5;  62: x02 = 14;  63: x02 =  9;
		endcase
	end
	
	always @(posedge clk)
	begin
		key2Shift[1]<=key2Shift[0];
		dInShift[1]<=dInShift[0];
	end
	
	// P8
	wire [7:0] p80;
	assign p80=
	{
		x01[0],x02[2],x02[0],x01[1],
		x01[2],x02[1],x02[3],x01[3]
	};
	
	// stage 3: P8 xor L0, regs shift
	reg [7:0] l1;
	reg [7:0] r1;
	
	always @(posedge clk)
	begin
		r1<=p80^dInShift[1][15:8];
		l1<=dInShift[1][7:0];
	end
	
	always @(posedge clk)
	begin
		key2Shift[2]<=key2Shift[1];
	end
	
	
	
	//////////////////////////////////////////////
	//	iteration 2
	//////////////////////////////////////////////
	
	// E/P
	wire [11:0] ep1;
	assign ep1=
	{
		r1[0],r1[7],r1[6],r1[5],r1[4],r1[3],
		r1[4],r1[3],r1[2],r1[1],r1[0],r1[7]
	};
	
	// stage 4: ep1 xor key2, regs shift
	reg [11:0] s1;
	reg [15:0] dIn2Shift[0:1];
	
	always @(posedge clk)
	begin
		s1<=ep1^key2Shift[2];
	end
	
	always @(posedge clk)
	begin
		dIn2Shift[0]<={l1,r1};
	end
	
	// stage 5: S box, regs shift
	reg [3:0] x11;
	reg [3:0] x12;
	
	always @(posedge clk) begin
		case ({s1[11], s1[6], s1[10:7]})
			 0: x11 = 14;   1: x11 =  4;   2: x11 = 13;   3: x11 =  1;
			 4: x11 =  2;   5: x11 = 15;   6: x11 = 11;   7: x11 =  8;
			 8: x11 =  3;   9: x11 = 10;  10: x11 =  6;  11: x11 = 12;
			12: x11 =  5;  13: x11 =  9;  14: x11 =  0;  15: x11 =  7;
			16: x11 =  0;  17: x11 = 15;  18: x11 =  7;  19: x11 =  4;
			20: x11 = 14;  21: x11 =  2;  22: x11 = 13;  23: x11 =  1;
			24: x11 = 10;  25: x11 =  6;  26: x11 = 12;  27: x11 = 11;
			28: x11 =  9;  29: x11 =  5;  30: x11 =  3;  31: x11 =  8;
			32: x11 =  4;  33: x11 =  1;  34: x11 = 14;  35: x11 =  8;
			36: x11 = 13;  37: x11 =  6;  38: x11 =  2;  39: x11 = 11;
			40: x11 = 15;  41: x11 = 12;  42: x11 =  9;  43: x11 =  7;
			44: x11 =  3;  45: x11 = 10;  46: x11 =  5;  47: x11 =  0;
			48: x11 = 15;  49: x11 = 12;  50: x11 =  8;  51: x11 =  2;
			52: x11 =  4;  53: x11 =  9;  54: x11 =  1;  55: x11 =  7;
			56: x11 =  5;  57: x11 = 11;  58: x11 =  3;  59: x11 = 14;
			60: x11 = 10;  61: x11 =  0;  62: x11 =  6;  63: x11 = 13;
		endcase
	end
	
	always @(posedge clk) begin
		case ({s1[5], s1[0], s1[4:1]})
			 0: x12 = 15;   1: x12 =  1;   2: x12 =  8;   3: x12 = 14;
			 4: x12 =  6;   5: x12 = 11;   6: x12 =  3;   7: x12 =  4;
			 8: x12 =  9;   9: x12 =  7;  10: x12 =  2;  11: x12 = 13;
			12: x12 = 12;  13: x12 =  0;  14: x12 =  5;  15: x12 = 10;
			16: x12 =  3;  17: x12 = 13;  18: x12 =  4;  19: x12 =  7;
			20: x12 = 15;  21: x12 =  2;  22: x12 =  8;  23: x12 = 14;
			24: x12 = 12;  25: x12 =  0;  26: x12 =  1;  27: x12 = 10;
			28: x12 =  6;  29: x12 =  9;  30: x12 = 11;  31: x12 =  5;
			32: x12 =  0;  33: x12 = 14;  34: x12 =  7;  35: x12 = 11;
			36: x12 = 10;  37: x12 =  4;  38: x12 = 13;  39: x12 =  1;
			40: x12 =  5;  41: x12 =  8;  42: x12 = 12;  43: x12 =  6;
			44: x12 =  9;  45: x12 =  3;  46: x12 =  2;  47: x12 = 15;
			48: x12 = 13;  49: x12 =  8;  50: x12 = 10;  51: x12 =  1;
			52: x12 =  3;  53: x12 = 15;  54: x12 =  4;  55: x12 =  2;
			56: x12 = 11;  57: x12 =  6;  58: x12 =  7;  59: x12 = 12;
			60: x12 =  0;  61: x12 =  5;  62: x12 = 14;  63: x12 =  9;
		endcase
	end
	
	always @(posedge clk)
	begin
		dIn2Shift[1]<=dIn2Shift[0];
	end
	
	// P8
	wire [7:0] p81;
	assign p81=
	{
		x11[0],x12[2],x12[0],x11[1],
		x11[2],x12[1],x12[3],x11[3]
	};
	
	// stage 6: P8 xor L0, regs shift
	reg [7:0] l2;
	reg [7:0] r2;
	wire [15:0] lr2;
	
	always @(posedge clk)
	begin
		l2<=p81^dIn2Shift[1][15:8];
		r2<=dIn2Shift[1][7:0];
	end
	assign lr2={l2,r2};
	
	assign dOut=
	{
		lr2[14],lr2[6],lr2[12],lr2[2],lr2[4],lr2[15],lr2[10],lr2[0],
		lr2[3],lr2[7],lr2[5],lr2[13],lr2[1],lr2[9],lr2[8],lr2[11]
	};
	
	// en shift
	reg enShift [0:6];
	always @(posedge clk)
	begin
		if(rst==1)
		begin
			enShift[0]<=0;
			enShift[1]<=0;
			enShift[2]<=0;
			enShift[3]<=0;
			enShift[4]<=0;
			enShift[5]<=0;
			enShift[6]<=0;
		end
		
		else
		begin
			enShift[0]<=en;
			enShift[1]<=enShift[0];
			enShift[2]<=enShift[1];
			enShift[3]<=enShift[2];
			enShift[4]<=enShift[3];
			enShift[5]<=enShift[4];
			enShift[6]<=enShift[5];
		end
	end
	assign valid=enShift[6];
	
endmodule
