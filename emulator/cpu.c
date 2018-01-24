#include "cpu.h"

cpu_t* cpu_create()
{
    log_message("Creating CPU");

    cpu_t* cpu = (cpu_t*)malloc(sizeof(cpu_t));
    return cpu;
}

void cpu_reset(cpu_t* cpu)
{
    memset((void*)(&cpu->reg), 0, sizeof(cpu->reg));
}

// OPs implementation

void cpu_op_nop(cpu_t * cpu)
{
    cpu->clock.m = 1;
    cpu->clock.t = 4;
    cpu->reg.pc.word++;
}

