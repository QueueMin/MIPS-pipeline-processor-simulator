#include <iostream>
#include "Simulator.cpp"

int main(void)
{
	std::string fileName = "t.s";
	Simulator simulator;
	simulator.fileLoad(fileName);
	simulator.run();
	return 0;
}