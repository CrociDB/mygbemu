#ifndef _CPU_OPCODES_H_
#define _CPU_OPCODES_H_

#include "cpu.h"

typedef struct _opfunc_t
{
    void(*func)(cpu_t* cpu, mmu_t* mmu);
    uint8_t m;
    uint8_t t;
    uint8_t b;

} opfunc_t;

opfunc_t optable[0xFF];
opfunc_t optable_cb[0xFF];

void cpu_init_table();
static void _cpu_init_table_cb();

// OPs

void cpu_op_00(cpu_t* cpu, mmu_t* mmu);
void cpu_op_01(cpu_t* cpu, mmu_t* mmu);
void cpu_op_02(cpu_t* cpu, mmu_t* mmu);
void cpu_op_03(cpu_t* cpu, mmu_t* mmu);
void cpu_op_04(cpu_t* cpu, mmu_t* mmu);
void cpu_op_05(cpu_t* cpu, mmu_t* mmu);
void cpu_op_06(cpu_t* cpu, mmu_t* mmu);
void cpu_op_07(cpu_t* cpu, mmu_t* mmu);
void cpu_op_08(cpu_t* cpu, mmu_t* mmu);
void cpu_op_09(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_0f(cpu_t* cpu, mmu_t* mmu);

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
void cpu_op_1f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_20(cpu_t* cpu, mmu_t* mmu);
void cpu_op_21(cpu_t* cpu, mmu_t* mmu);
void cpu_op_22(cpu_t* cpu, mmu_t* mmu);
void cpu_op_23(cpu_t* cpu, mmu_t* mmu);
void cpu_op_24(cpu_t* cpu, mmu_t* mmu);
void cpu_op_25(cpu_t* cpu, mmu_t* mmu);
void cpu_op_26(cpu_t* cpu, mmu_t* mmu);
void cpu_op_27(cpu_t* cpu, mmu_t* mmu);
void cpu_op_28(cpu_t* cpu, mmu_t* mmu);
void cpu_op_29(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_2f(cpu_t* cpu, mmu_t* mmu);

void cpu_op_30(cpu_t* cpu, mmu_t* mmu);
void cpu_op_31(cpu_t* cpu, mmu_t* mmu);
void cpu_op_32(cpu_t* cpu, mmu_t* mmu);
void cpu_op_33(cpu_t* cpu, mmu_t* mmu);
void cpu_op_34(cpu_t* cpu, mmu_t* mmu);
void cpu_op_35(cpu_t* cpu, mmu_t* mmu);
void cpu_op_36(cpu_t* cpu, mmu_t* mmu);
void cpu_op_37(cpu_t* cpu, mmu_t* mmu);
void cpu_op_38(cpu_t* cpu, mmu_t* mmu);
void cpu_op_39(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_3f(cpu_t* cpu, mmu_t* mmu);

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
void cpu_op_88(cpu_t* cpu, mmu_t* mmu);
void cpu_op_89(cpu_t* cpu, mmu_t* mmu);
void cpu_op_8a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_8b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_8c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_8d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_8e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_8f(cpu_t* cpu, mmu_t* mmu);

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

void cpu_op_a0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a3(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a4(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a6(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a7(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a8(cpu_t* cpu, mmu_t* mmu);
void cpu_op_a9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_aa(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ab(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ac(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ad(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ae(cpu_t* cpu, mmu_t* mmu);
void cpu_op_af(cpu_t* cpu, mmu_t* mmu);

void cpu_op_b0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b3(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b4(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b6(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b7(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b8(cpu_t* cpu, mmu_t* mmu);
void cpu_op_b9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ba(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bb(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bc(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bd(cpu_t* cpu, mmu_t* mmu);
void cpu_op_be(cpu_t* cpu, mmu_t* mmu);
void cpu_op_bf(cpu_t* cpu, mmu_t* mmu);

void cpu_op_c0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c3(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c6(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c7(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c8(cpu_t* cpu, mmu_t* mmu);
void cpu_op_c9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ca(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cd(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cf(cpu_t* cpu, mmu_t* mmu);

void cpu_op_d0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d7(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d8(cpu_t* cpu, mmu_t* mmu);
void cpu_op_d9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_da(cpu_t* cpu, mmu_t* mmu);
void cpu_op_df(cpu_t* cpu, mmu_t* mmu);

void cpu_op_e0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e6(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e7(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e8(cpu_t* cpu, mmu_t* mmu);
void cpu_op_e9(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ea(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ef(cpu_t* cpu, mmu_t* mmu);

void cpu_op_f0(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f1(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f2(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f3(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f5(cpu_t* cpu, mmu_t* mmu);
void cpu_op_f7(cpu_t* cpu, mmu_t* mmu);
void cpu_op_fa(cpu_t* cpu, mmu_t* mmu);
void cpu_op_fb(cpu_t* cpu, mmu_t* mmu);
void cpu_op_fe(cpu_t* cpu, mmu_t* mmu);
void cpu_op_ff(cpu_t* cpu, mmu_t* mmu);

// CBs

void cpu_op_cb_00(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_01(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_02(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_03(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_04(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_05(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_06(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_07(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_08(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_09(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_0a(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_0b(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_0c(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_0d(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_0e(cpu_t* cpu, mmu_t* mmu);
void cpu_op_cb_0f(cpu_t* cpu, mmu_t* mmu);

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
