#include <iostream>
#include "automatasimulator.hpp"

int main (int argc, char** argv) {
	AutomataSimulator a(argv[1]);
	a.process();
	return 0;
}
