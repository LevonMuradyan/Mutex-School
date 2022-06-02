#include <iostream>
#include <fstream>
#include <vector>

#include "cpu.h"

CPU::CPU() : m_inReg(0), m_outReg(0), m_reg0(0), m_reg1(0),
    m_reg2(0), m_reg3(0), m_reg4(0), m_reg5(0), isCondition(false),
    m_counter(0)
{

}

void CPU::read(char *fileName)
{
    std::ifstream input(fileName, std::ios::binary);
    m_ram = std::vector<int8_t>(std::istreambuf_iterator<char>(input), {});

    for (auto& e: m_ram) {
        std::cout << +e << std::endl;
    }
}

void CPU::process()
{

}
