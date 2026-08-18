#ifndef ALU_H
#define ALU_H

#include <stdbool.h>
#include "types.h"

typedef enum
{
    ALU_ADD,
    ALU_SUB,
    ALU_AND,
    ALU_NOT,
    ALU_OR,
    ALU_XOR
} ALUOperation;

typedef struct ALUResult
{
    word value;

    bool zero;
    bool negative;
    bool carry;
    bool overflow;
}ALUResult;

ALUResult alu_execute(word a, word b, ALUOperation operation);

#endif