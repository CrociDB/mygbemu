#include "debug.h"
#include "sys.h"

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

void debugger_init_loop(debugger_t* debugger, mmu_t* mmu, ppu_t* ppu)
{
    debugger->mmu = mmu;
    debugger->ppu = ppu;
    debugger->running = true;

    debugger->thread = SDL_CreateThread(debug_thread_loop, "debugger_thread", (void*)debugger);
}

void debugger_end_loop(debugger_t* debugger)
{
    debugger->running = false;
    int status;
    SDL_WaitThread(debugger->thread, &status);
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
    uint8_t size = (uint8_t)strlen(disasm);
    bp->asmline = (char*)malloc(size);
    strcpy_s(bp->asmline, size, disasm);
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

int debug_thread_loop(void* data)
{
    debugger_t* debugger = (debugger_t*)data;

    while (debugger->running)
    {
        if (debugger->debug)
        {
            debug_loop(debugger);
            debugger->debug = false;
        }
    }

    return 0;
}

void debug_loop(debugger_t* debugger)
{
    uint16_t pc_addr = (debugger->cpu->reg.pc.word - 1);
    printf("\n> 0x%04X\t%02X\t%s\n\n", pc_addr, debugger->cpu->currop, debugger->current_disasm);

    while (1)
    {
        char cmd[50];
        printf("DBG > ");
        scanf_s("%s", cmd, 50);

        if (!strcmp(cmd, "c"))
        {
            break;
        }
        else if (!strcmp(cmd, "s"))
        {
            debugger->stopnext = true;
            break;
        }
        else if (!strcmp(cmd, "q"))
        {
            sys_error("Quit debugging.");
            break;
        }
        else if (!strcmp(cmd, "r"))
        {
            printf("CPU REGISTERS\n"\
                "\tA: %02x \tF: %02x \tAF: %04x\n"\
                "\tB: %02x \tC: %02x \tBC: %04x\n"\
                "\tD: %02x \tE: %02x \tDE: %04x\n"\
                "\tH: %02x \tL: %02x \tHL: %04x\n"\
                "\tSP: %04x \tPC: %04x\n",
                debugger->cpu->reg.af.hi, debugger->cpu->reg.af.lo, debugger->cpu->reg.af.word,
                debugger->cpu->reg.bc.hi, debugger->cpu->reg.bc.lo, debugger->cpu->reg.bc.word,
                debugger->cpu->reg.de.hi, debugger->cpu->reg.de.lo, debugger->cpu->reg.de.word,
                debugger->cpu->reg.hl.hi, debugger->cpu->reg.hl.lo, debugger->cpu->reg.hl.word,
                debugger->cpu->reg.sp.word, (debugger->cpu->reg.pc.word - 0x01));
        }
        else if (!strcmp(cmd, "i"))
        {
            printf("\n> 0x%04X\t%02X\t%s\n\n", pc_addr, debugger->cpu->currop, debugger->current_disasm);
        }
        else if (!strcmp(cmd, "h"))
        {
            printf("%s", DEBUGGER_INSTRUCTIONS);
        }
        else
        {
            printf("Unknown command.\n%s", DEBUGGER_INSTRUCTIONS);
        }
    }
}

void debug_instruction(cpu_t* cpu, mmu_t* mmu, const char* disasm, ...)
{
    debugger_t* debugger = debug_get(cpu);
    assert(debugger != NULL);

    char buffer[0xFF];
    va_list argptr;
    va_start(argptr, disasm);
    vsprintf_s(buffer, 0xFF, disasm, argptr);

    uint16_t pc_addr = (cpu->reg.pc.word - 1);
    bool isbreak = _debug_isbreak(debugger, pc_addr, buffer) || debugger->stopnext;

    if (debugger->printall)
    {
        log_cpu("0x%04X\t%02X\t%s", pc_addr, cpu->currop, buffer);
    }

    if (isbreak)
    {
        debugger->current_addr = pc_addr;
        strcpy_s(debugger->current_disasm, sizeof(debugger->current_disasm), buffer);
        debugger->stopnext = false;
        debugger->debug = true;
        //debug_loop(debugger);
    }
    
    va_end(argptr);
}
