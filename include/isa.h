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

typedef enum
{
    NOP = 0,
    HALT = 1,
    MOV = 2,
    LDI = 3,
    LOAD = 4,
    STORE = 5,
    ADD = 6,
    SUB = 7,
    AND = 8,
    OR = 9,
    XOR = 10,
    NOT = 11,
    CMP = 12,
    JMP = 13,
    JZ = 14,
    JNZ = 15,
    JN = 16,
    PUSH = 17,
    POP = 18
} Opcode;

#endif