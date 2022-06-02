#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <vector>

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
    int32_t m_inReg;
    int32_t m_outReg;
    int32_t m_reg0;
    int32_t m_reg1;
    int32_t m_reg2;
    int32_t m_reg3;
    int32_t m_reg4;
    int32_t m_reg5;

    bool isCondition;
    uint32_t m_counter;

    // ram buffer
    std::vector<int8_t> m_ram;
};

#endif // CPU_H
