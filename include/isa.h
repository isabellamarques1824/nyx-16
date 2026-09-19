#ifndef ISA_H
#define ISA_H

typedef enum{
    REG_R0 = 0,
    REG_R1 = 1,
    REG_R2 = 2, 
    REG_R3 = 3,
    REG_R4 = 4,
    REG_R5 = 5,
    REG_R6 = 6, 
    REG_R7 = 7

}RegisterCode;

typedef enum {
    OP_NOP = 0,
    OP_HALT = 1,
    OP_MOV = 2,
    OP_LDI = 3,
    OP_LOAD = 4,
    OP_STORE = 5,
    OP_ADD = 6,
    OP_SUB = 7, 
    OP_AND = 8,
    OP_OR = 9,
    OP_XOR = 10,
    OP_NOT = 11,
    OP_CMP = 12,
    OP_JMP = 13,
    OP_JZ = 14,
    OP_JNZ = 15,
    OP_JN = 16,
    OP_PUSH = 17,
    OP_POP = 18
} Opcode;

typedef enum {
    FORMAT_NONE,
    FORMAT_R,
    FORMAT_RR,
    FORMAT_RP,
    FORMAT_A
} InstructionFormat;

#define INSTRUCTION_WORDS 2

#define OPCODE_SHIFT 11
#define REG1_SHIFT 8
#define REG2_SHIFT 5

#define OPCODE_MASK 0xF800
#define REG1_MASK   0x0700
#define REG2_MASK   0x00E0

#endif