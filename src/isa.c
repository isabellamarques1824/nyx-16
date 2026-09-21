#include "isa.h"

InstructionFormat get_instruction_format(Opcode opcode){
    if(opcode == OP_ADD || opcode == OP_AND || opcode == OP_SUB
        || opcode == OP_CMP || opcode == OP_XOR || opcode == OP_MOV || opcode == OP_OR){
            return FORMAT_RR; 
    }  

    else if(opcode == OP_JMP || opcode == OP_JZ || opcode == OP_JNZ || opcode == OP_JN){
        return FORMAT_A;
    }

    else if(opcode == OP_LDI || opcode == OP_LOAD || opcode == OP_STORE){
        return FORMAT_RP;
    }

    else if(opcode == OP_NOT || opcode == OP_PUSH || opcode == OP_POP){
        return FORMAT_R;
    }

    else if(opcode == OP_NOP || opcode == OP_HALT){
        return FORMAT_NONE;
    }

    else {
        return FORMAT_INVALID;
    }
}