#include <iostream>
#include <fstream>
#include "top.h"
using namespace std;

void en(char in[], char out[]);
void de(char in[], char out[]);


/*
int main()
{
	char a[17] = { 0 }, c[17] = { 0 }, d[17] = { 0 };
	/ *cin >> a;
	en(a, c);
	cout << c << endl;
	de(c, a);
	cout << a << endl;* /

	ifstream fin("loc.txt");

	for (int i = 0; i < 40; i++)
	{
		fin >> a;
		cout << a << " ";
		en(a, c);
		cout << c << " ";
		de(c, d);
		cout << d << endl;
	}



	fin.close();
	system("pause");
}*/

char xor(char a, char b)
{
	if (a == b)
		return '0';
	else
		return '1';
}

int eval(char a)
{
	if (a == '0')
		return 0;
	if (a == '1')
		return 1;
}

char eval(int a)
{
	if (a == 0)
		return '0';
	if (a == 1)
		return '1';
}

int eval(char a, char b)
{
	if (a == '0'&&b == '0')
		return 0;
	if (a == '0'&&b == '1')
		return 1;
	if (a == '1'&&b == '0')
		return 2;
	if (a == '1'&&b == '1')
		return 3;
}

int eval(char a, char b, char c, char d)
{
	return eval(a) * 8 + eval(b) * 4 + eval(c) * 2 + eval(d);
}

void eval(int a, char b[])
{
	int d1 = a / 8;
	a %= 8;
	int d2 = a / 4;
	a %= 4;
	int d3 = a / 2;
	a %= 2;
	int d4 = a;
	b[0] = eval(d1);
	b[1] = eval(d2);
	b[2] = eval(d3);
	b[3] = eval(d4);
}

void f(char b[], char out[], char k1[])
{
	/////////////////////////////////////////
	int ep[12] = { 8,1,2,3,4,5,4,5,6,7,8,1 };
	char epr[12];
	for (int i = 0; i < 12; i++)
		epr[i] = b[ep[i] + 7];

	/////////////////////////////////////////
	char s[12];
	for (int i = 0; i < 12; i++)
		s[i] = xor (epr[i], k1[i]);

	int s0[4][16] = {
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
	};
	int s1[4][16] = {
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
	};
	char tmp1[2][4];
	/*
		cout << s[0] << s[5] << endl;
		cout << eval(s[0], s[5]) << endl;
		cout << s[6] << s[11] << endl;
		cout << eval(s[6], s[11]) << endl;
		cout << s[1]<< s[2]<<  s[3] << s[4]<<endl;
		cout << " " << eval(s[1], s[2], s[3], s[4]) << endl;
		cout << s[7]<<s[8] << s[9] << s[10] << endl;
		cout << " " << eval(s[7], s[8], s[9], s[10]) << endl;
		cout << s0[eval(s[0], s[5])][eval(s[1], s[2], s[3], s[4])] << endl;
		cout << s1[eval(s[6], s[11])][eval(s[7], s[8], s[9], s[10])] << endl;*/
	eval(s0[eval(s[0], s[5])][eval(s[1], s[2], s[3], s[4])], tmp1[0]);
	eval(s1[eval(s[6], s[11])][eval(s[7], s[8], s[9], s[10])], tmp1[1]);
	/*cout << s[0] << s[5] << " " << s[1] << s[2] << s[3] << s[4] << "    ";
	cout << s[6] << s[11] << " " << s[7] << s[8] << s[9] << s[10] << endl;*/
	char p4[8];
	p4[0] = tmp1[0][3];
	p4[1] = tmp1[1][1];
	p4[2] = tmp1[1][3];
	p4[3] = tmp1[0][2];
	p4[4] = tmp1[0][1];
	p4[5] = tmp1[1][2];
	p4[6] = tmp1[1][0];
	p4[7] = tmp1[0][0];

	/////////////////////////////////////////
	/*char r1[4], l1[4];
	for (int i = 0; i < 4; i++)
	{
	r1[i] = xor (p4[i], b[i]);
	l1[i] = b[i + 4];
	}
	for (int i = 0; i < 4; i++)
	{
	out[i] = l1[i];
	out[i + 4] = r1[i];
	}*/
	for (int i = 0; i < 8; i++)
	{
		out[i] = p4[i];
		/*cout << out[i];*/
	}
	/*cout << endl;*/


}

void en(char in[], char out[],char k1[],char k2[])
{
	/*char k1[12] = { '1','0','1','0','0','0','1','1','0','1','1','1' };
	char k2[12] = { '0','0','1','1','1','1','1','0','1','0','0','1' };*/

	char b[16], c[16], d[16];
	int ip[16] = { 6,1,12,3,16,7,14,15,10,2,11,5,9,4,13,8 };
	for (int i = 0; i < 16; i++)
		b[i] = in[ip[i] - 1];

	/*for (int i = 0; i < 16; i++)cout << b[i];
	cout << endl;*/

	f(b, c, k1);

	char r1[8], l1[8];
	char b1[16];
	for (int i = 0; i < 8; i++)
	{
		r1[i] = xor (c[i], b[i]);
		l1[i] = b[i + 8];
	}

	/*
		for (int i = 0; i < 8; i++)
			cout << l1[i];
		cout << "    ";
		for (int i = 0; i < 8; i++)
			cout << r1[i];
		cout << endl;*/

	for (int i = 0; i < 8; i++)
	{
		b1[i] = l1[i];
		b1[i + 8] = r1[i];
	}

	f(b1, d, k2);


	//char r1[4], l1[4];
	char b2[16];
	for (int i = 0; i < 8; i++)
	{
		l1[i] = xor (d[i], b1[i]);
		r1[i] = b1[i + 8];
	}


	/*
		for (int i = 0; i < 8; i++)
			cout << l1[i];
		cout << "    ";
		for (int i = 0; i < 8; i++)
			cout << r1[i];
		cout << endl;*/

	for (int i = 0; i < 8; i++)
	{
		b2[i] = l1[i];
		b2[i + 8] = r1[i];
	}

	int ip2[16] = { 2,10,4,14,12,1,6,16,13,9,11,3,15,7,8,5 };
	for (int i = 0; i < 16; i++)
		out[i] = b2[ip2[i] - 1];

}

void de(char in[], char out[])
{
	char k1[12] = { '1','0','1','0','0','0','1','1','0','1','1','1' };
	char k2[12] = { '0','0','1','1','1','1','1','0','1','0','0','1' };

	char b[16], c[16], d[16];
	int ip[16] = { 6,1,12,3,16,7,14,15,10,2,11,5,9,4,13,8 };
	for (int i = 0; i < 16; i++)
		b[i] = in[ip[i] - 1];

	/*for (int i = 0; i < 16; i++)cout << b[i];
	cout << endl;*/

	f(b, c, k2);

	char r1[8], l1[8];
	char b1[16];
	for (int i = 0; i < 8; i++)
	{
		r1[i] = xor (c[i], b[i]);
		l1[i] = b[i + 8];
	}


	/*
		for (int i = 0; i < 8; i++)
			cout << l1[i];
		cout << "    ";
		for (int i = 0; i < 8; i++)
			cout << r1[i];
		cout << endl;*/

	for (int i = 0; i < 8; i++)
	{
		b1[i] = l1[i];
		b1[i + 8] = r1[i];
	}

	f(b1, d, k1);


	//char r1[4], l1[4];
	char b2[16];
	for (int i = 0; i < 8; i++)
	{
		l1[i] = xor (d[i], b1[i]);
		r1[i] = b1[i + 8];
	}


	/*
		for (int i = 0; i < 8; i++)
			cout << l1[i];
		cout << "    ";
		for (int i = 0; i < 8; i++)
			cout << r1[i];
		cout << endl;*/

	for (int i = 0; i < 8; i++)
	{
		b2[i] = l1[i];
		b2[i + 8] = r1[i];
	}

	int ip2[16] = { 2,10,4,14,12,1,6,16,13,9,11,3,15,7,8,5 };
	for (int i = 0; i < 16; i++)
		out[i] = b2[ip2[i] - 1];

}

