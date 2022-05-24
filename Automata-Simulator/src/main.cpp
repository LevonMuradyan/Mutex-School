#include <iostream>
#include "automatasimulator.hpp"

int main (int argc, char** argv) {
	if (argc > 1) {
		AutomataSimulator a(argv[1]);
		a.run();
	} else {
		std::cout << "Input file argument missing" << std::endl;
	}
	return 0;
}
