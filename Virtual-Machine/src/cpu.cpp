#include <iostream>
#include <fstream>
#include <bitset>
#include <limits>

#include "cpu.h"

CPU::CPU() :
	m_regs(std::vector<int32_t>(6)),
	m_counter(0),
	m_input(0),
	m_output(0)
{
}

void CPU::read(const char *fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) {
		throw std::ifstream::failure("Can't open input file, check the path.");
	}

	m_ram = std::vector<int8_t>(std::istreambuf_iterator<char>(file), {});

	file.close();
}

void CPU::process()
{
	while (m_counter + 3 < m_ram.size()) {
		int8_t opcode = m_ram[m_counter];
		int32_t arg1 = static_cast<int32_t>(m_ram[m_counter + 1]);
		int32_t arg2 = static_cast<int32_t>(m_ram[m_counter + 2]);
		int32_t tmp = static_cast<int32_t>(m_ram[m_counter + 3]);
		int32_t* dest = &tmp;

		// using std::bitset for easy bit access by [] operator
		// for immidiate(6,7) and condition(5) bits checking
		std::bitset<8> opcodeBits(opcode);

		// handle if argument 1 is a memory address
		if (opcodeBits[7] == 0) {
			if (arg1 >= 0 && arg1 <= 5) {
				arg1 = m_regs[arg1];
			} else if (arg1 == 7) {
				arg1 = m_input;
			} else {
				throw std::runtime_error("Input File : invalid argument format");
			}
		}

		// handle if argument 2 is a memory address
		if (opcodeBits[6] == 0) {
			if (arg2 >= 0 && arg2 <= 5) {
				arg2 = m_regs[arg2];
			} else if (arg2 == 7) {
				arg2 = m_input;
			} else {
				throw std::runtime_error("Input File : invalid argument format");
			}
		}

		// handle if destination is a memory address
		if (opcodeBits[5] == 0) {
			if (*dest >= 0 && *dest <= 5) {
				dest = &m_regs[*dest];
			} else if (*dest == 7) {
				dest = &m_output;
			} else {
				throw std::runtime_error("Input File : invalid destination format");
			}
		}

		// opcode & 63 to ignore 7_th, 8_th bits
		bool condition = false;
		switch (opcode & 63) {
		case ADD:
			*dest = arg1 + arg2;
			break;
		case SUB:
			*dest = arg1 - arg2;
			break;
		case AND:
			*dest = arg1 & arg2;
			break;
		case OR:
			*dest = arg1 | arg2;
			break;
		case NOT:
			*dest = ~arg1;
			break;
		case XOR:
			*dest = arg1 ^ arg2;
			break;
		case EQ:
			condition = arg1 == arg2;
			break;
		case NEQ:
			condition = arg1 != arg2;
			break;
		case L:
			condition = arg1 < arg2;
			break;
		case LE:
			condition = arg1 <= arg2;
			break;
		case G:
			condition = arg1 > arg2;
			break;
		case GE:
			condition = arg1 >= arg2;
			break;
		default:
			throw std::runtime_error("Input File : invalid opcode format");
			break;
		}

		if (condition) {
			if (*dest >= 0 && *dest <= std::numeric_limits<uint32_t>::max()) {
				m_counter = *dest;
			} else {
				throw std::overflow_error("Segmentation fault");
			}
		} else {
			if (m_counter + 4 <= std::numeric_limits<uint32_t>::max()) {
				m_counter += 4;
			} else {
				throw std::overflow_error("Segmentation fault");
			}
		}
	}
}
