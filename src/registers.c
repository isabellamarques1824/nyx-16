#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "types.h"
#include "registers.h"

void init_registers(Registers *regs)
{
    assert(regs != NULL);

    for(int i = 0; i < GPR_COUNT; i++){
        regs->gpr[i] = 0;
    }

    regs->pc = 0;
    regs->ir = 0;
    regs->sp = 0;
    regs->sr = 0;
}

word read_register(const Registers *regs, unsigned int index)
{
    assert(regs != NULL);
    assert(index < GPR_COUNT);

    return regs->gpr[index];
}

void write_register(Registers *regs, unsigned int index, word value)
{
    assert(regs != NULL);
    assert(index < GPR_COUNT);

    regs->gpr[index] = value;
}

void advance_pc(Registers *regs)
{
    assert(regs != NULL);

    regs->pc++;
}

void load_pc(Registers *regs, word new_pc)
{
    assert(regs != NULL);

    regs->pc = new_pc;
}

void load_ir(Registers *regs, word new_ir)
{
    assert(regs != NULL);

    regs->ir = new_ir;
}

void set_flag(Registers *regs, Flag flag, bool value)
{
    assert(regs != NULL);

    if(value){
        regs->sr = regs->sr | flag;
    }else{
        regs->sr = regs->sr & ~flag;
    } 
}

bool read_flag(const Registers *regs, Flag flag)
{

    assert(regs != NULL);
    return (regs->sr & flag) != 0;
}

// o comportamento do registrador sp vai ser definido depois de implementar stack