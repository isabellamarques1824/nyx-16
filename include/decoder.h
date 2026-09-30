#ifndef DECODER_H 
#define DECODER_H

#include "isa.h"

typedef struct {
    Opcode opcode;
    InstructionFormat format;
    RegisterCode reg1;
    RegisterCode reg2;
    word payload;
} DecodedInstruction;

DecodedInstruction decoder(word word1, word word2);

#endif