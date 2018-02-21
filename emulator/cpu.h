#ifndef _CPU_H_
#define _CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"
#include "log.h"

// Flag bits
#define CPU_FLAG_ZERO_BIT    7
#define CPU_FLAG_SUB_BIT     6
#define CPU_FLAG_HC_BIT      5
#define CPU_FLAG_CARRY_BIT   4

// Interruptins
#define CPU_INT_VBLANK      0x01
#define CPU_INT_LCD         (0x01 << 1)
#define CPU_INT_TIMER       (0x01 << 2)
#define CPU_INT_SERIAL      (0x01 << 3)
#define CPU_INT_JOYPAD      (0x01 << 4)

typedef struct _ppu_t ppu_t;
typedef struct _mmu_t mmu_t;

typedef enum _condition_e
{
    CPU_CONDITION_C,
    CPU_CONDITION_NC,
    CPU_CONDITION_Z,
    CPU_CONDITION_NZ,
    CPU_CONDITION_ALWAYS
} condition_e;

typedef union _reg16_t
{
    struct
    {
        uint8_t lo;
        uint8_t hi;
    };
    uint16_t word;
} reg16_t;

typedef struct _clock_t
{
    uint32_t m;
    uint32_t t;
} clck_t;

typedef struct _cpu_t
{
    clck_t currclock;
    clck_t totalclock;
    
    struct
    {
        reg16_t af, bc, de, hl;
        reg16_t sp, pc;
    } reg;

    bool ime;

    uint16_t currop;
    uint16_t curropaddr;
} cpu_t;

cpu_t* cpu_create();
void cpu_destroy(cpu_t* cpu);
void cpu_reset(cpu_t* cpu);
void cpu_run_cartridge(cpu_t* cpu, mmu_t* mmu, ppu_t* ppu);

void cpu_enable_int(cpu_t* cpu);
void cpu_disable_int(cpu_t* cpu);
void cpu_handle_int(cpu_t* cpu, mmu_t* mmu, uint8_t in);
void cpu_handle_int_vblank(cpu_t* cpu, mmu_t* mmu);

void cpu_tick(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb(cpu_t* cpu, mmu_t* mmu);

inline void cpu_flag_set_zero(cpu_t* cpu, const bool value);
inline void cpu_flag_set_sub(cpu_t* cpu, const bool value);
inline void cpu_flag_set_halfcarry(cpu_t* cpu, const bool value);
inline void cpu_flag_set_carry(cpu_t* cpu, const bool value);

inline bool cpu_flag(cpu_t* cpu, const uint8_t flag);

inline bool cpu_check_condition(cpu_t* cpu, condition_e condition);

// CPU Instructions

void cpu_ins_bit(cpu_t* cpu, uint8_t bit, uint8_t bytereg);
void cpu_ins_rl(cpu_t* cpu, uint8_t* reg);
void cpu_ins_rlc(cpu_t* cpu, uint8_t* reg);
void cpu_ins_rr(cpu_t* cpu, uint8_t* reg);
void cpu_ins_rrc(cpu_t* cpu, uint8_t* reg);
void cpu_ins_and(cpu_t* cpu, const uint8_t value);
void cpu_ins_xor(cpu_t* cpu, const uint8_t value);
void cpu_ins_or(cpu_t* cpu, const uint8_t value);
void cpu_ins_cp(cpu_t* cpu, const uint8_t value);

void cpu_ins_inc8(cpu_t* cpu, uint8_t* reg);
void cpu_ins_add8(cpu_t* cpu, uint8_t* reg, const uint8_t value);
void cpu_ins_add16(cpu_t* cpu, uint16_t* reg, const uint16_t value, bool zero);
void cpu_ins_dec8(cpu_t* cpu, uint8_t* reg);
void cpu_ins_sub8(cpu_t* cpu, uint8_t value);

void cpu_ins_call(cpu_t* cpu, mmu_t* mmu, uint16_t addr);
void cpu_ins_ret(cpu_t* cpu, mmu_t* mmu);
void cpu_ins_ret_condition(cpu_t* cpu, mmu_t* mmu, condition_e c);
void cpu_ins_jr(cpu_t* cpu, int8_t offset, condition_e c);
void cpu_ins_jp(cpu_t* cpu, uint16_t addr, condition_e c);

#endif
