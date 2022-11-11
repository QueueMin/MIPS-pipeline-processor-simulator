#ifndef OPERATIONS_INCLUDED
#define OPERATIONS_INCLUDED
#include <bitset>
// 개발 속도를 위해 10진수로 변환 후 c++의 기본 지원 bitwise 연산 사용을 제안함.
// 변환 연산자를 잘 만들어놓기도 했으므로...
// 스트링으로 주어진 2진수들의 덧셈. 이후 16진수로 반환하려고 함.

template <size_t T>
std::bitset<T> addOperation(std::bitset<T> data1, std::bitset<T> data2)
{
	unsigned int i1 = binToDec(data1);
	unsigned int i2 = binToDec(data2);

	return decToHex(i1 | i2);
}

// 스트링으로 주어진 2진수들의 덧셈.
template <size_t T>
std::bitset<T> orOperation(std::string data1, std::string data2)
{
	// 미완성
	std::string ans = "";
	for (int i = 0; i < data1.length(); i++)
	{
		if (data1[i] == 1 || data2[i] == 1)
			ans = "1" + ans;
		else
			ans = "0" + ans;
	}
}
#endif