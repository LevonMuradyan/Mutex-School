#include <iostream>
#include <fstream>
#include "cpu.h"

void testFibonacci() {
	CPU cpu;
	try {
		cpu.read("../inputs/fib");
		cpu.process();
	}  catch (std::ifstream::failure& e) {
		std::cout << e.what() << std::endl;
		std::cout << "If you want to test Fibonacci number calculation," \
					 " please go to the \'bin\' directory and execute from there" << std::endl;
		return;
	}

	std::cout << "-----------------Testing Fibonacci number calculation--------------" << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cout << "Fibonacci " + std::to_string(46) + "_th number = " << cpu.getOutput() << std::endl;
	std::cout << "if you want to calculate other Fibonacci number, you have to change the 3_rd byte " \
				 "of the input file fib, maximum calculated number is 46_th Fibonacci number" << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
}

int main (int argc, char** argv) {
	if (argc > 1) {
		CPU cpu;
		cpu.read(argv[1]);
		cpu.process();
	} else {
		std::cout << "Input file argument is missing, using test file" << std::endl << std::endl;;
		testFibonacci();
	}
	return 0;
}
