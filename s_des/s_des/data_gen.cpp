#include <iostream>
#include <fstream>
#include "top.h"
using namespace std;
int main()
{
	/*char a[65];
	ifstream fin("key_seed.txt");
	ofstream foutK1("key1.txt");
	ofstream foutK2("key2.txt");
	for (int i = 0; i < 7840; i++)
	{
		fin >> a;
		for (int j = 52; j < 64; j++)
			foutK2 << a[j];
		foutK2 << endl;
		for (int j = 40; j < 52; j++)
			foutK1 << a[j];
		foutK1 << endl;
	}
	fin.close();
	foutK1.close();
	foutK2.close();*/

	char dIn[17] = { 0 };
	char dOut[17] = { 0 };
	char key1[13] = { 0 };
	char key2[13] = { 0 };


	ifstream finLoc("loc.txt");
	ifstream finK1("key1.txt");
	ifstream finK2("key2.txt");
	ofstream foutCipherLoc("c_loc.txt");
	ofstream foutValid("valid_loc.txt");

	for (int i = 0; i < 7840; i++)
	{
		finLoc >> dIn;
		finK1 >> key1;
		finK2 >> key2;
		//cout << key1 << " " << key2 << endl;
		en(dIn, dOut, key2, key1);
		foutCipherLoc << dOut << endl;

		char tmp[17] = { 0 };
		en(dOut, tmp, key1, key2);
		foutValid << tmp << endl;
	}

	/*en("0000000000000000", dOut, "000000000000", "000000000000");
	cout << dOut;
	system("pause");*/

}