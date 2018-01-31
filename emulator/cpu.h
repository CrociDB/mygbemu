#ifndef _CPU_H_
#define _CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"
#include "mmu.h"
#include "log.h"

// Flag bits
#define CPU_FLAG_ZERO_BIT    7
#define CPU_FLAG_SUB_BIT     6
#define CPU_FLAG_HC_BIT      5
#define CPU_FLAG_CARRY_BIT   4

typedef enum _condition_e
{
    CPU_CONDITION_C,
    CPU_CONDITION_NC,
    CPU_CONDITION_Z,
    CPU_CONDITION_NZ,
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
static opfunc_t optable_cb[0xFF];


cpu_t* cpu_create();
void cpu_init_table();
static void _cpu_init_table_cb();
void cpu_reset(cpu_t* cpu);

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
void cpu_ins_rr(cpu_t* cpu, uint8_t* reg);
void cpu_ins_inc8(cpu_t* cpu, uint8_t* reg);
void cpu_ins_dec8(cpu_t* cpu, uint8_t* reg);
void cpu_ins_call(cpu_t* cpu, mmu_t* mmu, uint16_t addr);
void cpu_ins_ret(cpu_t* cpu, mmu_t* mmu);

void cpu_int_jr(cpu_t* cpu, int8_t offset, condition_e c);

// OPs

void cpu_op_00(cpu_t* cpu, mmu_t* mmu);
void cpu_op_02(cpu_t* cpu, mmu_t* mmu);
void cpu_op_03(cpu_t* cpu, mmu_t* mmu);
void cpu_op_04(cpu_t* cpu, mmu_t* mmu);
void cpu_op_05(cpu_t* cpu, mmu_t* mmu);
void cpu_op_06(cpu_t* cpu, mmu_t* mmu);
void cpu_op_08(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0d(cpu_t* cpu, mmu_t* mmu);

void cpu_op_11(cpu_t* cpu, mmu_t* mmu);
void cpu_op_12(cpu_t* cpu, mmu_t* mmu);
void cpu_op_13(cpu_t* cpu, mmu_t* mmu);
void cpu_op_14(cpu_t* cpu, mmu_t* mmu);
void cpu_op_15(cpu_t* cpu, mmu_t* mmu);
void cpu_op_17(cpu_t* cpu, mmu_t* mmu);
void cpu_op_18(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1d(cpu_t* cpu, mmu_t* mmu);

void cpu_op_20(cpu_t* cpu, mmu_t* mmu);
void cpu_op_21(cpu_t* cpu, mmu_t* mmu);
void cpu_op_22(cpu_t* cpu, mmu_t* mmu);
void cpu_op_23(cpu_t* cpu, mmu_t* mmu);
void cpu_op_24(cpu_t* cpu, mmu_t* mmu);
void cpu_op_25(cpu_t* cpu, mmu_t* mmu);
void cpu_op_28(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2d(cpu_t* cpu, mmu_t* mmu);

void cpu_op_31(cpu_t* cpu, mmu_t* mmu);
void cpu_op_32(cpu_t* cpu, mmu_t* mmu);
void cpu_op_33(cpu_t* cpu, mmu_t* mmu);
void cpu_op_34(cpu_t* cpu, mmu_t* mmu);
void cpu_op_35(cpu_t* cpu, mmu_t* mmu);
void cpu_op_38(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3d(cpu_t* cpu, mmu_t* mmu);

void cpu_op_4f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_77(cpu_t* cpu, mmu_t* mmu);

void cpu_op_af(cpu_t* cpu, mmu_t* mmu);

void cpu_op_c1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cd(cpu_t* cpu, mmu_t* mmu);

void cpu_op_d1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d5(cpu_t* cpu, mmu_t* mmu);

void cpu_op_e0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e5(cpu_t* cpu, mmu_t* mmu);

void cpu_op_f1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f5(cpu_t* cpu, mmu_t* mmu);

// CBs

void cpu_op_cb_10(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_11(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_12(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_13(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_14(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_15(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_16(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_17(cpu_t* cpu, mmu_t* mmu);

void cpu_op_cb_18(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_19(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_1a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_1b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_1c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_1d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_1e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_1f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_cb_7c(cpu_t* cpu, mmu_t* mmu);


#endif
