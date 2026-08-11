#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

typedef uint16_t word;

typedef struct registers
{
    word gpr[8];

    word pc;
    word ir; 
}registers;


#endif