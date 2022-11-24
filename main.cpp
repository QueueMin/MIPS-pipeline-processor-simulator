#include <iostream>
#include "Simulator.cpp"

int main(void)
{
	std::string fileName = "test inf.s";
	Simulator simulator;
	simulator.fileLoad(fileName);
	simulator.runSingleCycle();
	simulator.runSingleCycle();
	simulator.runSingleCycle();
	simulator.runSingleCycle();
	simulator.runSingleCycle();
	simulator.runSingleCycle();
	simulator.runSingleCycle();
	return 0;
}