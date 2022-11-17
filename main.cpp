#include <iostream>
#include "Simulator.cpp"

int main(void)
{
	std::string fileName = "test.s";
	Simulator simulator;
	simulator.fileLoad(fileName);
	simulator.run();
	return 0;
}