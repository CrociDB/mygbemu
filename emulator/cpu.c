#include "cpu.h"

cpu_t* cpu_create()
{
    cpu_t* cpu = (cpu_t*)malloc(sizeof(cpu_t));
    return cpu;
}

void cpu_reset(cpu_t* cpu)
{
    cpu->af = 0x0000;
    cpu->bc = 0x0000;
    cpu->de = 0x0000;
    cpu->hl = 0x0000;
    cpu->sp = 0x0000;
    cpu->pc = 0x0000;
}
