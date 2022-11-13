#ifndef TRANSLATES_INCLUDED
#define TRANSLATES_INCLUDED
#include <bitset>
#include "Elements.cpp"

// operation과 rs, rt, rd 레지스터의 번호를 전달받아 32자리 2진수로 반환
std::bitset<32> encode(std::string operation, std::bitset<5> rs, std::bitset<5> rt, std::bitset<5> rd)
{
	std::bitset<32> oper;
	oper.reset();
	std::bitset<5> shamt;
	shamt.reset();
	// 컴파일러의 반환값을 확인하고 구현
	// if(operation == "add"){
	// 	shamt = 0;
	// 	oper = decToBin(6,OP_ADD) + decToBin(5,rs) + decToBin(5,rt)
	// 	+ decToBin(5,rd) + decToBin(5,shamt) + decToBin(6,FUNCT_ADD);
	// }
	return oper;
} // 컴파일파일 제작 후 이동 예정

// 10진수 Dec를 8자리의 16진수로 바꾼 후 앞에 0x를 붙여 string으로 반환
std::string decToHex(int Dec)
{
	std::string Hex = "";
	std::string str[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
	while (Dec != 0)
	{
		Hex = str[Dec % 16] + Hex;
		Dec /= 16;
	}
	while (Hex.length() < 8)
	{
		Hex = "0" + Hex;
	}

	Hex = "0x" + Hex;
	return Hex;
}

// 10진수 Dec를 len길이만큼의 2진수로 변환하여 string으로 반환
// bitset 함수에 존재 ex) bitset<5> b(6); = 00110
// std::bitset decToBin(int len, int Dec)
// {
// 	std::bitset<5> Bin;Bin.reset();
// 	while(Dec != 0){
// 		if(Dec%2 == 1) Bin = "1"+Bin;
// 		else Bin = "0"+Bin;
// 		Dec/=2;
// 	}
// 	return Bin;
// }

// 2진수 Bin을 10진수로 변환하여 int로 반환
template <size_t T>
int binToDec(std::bitset<T> Bin)
{
	int Dec = 0;
	for (int i = 0; i < Bin.size(); i++)
	{
		Dec *= 2;
		if (Bin[i] == '1')
			Dec += 1;
	}

	return Dec;
}

// 2진수를 16진수로 반환. 0xXXXXXXXX의 문자열 형태
template <size_t T>
std::string binToHex(std::bitset<T> Bin)
{
	int Dec = binToDec(Bin);
	return decToHex(Dec);
}

// 0xXXXXXXXX형태의 문자열로 받은 16진수를 10진수로 변환하여 반환.
int hexToDec(std::string Hex)
{
	char str[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int Dec = 0;
	for (int i = 2; i < Hex.length(); i++)
	{
		Dec *= 16;
		for (int j = 0; j < 16; j++)
		{
			if (str[j] == Hex[i])
			{
				Dec += j;
				break;
			}
		}
	}
	return Dec;
}

// 16진수를 32자리의 2진수로 변환하여 반환.
std::bitset<32> hexToBin(std::string Hex)
{
	int Dec = hexToDec(Hex);
	std::bitset<32> tmp = Dec;
	return tmp;
}

// bitset[0]이 부호인것을 감안해 이진수 Bin을 16자리만큼 sign extend하여 반환.
std::bitset<32> signExtention(std::bitset<16> Bin)
{
	std::bitset<32> tmp;
	for (int i = 0; i < 16; i++)
		tmp[16 + i] = Bin[i];
	std::bitset<32> ans;
	if (Bin[0] == 0)
	{
		ans.reset();
	}
	else
	{
		ans.set();
	}
	return tmp | ans;
}
#endif
