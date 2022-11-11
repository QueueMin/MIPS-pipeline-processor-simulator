#include <iostream>
#include <fstream>
#include <bitset>
#include "control.cpp"
#include "translate.cpp"
#include "simulator.cpp"
using namespace std;


int main(void){
	Simulator reg();
	ControlUnit constolSignal;

	IF_ID IFID;
	ID_EX IDEX;
	EX_MEM EXMEM;
	MEM_WB MEMWB;

	string op = "add";
	bitset<5> rs = 1;
	bitset<5> rt = 2;
	bitset<5> rd = 3;
	bitset<32> str = encode(op,rs,rt,rd);
	cout << str << '\n';
	int x = binToDec(str);
	cout << x << '\n';
	string h = decToHex(x);
	cout << h << '\n';
	cout << hexToBin(h) << endl;


	// cout << addOperation("01111111111111111111111110101010", "1010101") << "\n";


	// int cnt=0;
	// while(cnt<5){
	// 	if(file.eof() == false) cnt = 0;
	// 	cnt++;
	// }

	return 0;
}