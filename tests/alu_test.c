#include <assert.h>
#include <stdio.h>
#include "alu.h"

void test_add(void)
{
    ALUResult result;

    result = alu_execute(5, 3, ALU_ADD);
    assert(result.value == 8);
    assert(result.zero == false);
    assert(result.negative == false);
    assert(result.carry == false);
    assert(result.overflow == false);

    result = alu_execute(0xFFFF, 1, ALU_ADD);
    assert(result.value == 0x0000);
    assert(result.zero == true);
    assert(result.negative == false);
    assert(result.carry == true);
    assert(result.overflow == false);

    result = alu_execute(0x7FFF, 1, ALU_ADD);
    assert(result.value == 0x8000);
    assert(result.zero == false);
    assert(result.negative == true);
    assert(result.carry == false);
    assert(result.overflow == true);
}

void test_sub(void)
{
    ALUResult result;

    result = alu_execute(5, 3, ALU_SUB);
    assert(result.value == 2);
    assert(result.zero == false);
    assert(result.negative == false);
    assert(result.carry == true);
    assert(result.overflow == false);

    result = alu_execute(3, 5, ALU_SUB);
    assert(result.value == 0xFFFE);
    assert(result.zero == false);
    assert(result.negative == true);
    assert(result.carry == false);
    assert(result.overflow == false);

    result = alu_execute(0x7FFF, 0xFFFF, ALU_SUB);
    assert(result.value == 0x8000);
    assert(result.zero == false);
    assert(result.negative == true);
    assert(result.overflow == true);
}

void test_logic(void)
{
    ALUResult result;

    result = alu_execute(0xF0F0, 0x0FF0, ALU_AND);
    assert(result.value == 0x00F0);
    assert(result.zero == false);
    assert(result.negative == false);

    result = alu_execute(0xF000, 0x0F00, ALU_OR);
    assert(result.value == 0xFF00);
    assert(result.negative == true);

    result = alu_execute(0xFFFF, 0xFFFF, ALU_XOR);
    assert(result.value == 0x0000);
    assert(result.zero == true);

    result = alu_execute(0x0000, 0, ALU_NOT);
    assert(result.value == 0xFFFF);
    assert(result.zero == false);
    assert(result.negative == true);
}

int main(void)
{
    test_add();
    test_sub();
    test_logic();

    printf("All ALU tests passed.\n");

    return 0;
}