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

typedef enum
{
    FLAG_ZERO = 1u << 0,
    FLAG_NEGATIVE = 1u << 1,
    FLAG_CARRY = 1u << 2,
    FLAG_OVERFLOW = 1u << 3
} Flag;

void init_registers(Registers *regs);
word read_register(Registers *regs, unsigned int index);
void write_register(Registers *regs, unsigned int index, word value);
void advance_pc(Registers *regs);
void load_pc(Registers *regs, word new_pc);
void load_ir(Registers *regs, word new_ir);
void set_flag(Registers *regs, Flag flag, bool value);
bool read_flag(const Registers *regs, Flag flag);

#endif