#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

#include "cpu.h"

CPU::CPU() : m_counter(0), m_input(0), m_output(0)
{
	m_regs = std::vector<int32_t>(6);
}

void CPU::read(char *fileName)
{
    std::ifstream input(fileName, std::ios::binary);
	m_ram = std::vector<int8_t>(std::istreambuf_iterator<char>(input), {});

	for (size_t i = 0; i < m_ram.size(); ++i) {
		std::bitset<8> b1(m_ram[i]);
		std::cout << b1 << std::endl;
	}
}

void CPU::process()
{
	while (m_regs[COUNTER] + 3 < (int8_t)m_ram.size()) {
		int8_t opcode = +m_ram[m_regs[COUNTER]];
		int8_t arg1 = +m_ram[m_regs[COUNTER] + 1];
		int8_t arg2 = +m_ram[m_regs[COUNTER] + 2];
		int8_t dest = +m_ram[m_regs[COUNTER] + 3];

		int8_t value1 = opcode != (opcode & (~(1 << 7))) ? arg1 : m_regs[arg1];

		bool cond = false;

		switch (opcode) {
		case EQ:
			cond = m_regs[arg1] == m_regs[arg2];
			break;
		case NEQ:
			cond = m_regs[arg1] != m_regs[arg2];
			break;
		case L:
			cond = m_regs[arg1] < m_regs[arg2];
			break;
		case LE:
			cond = m_regs[arg1] <= m_regs[arg2];
			break;
		case G:
			cond = m_regs[arg1] > m_regs[arg2];
			break;
		case GE:
			cond = m_regs[arg1] >= m_regs[arg2];
			break;
		}

		if (opcode != (opcode & (~(1 << 5))) && cond) {
			m_regs[COUNTER] = (uint8_t)dest;
		} else {
			m_regs[COUNTER] += 4;
		}

	}

}
