#include "cpu.h"

cpu_t* cpu_create()
{
    cpu_t* cpu = (cpu_t*)malloc(sizeof(cpu_t));
    return cpu;
}

void cpu_reset(cpu_t* cpu)
{
    memset((void*)(&cpu->reg), 0, sizeof(cpu->reg));
}
