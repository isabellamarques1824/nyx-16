#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#define GPR_COUNT 8

typedef uint16_t word;

typedef struct registers
{
    word gpr[8];

    word pc;
    word ir; 
    word sp;

    word sr;

}Registers;

void init_registers(Registers *regs);
word read_register(Registers *regs, unsigned int index);


#endif