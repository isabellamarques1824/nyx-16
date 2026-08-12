#include <stdlib.h>
#include <assert.h>
#include "registers.h"

void init_registers(Registers *regs){

    if(regs == NULL){
        return;
    }

    for(int i = 0; i < GPR_COUNT; i++){
        regs->gpr[i] = 0;
    }

    regs->pc = 0;
    regs->ir = 0;
    regs->sp = 0;
    regs->sr = 0;
}

word read_register(Registers *regs, unsigned int index){
    assert(regs != NULL);
    assert(index < GPR_COUNT);

    return regs->gpr[index];
}