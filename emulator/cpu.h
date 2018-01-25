#ifndef _CPU_H_
#define _CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mmu.h"
#include "log.h"

// Flag bits
#define CPU_FLAG_ZERO_BIT    0x80
#define CPU_FLAG_SUB_BIT     0x40
#define CPU_FLAG_HC_BIT      0x20
#define CPU_FLAG_CARRY_BIT   0x10

typedef union _reg16_t
{
    struct
    {
        uint8_t lo;
        uint8_t hi;
    };
    uint16_t word;
} reg16_t;

typedef union _clock_t
{
    uint8_t m;
    uint8_t t;
} clck_t;

typedef struct _cpu_t
{
    clck_t clock;
    
    struct
    {
        reg16_t af, bc, de, hl;
        reg16_t sp, pc;
    } reg;
    
} cpu_t;

typedef struct _opfunc_t
{
    void(*func)(cpu_t* cpu, mmu_t* mmu);
    uint8_t m;
    uint8_t t;
    uint8_t b;

} opfunc_t;

static opfunc_t optable[0xFF];


cpu_t* cpu_create();
void cpu_init_table();
void cpu_reset(cpu_t* cpu);
void cpu_tick(cpu_t* cpu, mmu_t* mmu);


inline void cpu_trick_set_bit(uint8_t* byte, uint8_t n);
inline void cpu_trick_unset_bit(uint8_t* byte, uint8_t n);

inline void cpu_flag_set_bit(cpu_t* cpu, uint8_t bit);
inline void cpu_flag_unset_bit(cpu_t* cpu, uint8_t bit);

// OPs

// $0x
void cpu_op_nop(cpu_t* cpu, mmu_t* mmu); // $00

// $3x
void cpu_op_ld_sp_d16(cpu_t* cpu, mmu_t* mmu); // $31

// $Ax
void cpu_op_xor_a(cpu_t* cpu, mmu_t* mmu); // $AF

#endif
