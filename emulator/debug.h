#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUGGERS_MAX 2

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include <SDL3/SDL.h>

#include "cpu.h"
#include "mmu.h"
#include "ppu.h"

static const char* DEBUGGER_INSTRUCTIONS =
    "Usage:\n\t- c \t\t\t continue\n\t- s \t\t\t step\n\n\t- r \t\t\t display "
    "cpu registers"
    "\n\t- i \t\t\t info\n"
    "\n\t- mem8 [addr] \t\t display 8bit value in specified addr in memory"
    "\n\t- mem16 [addr] \t\t display 16bit value in specified addr in memory"
    "\n\t- set8 [addr] [value] \t set 8bit value in specified addr in memory"
    "\n\t- set16 [addr] [value] \t set 16bit value in specified addr in memory"
    "\n\n\t- h \t\t\t help\n\t- q \t\t\t quit\n";

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

  SDL_Thread* thread;

  uint16_t current_addr;
  char current_disasm[256];

  debug_breakpoint_t* breakpoints;
} debugger_t;

static debugger_t debuggers[DEBUGGERS_MAX];

debugger_t* debug_get(cpu_t* cpu);

void debug_breakpoint_addr(cpu_t* cpu, uint16_t addr);
void debug_breakpoint_asm(cpu_t* cpu, const char* disasm);

static void _debug_breakpoint(debugger_t* debugger,
                              debug_breakpoint_t* breakpoint);
static bool _debug_isbreak(debugger_t* debugger, uint16_t addr, char* asmline);

void debug_opcode_error(cpu_t* cpu);
void debug_instruction(cpu_t* cpu, mmu_t* mmu, const char* disasm, ...);
void debug_interruption(cpu_t* cpu, mmu_t* mmu, const char* msg, ...);

void debug_loop(debugger_t* debugger);

#endif
