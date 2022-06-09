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
//		std::cout << b1 << std::endl;
	}
}

void CPU::process()
{
	while (m_counter + 3 < m_ram.size()) {
		std::bitset<8> opcode(m_ram[m_counter]);
		std::bitset<8> arg1(m_ram[m_counter + 1]);
		std::bitset<8> arg2(m_ram[m_counter + 2]);
		std::bitset<8> dest(m_ram[m_counter + 3]);

		int8_t opcodeValue = (int8_t)(opcode.to_ulong());

		int8_t value1 = (int8_t)(arg1.to_ulong());
		if (opcode[7] == 0) {
			if (value1 >= 0 && value1 <= 5) {
				value1 = m_regs[value1];
			} else if (value1 == 7) {
				value1 = m_input;
			} else {
				std::cout << "invalid argument" << std::endl;
			}
		}

		int8_t value2 = (int8_t)(arg2.to_ulong());
		if (opcode[6] == 0) {
			if (value2 >= 0 && value2 <= 5) {
				value2 = m_regs[value2];
			} else if (value2 == 7) {
				value2 = m_input;
			} else {
				std::cout << "invalid argument" << std::endl;
			}
		}

		int32_t a = (int8_t)(dest.to_ulong());
		int32_t* destValue = &a;
		if (opcode[5] == 0) {
			if (*destValue >= 0 && *destValue <= 5) {
				destValue = &m_regs[*destValue];
			} else if (*destValue == 7) {
				destValue = &m_output;
			} else {
				std::cout << "invalid destination" << std::endl;
			}
		}

		switch (opcodeValue & 63) {
		case ADD:
			*destValue = value1 + value2;
            m_counter += 4;
			break;
		case SUB:
			*destValue = value1 - value2;
            m_counter += 4;
			break;
		case AND:
			*destValue = value1 & value2;
            m_counter += 4;
			break;
		case OR:
			*destValue = value1 | value2;
            m_counter += 4;
			break;
		case NOT:
			*destValue = ~value1;
            m_counter += 4;
			break;
		case XOR:
			*destValue = value1 ^ value2;
            m_counter += 4;
			break;
		case EQ:
			m_counter = (value1 == value2 ? *destValue : m_counter + 4);
			break;
		case NEQ:
			m_counter = (value1 != value2 ? *destValue : m_counter + 4);
			break;
		case L:
			m_counter = (value1 < value2 ? *destValue : m_counter + 4);
			break;
		case LE:
			m_counter = (value1 <= value2 ? *destValue : m_counter + 4);
			break;
		case G:
			m_counter = (value1 > value2 ? *destValue : m_counter + 4);
			break;
		case GE:
			m_counter = (value1 >= value2 ? *destValue : m_counter + 4);
			break;
		}
	}

    std::cout << "output = " << m_output << std::endl;
}
