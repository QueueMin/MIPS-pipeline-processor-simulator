#include <iostream>
#include <fstream>
#include "translate.cpp"
using namespace std;

int main(void){
	string op = "add";
	int rs = 1,rt = 2,rd = 3;
	string str = encode(op,rs,rt,rd);
	cout << str << '\n';
	int x = BintoDec(str);
	cout << x << '\n';
	cout << DectoHex(x) << '\n';
	return 0;
}
