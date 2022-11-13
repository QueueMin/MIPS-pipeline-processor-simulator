#include <iostream>
#include "Simulator.cpp"


int main(void){
  std::string fileName;
	std::cin >> fileName;
	Simulator simulator(fileName);

	return 0;
}