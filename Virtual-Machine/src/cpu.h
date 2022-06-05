#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <vector>

#define REG0 0
#define REG1 1
#define REG2 2
#define REG3 3
#define REG4 4
#define REG5 5
#define COUNTER 6
#define INPUT 7
#define OUTPUT 8

#define ADD 0
#define SUB 1
#define AND 2
#define OR 3
#define NOT 4
#define XOR 5

#define EQ 32
#define NEQ 33
#define L 34
#define LE 35
#define G 36
#define GE 37

class CPU
{
public:
    CPU();
    void read(char* fileName);
    void process();

private:
    // registers
	std::vector<int32_t> m_regs;
	uint32_t m_counter;
	int32_t m_input;
	int32_t m_output;

    // ram buffer
	std::vector<int8_t> m_ram;
};

#endif // CPU_H
