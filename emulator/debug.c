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
            debuggers[i].breakpoints = NULL;
            return &debuggers[i];
        }
    }

    return NULL;
}

void debug_breakpoint_addr(cpu_t* cpu, uint16_t addr)
{
    debugger_t* debugger = debug_get(cpu);
    debug_breakpoint_t* bp = (debug_breakpoint_t*)malloc(sizeof(debug_breakpoint_t));
    bp->type = DEBUG_BREAKPOINT_ADDR;
    bp->addr = addr;
    bp->next = NULL;
    _debug_breakpoint(debugger, bp);
}

void debug_breakpoint_asm(cpu_t* cpu, const char* disasm)
{
    debugger_t* debugger = debug_get(cpu);
    debug_breakpoint_t* bp = (debug_breakpoint_t*)malloc(sizeof(debug_breakpoint_t));
    bp->type = DEBUG_BREAKPOINT_ASM;
    uint8_t size = strlen(disasm);
    bp->asmline = (char*)malloc(size);
    strcpy(bp->asmline, disasm);
    bp->next = NULL;
    _debug_breakpoint(debugger, bp);
}

void _debug_breakpoint(debugger_t* debugger, debug_breakpoint_t* breakpoint)
{
    if (debugger->breakpoints == NULL)
    {
        debugger->breakpoints = breakpoint;
        return;
    }

    debug_breakpoint_t* bp = debugger->breakpoints;
    while(bp->next != NULL) bp = bp->next;
    bp->next = breakpoint;
}

bool _debug_isbreak(debugger_t* debugger, uint16_t addr, char* asmline)
{
    debug_breakpoint_t* bp = debugger->breakpoints;
    while (bp != NULL)
    {
        if (bp->type == DEBUG_BREAKPOINT_ADDR)
        {
            if (bp->addr == addr) return true;
        }
        else
        {
            if (!strcmp(bp->asmline, asmline)) return true;
        }

        bp = bp->next;
    } 

    return false;
}

void debug_instruction(cpu_t* cpu, mmu_t* mmu, const char* disasm, ...)
{
    debugger_t* debugger = debug_get(cpu);
    assert(debugger != NULL);

    char buffer[0xFF];
    va_list argptr;
    va_start(argptr, disasm);
    vsprintf(buffer, disasm, argptr);

    uint16_t pc_addr = (cpu->reg.pc.word - 1);
    bool isbreak = _debug_isbreak(debugger, pc_addr, buffer);

    if (debugger->printall || isbreak)
    {
        log_cpu("0x%04X\t%s", pc_addr, buffer);
    }

    if (isbreak)
    {
        int a = 0; // ADD A FREAKING BREAKPOINT HERE
    }
    
    va_end(argptr);
}
