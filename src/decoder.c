#include "decoder.h"
#include "isa.h"
#include <stdio.h>

DecodedInstruction decoder(word word1, word word2){
    DecodedInstruction instruction;

    instruction.opcode = (word1 & OPCODE_MASK) >> OPCODE_SHIFT; 
    instruction.reg1 = (word1 & REG1_MASK) >> REG1_SHIFT;
    instruction.reg2 = (word1 & REG2_MASK) >> REG2_SHIFT;
    instruction.payload = word2;
    instruction.format = get_instruction_format(instruction.opcode);

    return instruction;

}