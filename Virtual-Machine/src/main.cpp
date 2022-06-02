#include <iostream>
#include "cpu.h"

int main (int argc, char** argv) {
	if (argc > 1) {
        CPU cpu;
        cpu.read(argv[1]);
        cpu.process();
	} else {
		std::cout << "Input file argument missing" << std::endl;
	}
	return 0;
}
