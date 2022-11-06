#include "elements.cpp"

std::string encode(std::string operation, int rs, int rt, int rd);
void decode(int oper);
std::string decToHex(int Dec);
std::string decToBin(int len, int Dec);
int binToDec();
std::string binToHex(std::string Bin);
int hexToDec(std::string Hex);
std::string hexToBin(std::string Hex);

// operation과 rs, rt, rd 레지스터의 번호를 전달받아 32자리 2진수로 반환
std::string encode(std::string operation, int rs, int rt, int rd)
{

	std::string oper = "";
	int shamt = 0;
	if(operation == "add"){
		shamt = 0;
		oper = decToBin(6,OP_ADD) + decToBin(5,rs) + decToBin(5,rt)
		+ decToBin(5,rd) + decToBin(5,shamt) + decToBin(6,FUNCT_ADD);
	}
	return oper;
}

void decode(int oper)
{

}


// 10진수 Dec를 8자리의 16진수로 바꾼 후 앞에 0x를 붙여 string으로 반환
std::string decToHex(int Dec) 
{
	std::string Hex = "";
	std::string str[16] = {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};
	while(Dec != 0){
		Hex = str[Dec%16] + Hex;
		Dec/=16;
	}
	while(Hex.length() < 8){
		Hex = "0"+Hex;
	}

	Hex = "0x" + Hex;
	return Hex;
}

// 10진수 Dec를 len길이만큼의 2진수로 변환하여 string으로 반환
std::string decToBin(int len, int Dec) 
{
	std::string Bin = "";
	while(Dec != 0){
		if(Dec%2 == 1) Bin = "1"+Bin;
		else Bin = "0"+Bin;
		Dec/=2;
	}
	while(Bin.length() < len){
		Bin = "0"+Bin;
	}
	return Bin;
}

// 2진수 Bin을 10진수로 변환하여 int로 반환
int binToDec(std::string Bin)
{
	int Dec = 0;
	for(int i = 0;i<Bin.length();i++){
		Dec*=2;
		if(Bin[i] == '1') Dec+=1;
	}

	return Dec;
}

// 2진수를 16진수로 반환. 0xXXXXXXXX의 문자열 형태
std::string binToHex(std::string Bin){
	int Dec = binToDec(Bin);
	return decToHex(Dec);
}


// 0xXXXXXXXX형태의 문자열로 받은 16진수를 10진수로 변환하여 반환.
int hexToDec(std::string Hex){
	char str[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	int Dec = 0;
	for(int i = 2;i<Hex.length();i++){
		Dec *=16;
		for(int j = 0;j<16;j++){
			if(str[j] == Hex[i]){
				Dec += j;
				break;
			}
		}
	}
	return Dec;
}

// 16진수를 32자리의 2진수로 변환하여 반환.
std::string hexToBin(std::string Hex){
	int Dec = hexToDec(Hex);
	return decToBin(32,Dec);
}


// 개발 속도를 위해 10진수로 변환 후 c++의 기본 지원 bitwise 연산 사용을 제안함.
// 변환 연산자를 잘 만들어놓기도 했으므로...
// 스트링으로 주어진 2진수들의 덧셈. 이후 16진수로 반환하려고 함.
std::string addOperation(std::string data1, std::string data2){
	unsigned int i1 = binToDec(data1);
	unsigned int i2 = binToDec(data2);
	
	return decToHex(i1|i2);
}

// 스트링으로 주어진 2진수들의 덧셈.
std::string orOperation(std::string data1,std::string data2){
	// 미완성
	std::string ans = "";
	for(int i = 0;i<data1.length();i++){
		if(data1[i] == 1 || data2[i] == 1) ans = "1"+ans;
		else ans = "0"+ans;
	}
}