#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUGGERS_MAX   2

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "cpu.h"
#include "mmu.h"
#include "log.h"

typedef struct _debugger_t
{
    bool assigned;
    cpu_t* cpu;
} debugger_t;

static debugger_t debuggers[DEBUGGERS_MAX];

debugger_t* debug_get(cpu_t* cpu);

void debug_instruction(cpu_t* cpu, mmu_t* mmu, const char* disasm, ...);

#endif