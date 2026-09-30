#include <assert.h>
#include <stdio.h>

#include "decoder.h"
#include "isa.h"

int main(void)
{
    word word1;
    word word2;
    DecodedInstruction instruction;

    word1 = (OP_ADD << OPCODE_SHIFT)
          | (REG_R1 << REG1_SHIFT)
          | (REG_R2 << REG2_SHIFT);

    word2 = 0;

    instruction = decoder(word1, word2);

    assert(instruction.opcode == OP_ADD);
    assert(instruction.reg1 == REG_R1);
    assert(instruction.reg2 == REG_R2);
    assert(instruction.format == FORMAT_RR);
    assert(instruction.payload == 0);

    word1 = (OP_LDI << OPCODE_SHIFT)
          | (REG_R3 << REG1_SHIFT);

    word2 = 100;

    instruction = decoder(word1, word2);

    assert(instruction.opcode == OP_LDI);
    assert(instruction.reg1 == REG_R3);
    assert(instruction.format == FORMAT_RP);
    assert(instruction.payload == 100);

    word1 = (OP_JMP << OPCODE_SHIFT);
    word2 = 0x2000;

    instruction = decoder(word1, word2);

    assert(instruction.opcode == OP_JMP);
    assert(instruction.format == FORMAT_A);
    assert(instruction.payload == 0x2000);

    word1 = ((word)31 << OPCODE_SHIFT);
    word2 = 0;

    instruction = decoder(word1, word2);

    assert(instruction.format == FORMAT_INVALID);

    printf("All decoder tests passed.\n");

    return 0;
}