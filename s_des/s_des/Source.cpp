/*
#include <iostream>
using namespace std;

void en(char in[], char out[]);
void de(char in[], char out[]);


int main()
{
	char a[9] = { 0 }, c[9] = { 0 };
	cin >> a;
	en(a, c);
	cout << c << endl;
	de(c, a);
	cout << a << endl;

	system("pause");
}

char xor(char a, char b)
{
	if (a == b)
		return '0';
	else
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
void eval(int a, char b[])
{
	if (a == 0)
	{
		b[0] = '0';
		b[1] = '0';
	}
	if (a == 1)
	{
		b[0] = '0';
		b[1] = '1';
	}
	if (a == 2)
	{
		b[0] = '1';
		b[1] = '0';
	}
	if (a == 3)
	{
		b[0] = '1';
		b[1] = '1';
	}
}

void f(char b[], char out[], char k1[])
{
	/////////////////////////////////////////
	int ep[8] = { 4,1,2,3,2,3,4,1 };
	char epr[8];
	for (int i = 0; i < 8; i++)
		epr[i] = b[ep[i] + 3];

	/////////////////////////////////////////
	char s[8];
	for (int i = 0; i < 8; i++)
		s[i] = xor (epr[i], k1[i]);
	//int p4[4] = { 2,4,3,1 };
	/ *int s0[4][4] = {
		1,0,2,3,
		2,3,0,1,
		0,1,3,2,
		3,2,1,0
	};
	int s1[4][4] = {
		0,1,2,3,
		2,0,3,1,
		1,3,0,2,
		3,2,1,0
	};* /
	int s0[4][4] = {
		1,3,2,0,
		2,3,1,0,
		0,2,3,1,
		2,1,3,0
	};
	int s1[4][4] = {
		0,1,2,3,
		1,0,3,2,
		3,2,1,0,
		2,1,0,3
	};
	char tmp1[2][2];
	eval(s0[eval(s[0], s[3])][eval(s[1], s[2])], tmp1[0]);
	eval(s1[eval(s[4], s[7])][eval(s[5], s[6])], tmp1[1]);

	char p4[4];
	p4[0] = tmp1[0][1];
	p4[1] = tmp1[1][1];
	p4[2] = tmp1[1][0];
	p4[3] = tmp1[0][0];

	/////////////////////////////////////////
	/ *char r1[4], l1[4];
	for (int i = 0; i < 4; i++)
	{
		r1[i] = xor (p4[i], b[i]);
		l1[i] = b[i + 4];
	}
	for (int i = 0; i < 4; i++)
	{
		out[i] = l1[i];
		out[i + 4] = r1[i];
	}* /
	for (int i = 0; i < 4; i++)
	{
		out[i] = p4[i];
		cout << out[i];
	}
	cout << endl;


}

void en(char in[], char out[])
{
	char k1[8] = { '1','0','1','0','0','0','1','1' };
	char k2[8] = { '0','0','1','1','1','1','1','0' };

	char b[8], c[8], d[8];
	int ip[8] = { 2,6,3,1,4,8,5,7 };
	for (int i = 0; i < 8; i++)
		b[i] = in[ip[i] - 1];

	f(b, c, k1);

	char r1[4], l1[4];
	char b1[8];
	for (int i = 0; i < 4; i++)
	{
		r1[i] = xor (c[i], b[i]);
		l1[i] = b[i + 4];
	}
	for (int i = 0; i < 4; i++)
	{
		b1[i] = l1[i];
		b1[i + 4] = r1[i];
	}
	/ *for (int i = 0; i < 4; i++)
		cout << l1[i];
	cout << "    ";
	for (int i = 0; i < 4; i++)
		cout << r1[i];
	cout << endl;* /
	f(b1, d, k2);


	//char r1[4], l1[4];
	char b2[8];
	for (int i = 0; i < 4; i++)
	{
		l1[i] = xor (d[i], b1[i]);
		r1[i] = b1[i + 4];
	}
	for (int i = 0; i < 4; i++)
	{
		b2[i] = l1[i];
		b2[i + 4] = r1[i];
	}
	/ *for (int i = 0; i < 4; i++)
		cout << l1[i];
	cout << "    ";
	for (int i = 0; i < 4; i++)
		cout << r1[i];
	cout << endl;* /
	int ip2[8] = { 4,1,3,5,7,2,8,6 };
	for (int i = 0; i < 8; i++)
		out[i] = b2[ip2[i] - 1];

}

void de(char in[], char out[])
{
	char k1[8] = { '1','0','1','0','0','0','1','1' };
	char k2[8] = { '0','0','1','1','1','1','1','0' };

	char b[8], c[8], d[8];
	int ip[8] = { 2,6,3,1,4,8,5,7 };
	for (int i = 0; i < 8; i++)
		b[i] = in[ip[i] - 1];

	f(b, c, k2);

	char r1[4], l1[4];
	char b1[8];
	for (int i = 0; i < 4; i++)
	{
		r1[i] = xor (c[i], b[i]);
		l1[i] = b[i + 4];
	}
	for (int i = 0; i < 4; i++)
	{
		b1[i] = l1[i];
		b1[i + 4] = r1[i];
	}
	/ *for (int i = 0; i < 4; i++)
		cout << l1[i];
	cout << "    ";
	for (int i = 0; i < 4; i++)
		cout << r1[i];
	cout << endl;* /


	f(b1, d, k1);


	//char r1[4], l1[4];
	char b2[8];
	for (int i = 0; i < 4; i++)
	{
		l1[i] = xor (d[i], b1[i]);
		r1[i] = b1[i + 4];
	}
	for (int i = 0; i < 4; i++)
	{
		b2[i] = l1[i];
		b2[i + 4] = r1[i];
	}
	/ *for (int i = 0; i < 4; i++)
		cout << l1[i];
	cout << "    ";
	for (int i = 0; i < 4; i++)
		cout << r1[i];
	cout << endl;* /

	int ip2[8] = { 4,1,3,5,7,2,8,6 };
	for (int i = 0; i < 8; i++)
		out[i] = b2[ip2[i] - 1];

}

*/
