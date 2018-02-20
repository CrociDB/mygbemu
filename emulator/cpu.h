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

    uint8_t currop;
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
void cpu_destroy(cpu_t* cpu);
void cpu_init_table();
static void _cpu_init_table_cb();
void cpu_reset(cpu_t* cpu);
void cpu_run_cartridge(cpu_t* cpu);

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
void cpu_ins_add8(cpu_t* cpu, uint8_t* reg, const uint8_t value);
void cpu_ins_add16(cpu_t* cpu, uint16_t* reg, const uint16_t value, bool zero);
void cpu_ins_dec8(cpu_t* cpu, uint8_t* reg);
void cpu_ins_sub8(cpu_t* cpu, uint8_t value);
void cpu_ins_call(cpu_t* cpu, mmu_t* mmu, uint16_t addr);
void cpu_ins_ret(cpu_t* cpu, mmu_t* mmu);
void cpu_ins_cp(cpu_t* cpu, uint8_t value);

void cpu_ins_jr(cpu_t* cpu, int8_t offset, condition_e c);
void cpu_ins_jp(cpu_t* cpu, uint16_t addr, condition_e c);

// OPs

void cpu_op_00(cpu_t* cpu, mmu_t* mmu);
void cpu_op_01(cpu_t* cpu, mmu_t* mmu);
void cpu_op_02(cpu_t* cpu, mmu_t* mmu);
void cpu_op_03(cpu_t* cpu, mmu_t* mmu);
void cpu_op_04(cpu_t* cpu, mmu_t* mmu);
void cpu_op_05(cpu_t* cpu, mmu_t* mmu);
void cpu_op_06(cpu_t* cpu, mmu_t* mmu);
void cpu_op_09(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0e(cpu_t* cpu, mmu_t* mmu);

void cpu_op_11(cpu_t* cpu, mmu_t* mmu);
void cpu_op_12(cpu_t* cpu, mmu_t* mmu);
void cpu_op_13(cpu_t* cpu, mmu_t* mmu);
void cpu_op_14(cpu_t* cpu, mmu_t* mmu);
void cpu_op_15(cpu_t* cpu, mmu_t* mmu);
void cpu_op_16(cpu_t* cpu, mmu_t* mmu);
void cpu_op_17(cpu_t* cpu, mmu_t* mmu);
void cpu_op_18(cpu_t* cpu, mmu_t* mmu);
void cpu_op_19(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_1e(cpu_t* cpu, mmu_t* mmu);

void cpu_op_20(cpu_t* cpu, mmu_t* mmu);
void cpu_op_21(cpu_t* cpu, mmu_t* mmu);
void cpu_op_22(cpu_t* cpu, mmu_t* mmu);
void cpu_op_23(cpu_t* cpu, mmu_t* mmu);
void cpu_op_24(cpu_t* cpu, mmu_t* mmu);
void cpu_op_25(cpu_t* cpu, mmu_t* mmu);
void cpu_op_26(cpu_t* cpu, mmu_t* mmu);
void cpu_op_28(cpu_t* cpu, mmu_t* mmu);
void cpu_op_29(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2e(cpu_t* cpu, mmu_t* mmu);

void cpu_op_30(cpu_t* cpu, mmu_t* mmu);
void cpu_op_31(cpu_t* cpu, mmu_t* mmu);
void cpu_op_32(cpu_t* cpu, mmu_t* mmu);
void cpu_op_33(cpu_t* cpu, mmu_t* mmu);
void cpu_op_34(cpu_t* cpu, mmu_t* mmu);
void cpu_op_35(cpu_t* cpu, mmu_t* mmu);
void cpu_op_36(cpu_t* cpu, mmu_t* mmu);
void cpu_op_38(cpu_t* cpu, mmu_t* mmu);
void cpu_op_39(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3e(cpu_t* cpu, mmu_t* mmu);

void cpu_op_40(cpu_t* cpu, mmu_t* mmu);
void cpu_op_41(cpu_t* cpu, mmu_t* mmu);
void cpu_op_42(cpu_t* cpu, mmu_t* mmu);
void cpu_op_43(cpu_t* cpu, mmu_t* mmu);
void cpu_op_44(cpu_t* cpu, mmu_t* mmu);
void cpu_op_45(cpu_t* cpu, mmu_t* mmu);
void cpu_op_46(cpu_t* cpu, mmu_t* mmu);
void cpu_op_47(cpu_t* cpu, mmu_t* mmu);
void cpu_op_48(cpu_t* cpu, mmu_t* mmu);
void cpu_op_49(cpu_t* cpu, mmu_t* mmu);
void cpu_op_4a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_4b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_4c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_4d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_4e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_4f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_50(cpu_t* cpu, mmu_t* mmu);
void cpu_op_51(cpu_t* cpu, mmu_t* mmu);
void cpu_op_52(cpu_t* cpu, mmu_t* mmu);
void cpu_op_53(cpu_t* cpu, mmu_t* mmu);
void cpu_op_54(cpu_t* cpu, mmu_t* mmu);
void cpu_op_55(cpu_t* cpu, mmu_t* mmu);
void cpu_op_56(cpu_t* cpu, mmu_t* mmu);
void cpu_op_57(cpu_t* cpu, mmu_t* mmu);
void cpu_op_58(cpu_t* cpu, mmu_t* mmu);
void cpu_op_59(cpu_t* cpu, mmu_t* mmu);
void cpu_op_5a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_5b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_5c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_5d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_5e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_5f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_60(cpu_t* cpu, mmu_t* mmu);
void cpu_op_61(cpu_t* cpu, mmu_t* mmu);
void cpu_op_62(cpu_t* cpu, mmu_t* mmu);
void cpu_op_63(cpu_t* cpu, mmu_t* mmu);
void cpu_op_64(cpu_t* cpu, mmu_t* mmu);
void cpu_op_65(cpu_t* cpu, mmu_t* mmu);
void cpu_op_66(cpu_t* cpu, mmu_t* mmu);
void cpu_op_67(cpu_t* cpu, mmu_t* mmu);
void cpu_op_68(cpu_t* cpu, mmu_t* mmu);
void cpu_op_69(cpu_t* cpu, mmu_t* mmu);
void cpu_op_6a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_6b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_6c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_6d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_6e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_6f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_70(cpu_t* cpu, mmu_t* mmu);
void cpu_op_71(cpu_t* cpu, mmu_t* mmu);
void cpu_op_72(cpu_t* cpu, mmu_t* mmu);
void cpu_op_73(cpu_t* cpu, mmu_t* mmu);
void cpu_op_74(cpu_t* cpu, mmu_t* mmu);
void cpu_op_75(cpu_t* cpu, mmu_t* mmu);
//void cpu_op_76(cpu_t* cpu, mmu_t* mmu);
void cpu_op_77(cpu_t* cpu, mmu_t* mmu);
void cpu_op_78(cpu_t* cpu, mmu_t* mmu);
void cpu_op_79(cpu_t* cpu, mmu_t* mmu);
void cpu_op_7a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_7b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_7c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_7d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_7e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_7f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_80(cpu_t* cpu, mmu_t* mmu);
void cpu_op_81(cpu_t* cpu, mmu_t* mmu);
void cpu_op_82(cpu_t* cpu, mmu_t* mmu);
void cpu_op_83(cpu_t* cpu, mmu_t* mmu);
void cpu_op_84(cpu_t* cpu, mmu_t* mmu);
void cpu_op_85(cpu_t* cpu, mmu_t* mmu);
void cpu_op_86(cpu_t* cpu, mmu_t* mmu);
void cpu_op_87(cpu_t* cpu, mmu_t* mmu);

void cpu_op_90(cpu_t* cpu, mmu_t* mmu);
void cpu_op_91(cpu_t* cpu, mmu_t* mmu);
void cpu_op_92(cpu_t* cpu, mmu_t* mmu);
void cpu_op_93(cpu_t* cpu, mmu_t* mmu);
void cpu_op_94(cpu_t* cpu, mmu_t* mmu);
void cpu_op_95(cpu_t* cpu, mmu_t* mmu);
void cpu_op_96(cpu_t* cpu, mmu_t* mmu);
void cpu_op_97(cpu_t* cpu, mmu_t* mmu);
void cpu_op_98(cpu_t* cpu, mmu_t* mmu);
void cpu_op_99(cpu_t* cpu, mmu_t* mmu);
void cpu_op_9a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_9b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_9c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_9d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_9e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_9f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_af(cpu_t* cpu, mmu_t* mmu);

void cpu_op_b8(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ba(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bb(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bc(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bd(cpu_t* cpu, mmu_t* mmu);
void cpu_op_be(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bf(cpu_t* cpu, mmu_t* mmu);

void cpu_op_c1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c3(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c6(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ca(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cd(cpu_t* cpu, mmu_t* mmu);

void cpu_op_d1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_da(cpu_t* cpu, mmu_t* mmu);

void cpu_op_e0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e8(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ea(cpu_t* cpu, mmu_t* mmu);

void cpu_op_f0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_fa(cpu_t* cpu, mmu_t* mmu);
void cpu_op_fe(cpu_t* cpu, mmu_t* mmu);

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
