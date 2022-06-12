#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <vector>

class CPU
{
private:
	enum OPCODE {
		ADD = 0,
		SUB = 1,
		AND = 2,
		OR  = 3,
		NOT = 4,
		XOR = 5,
		EQ  = 32,
		NEQ = 33,
		L   = 34,
		LE  = 35,
		G   = 36,
		GE  = 37,
	};
public:
    CPU();
	void read(const char* fileName);
    void process();
	// just to see the results
	int32_t getOutput() { return m_output; };

private:
	// using int32_t to store big numbers
    // registers
	std::vector<int32_t> m_regs;
	uint32_t m_counter;
	int32_t m_input;
	int32_t m_output;

    // ram buffer
	std::vector<int8_t> m_ram;
};

#endif // CPU_H
