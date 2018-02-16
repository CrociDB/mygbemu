#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUGGERS_MAX   2

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <SDL.h>

#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "log.h"

static const char* DEBUGGER_INSTRUCTIONS = "Usage:\n\tc - continue\n\ts - step\n\n\tr - display cpu registers"\
                                           "\n\ti - info\n\n\th - help\n\tq - quit\n";

typedef enum _debug_breakpoint_type_e
{
    DEBUG_BREAKPOINT_ADDR,
    DEBUG_BREAKPOINT_ASM
} debug_breakpoint_type_e;

typedef struct _debug_breakpoint_t
{
    debug_breakpoint_type_e type;
    union
    {
        uint16_t addr;
        char* asmline;
    };

    struct _debug_breakpoint_t* next;
} debug_breakpoint_t;


typedef struct _debugger_t
{
    bool assigned;
    cpu_t* cpu;
    mmu_t* mmu;
    ppu_t* ppu;
    bool printall;
    bool stopnext;

    bool running;
    bool debug;
    SDL_Thread* thread;

    uint16_t current_addr;
    char current_disasm[256];

    debug_breakpoint_t* breakpoints;
} debugger_t;

static debugger_t debuggers[DEBUGGERS_MAX];

debugger_t* debug_get(cpu_t* cpu);
void debugger_init_loop(debugger_t* debugger, mmu_t* mmu, ppu_t* ppu);
void debugger_end_loop(debugger_t* debugger);

void debug_breakpoint_addr(cpu_t* cpu, uint16_t addr);
void debug_breakpoint_asm(cpu_t* cpu, const char* disasm);

static void _debug_breakpoint(debugger_t* debugger, debug_breakpoint_t* breakpoint);
static bool _debug_isbreak(debugger_t* debugger, uint16_t addr, char* asmline);

void debug_instruction(cpu_t* cpu, mmu_t* mmu, const char* disasm, ...);

static int debug_thread_loop(void* data);
void debug_loop(debugger_t* debugger);

#endif