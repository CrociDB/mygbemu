#include "debug.h"

debugger_t* debug_get(cpu_t* cpu)
{
    int i;
    for (i = 0; i < DEBUGGERS_MAX; i++)
    {
        if (debuggers[i].assigned)
        {
            if (debuggers[i].cpu == cpu)
                return &debuggers[i];
        }
        else
        {
            debuggers[i].assigned = true;
            debuggers[i].cpu = cpu;
            return &debuggers[i];
        }
    }

    return NULL;
}

void debug_instruction(cpu_t* cpu, mmu_t* mmu, const char* disasm, ...)
{
    debugger_t* debugger = debug_get(cpu);
    assert(debugger != NULL);

    uint16_t pc_addr = (cpu->reg.pc.word - 1);

    if (debugger->printall)
    {
        char buffer[0xFF];
        va_list argptr;
        va_start(argptr, disasm);
        vsprintf(buffer, disasm, argptr);
        log_cpu("0x%04X\t%s", pc_addr, buffer);
        va_end(argptr);
    }
}
