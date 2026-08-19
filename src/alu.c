#include <stdint.h>
#include <assert.h>
#include "alu.h"

ALUResult alu_execute(word a, word b, ALUOperation operation)
{

    ALUResult result = {.value = 0 , .zero = 0, .negative = 0, .overflow = 0, .carry = 0};

    switch (operation)
    {
    case ALU_ADD: 
    {
        uint32_t wide = (uint32_t)a + (uint32_t)b;

        result.value = (word)wide;
        result.carry = (wide >> 16) & 1;
        result.overflow = ((a ^ result.value) & (b ^ result.value) & 0x8000) != 0;

        break;
    }

    case ALU_SUB: 
    {
        uint32_t wide = (uint32_t)a + (uint32_t)(word)(~b) + 1;
        
        result.value = (word)wide;
        result.carry = (wide >> 16) & 1;
        result.overflow = ((a ^ b) & (a ^ result.value) & 0x8000) != 0;
        break;
    }

    case ALU_AND:
        result.value = a & b;
        break;

    case ALU_NOT:
        result.value = ~a;
        break;

    case ALU_OR:
        result.value = a | b;
        break;

    case ALU_XOR:
        result.value = a ^ b;
        break;

    default:
        assert(!"Invalid ALU operation");
    }

    result.negative = (result.value & 0x8000) != 0;
    result.zero = (result.value == 0);

    return result;
}