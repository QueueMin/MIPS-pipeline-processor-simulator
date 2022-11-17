#ifndef OPERATIONS_INCLUDED
#define OPERATIONS_INCLUDED
#include <bitset>
#include "Translate.cpp"

template <size_t T>
std::bitset<T> addOperation(std::bitset<T> data1, std::bitset<T> data2)
{
	unsigned int i1 = binToDec(data1);
	unsigned int i2 = binToDec(data2);
	std::bitset<T> tmp = i1 + i2;
	return tmp;
}

template <size_t T>
std::bitset<T> subOperation(std::bitset<T> data1, std::bitset<T> data2)
{
	unsigned int i1 = binToDec(data1);
	unsigned int i2 = binToDec(data2);
	std::bitset<T> tmp = i1 - i2;
	return tmp;
}

template <size_t T>
std::bitset<T> orOperation(std::bitset<T> data1, std::bitset<T> data2)
{
	std::bitset<T> tmp = data1 | data2;
	return tmp;
}

template <size_t T>
std::bitset<T> andOperation(std::bitset<T> data1, std::bitset<T> data2)
{
	std::bitset<T> tmp = data1 & data2;
	return tmp;
}

template <size_t T>
std::bitset<T> sltOperation(std::bitset<T> data1, std::bitset<T> data2)
{
	std::bitset<T> tmp;
	if(data1 < data2) tmp = 1;
	else tmp = 0;
	return tmp;
}
#endif