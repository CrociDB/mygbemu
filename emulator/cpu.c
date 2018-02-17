#include "cpu.h"
#include "debug.h"

cpu_t* cpu_create()
{
    log_message("Creating CPU");

    cpu_t* cpu = (cpu_t*)malloc(sizeof(cpu_t));
    return cpu;
}

void cpu_destroy(cpu_t* cpu)
{
    free(cpu);
    cpu = NULL;
}

void cpu_reset(cpu_t* cpu)
{
    memset((void*)(&cpu->reg), 0, sizeof(cpu->reg));
}

void cpu_tick(cpu_t* cpu, mmu_t* mmu)
{
    if (cpu->reg.pc.word >= 0x8000) return;

    // Fetch instruction
    uint8_t op = mmu_read_byte(mmu, cpu->reg.pc.word);
    cpu->currop = op;

    // Run instruction
    opfunc_t* opfunc = &optable[op];
    cpu->reg.pc.word++;
    if (!opfunc || !opfunc->func)
    {
        log_error("Op '%02X' at 0x%04x does not exist", op, (cpu->reg.pc.word - 1));
        return;
    }

    (*opfunc->func)(cpu, mmu);
    cpu->currclock.m = opfunc->m;
    cpu->currclock.t = opfunc->t;
    cpu->reg.pc.word += opfunc->b;
}

// This is the caller for CB op code functions
void cpu_op_cb(cpu_t* cpu, mmu_t* mmu)
{
    // Fetch instruction
    uint8_t op = mmu_read_byte(mmu, cpu->reg.pc.word);

    // Run instruction
    opfunc_t* opfunc_cb = &optable_cb[op];
    cpu->reg.pc.word++;
    if (!opfunc_cb || !opfunc_cb->func)
    {
        log_error("Op 'CB%02X' does not exist", op);
        return;
    }

    (*opfunc_cb->func)(cpu, mmu);
    cpu->currclock.m = opfunc_cb->m;
    cpu->currclock.t = opfunc_cb->t;
    cpu->reg.pc.word += opfunc_cb->b;

    cpu->totalclock.m += cpu->currclock.m;
    cpu->totalclock.t += cpu->currclock.t;
}


void cpu_init_table()
{
    log_message("Initializing CPU OP Table");

    optable[0x00] = (opfunc_t) { &cpu_op_00, 1, 4, 0 };
    optable[0x01] = (opfunc_t) { &cpu_op_01, 3, 12, 2 };
    optable[0x02] = (opfunc_t) { &cpu_op_02, 1, 8, 0 };
    optable[0x03] = (opfunc_t) { &cpu_op_03, 1, 8, 0 };
    optable[0x04] = (opfunc_t) { &cpu_op_04, 1, 4, 0 };
    optable[0x05] = (opfunc_t) { &cpu_op_05, 1, 4, 0 };
    optable[0x06] = (opfunc_t) { &cpu_op_06, 2, 8, 1 };
    optable[0x0A] = (opfunc_t) { &cpu_op_0a, 1, 8, 0 };
    optable[0x0B] = (opfunc_t) { &cpu_op_0b, 1, 8, 0 };
    optable[0x0C] = (opfunc_t) { &cpu_op_0c, 1, 4, 0 };
    optable[0x0D] = (opfunc_t) { &cpu_op_0d, 1, 4, 0 };
    optable[0x0E] = (opfunc_t) { &cpu_op_0e, 2, 8, 1 };

    optable[0x11] = (opfunc_t) { &cpu_op_11, 3, 12, 2 };
    optable[0x12] = (opfunc_t) { &cpu_op_12, 1, 8, 0 };
    optable[0x13] = (opfunc_t) { &cpu_op_13, 1, 8, 0 };
    optable[0x14] = (opfunc_t) { &cpu_op_14, 1, 4, 0 };
    optable[0x15] = (opfunc_t) { &cpu_op_15, 1, 4, 0 };
    optable[0x16] = (opfunc_t) { &cpu_op_16, 2, 8, 1 };
    optable[0x17] = (opfunc_t) { &cpu_op_17, 1, 4, 0 };
    optable[0x18] = (opfunc_t) { &cpu_op_18, 2, 12, 1 };
    optable[0x1A] = (opfunc_t) { &cpu_op_1a, 1, 8, 0 };
    optable[0x1B] = (opfunc_t) { &cpu_op_1b, 1, 8, 0 };
    optable[0x1C] = (opfunc_t) { &cpu_op_1c, 1, 4, 0 };
    optable[0x1D] = (opfunc_t) { &cpu_op_1d, 1, 4, 0 };
    optable[0x1E] = (opfunc_t) { &cpu_op_1e, 2, 8, 1 };

    optable[0x20] = (opfunc_t) { &cpu_op_20, 2, 8, 1 };
    optable[0x21] = (opfunc_t) { &cpu_op_21, 3, 12, 2 };
    optable[0x22] = (opfunc_t) { &cpu_op_22, 1, 8, 0 };
    optable[0x23] = (opfunc_t) { &cpu_op_23, 1, 8, 0 };
    optable[0x24] = (opfunc_t) { &cpu_op_24, 1, 4, 0 };
    optable[0x25] = (opfunc_t) { &cpu_op_25, 1, 4, 0 };
    optable[0x26] = (opfunc_t) { &cpu_op_26, 2, 8, 1 };
    optable[0x28] = (opfunc_t) { &cpu_op_28, 2, 8, 1 };
    optable[0x2A] = (opfunc_t) { &cpu_op_2a, 1, 8, 0 };
    optable[0x2B] = (opfunc_t) { &cpu_op_2b, 1, 8, 0 };
    optable[0x2C] = (opfunc_t) { &cpu_op_2c, 1, 4, 0 };
    optable[0x2D] = (opfunc_t) { &cpu_op_2d, 1, 4, 0 };
    optable[0x2E] = (opfunc_t) { &cpu_op_2e, 2, 8, 1 };

    optable[0x30] = (opfunc_t) { &cpu_op_30, 2, 8, 1 };
    optable[0x31] = (opfunc_t) { &cpu_op_31, 3, 13, 2 };
    optable[0x32] = (opfunc_t) { &cpu_op_32 , 1, 8, 0 };
    optable[0x33] = (opfunc_t) { &cpu_op_33, 1, 8, 0 };
    optable[0x34] = (opfunc_t) { &cpu_op_34, 1, 12, 0 };
    optable[0x35] = (opfunc_t) { &cpu_op_35, 1, 12, 0 };
    optable[0x36] = (opfunc_t) { &cpu_op_36, 2, 12, 1 };
    optable[0x38] = (opfunc_t) { &cpu_op_38, 2, 8, 1 };
    optable[0x3A] = (opfunc_t) { &cpu_op_3a, 1, 8, 0 };
    optable[0x3B] = (opfunc_t) { &cpu_op_3b, 1, 8, 0 };
    optable[0x3C] = (opfunc_t) { &cpu_op_3c, 1, 4, 0 };
    optable[0x3D] = (opfunc_t) { &cpu_op_3d, 1, 4, 0 };
    optable[0x3E] = (opfunc_t) { &cpu_op_3e, 2, 8, 1 };

    optable[0x40] = (opfunc_t) { &cpu_op_40, 1, 4, 0 };
    optable[0x41] = (opfunc_t) { &cpu_op_41, 1, 4, 0 };
    optable[0x42] = (opfunc_t) { &cpu_op_42, 1, 4, 0 };
    optable[0x43] = (opfunc_t) { &cpu_op_43, 1, 4, 0 };
    optable[0x44] = (opfunc_t) { &cpu_op_44, 1, 4, 0 };
    optable[0x45] = (opfunc_t) { &cpu_op_45, 1, 4, 0 };
    optable[0x46] = (opfunc_t) { &cpu_op_46, 1, 8, 0 };
    optable[0x47] = (opfunc_t) { &cpu_op_47, 1, 4, 0 };
    optable[0x48] = (opfunc_t) { &cpu_op_48, 1, 4, 0 };
    optable[0x49] = (opfunc_t) { &cpu_op_49, 1, 4, 0 };
    optable[0x4A] = (opfunc_t) { &cpu_op_4a, 1, 4, 0 };
    optable[0x4B] = (opfunc_t) { &cpu_op_4b, 1, 4, 0 };
    optable[0x4C] = (opfunc_t) { &cpu_op_4c, 1, 4, 0 };
    optable[0x4D] = (opfunc_t) { &cpu_op_4d, 1, 4, 0 };
    optable[0x4E] = (opfunc_t) { &cpu_op_4e, 1, 8, 0 };
    optable[0x4F] = (opfunc_t) { &cpu_op_4f, 1, 4, 0 };

    optable[0x50] = (opfunc_t) { &cpu_op_50, 1, 4, 0 };
    optable[0x51] = (opfunc_t) { &cpu_op_51, 1, 4, 0 };
    optable[0x52] = (opfunc_t) { &cpu_op_52, 1, 4, 0 };
    optable[0x53] = (opfunc_t) { &cpu_op_53, 1, 4, 0 };
    optable[0x54] = (opfunc_t) { &cpu_op_54, 1, 4, 0 };
    optable[0x55] = (opfunc_t) { &cpu_op_55, 1, 4, 0 };
    optable[0x56] = (opfunc_t) { &cpu_op_56, 1, 8, 0 };
    optable[0x57] = (opfunc_t) { &cpu_op_57, 1, 4, 0 };
    optable[0x58] = (opfunc_t) { &cpu_op_58, 1, 4, 0 };
    optable[0x59] = (opfunc_t) { &cpu_op_59, 1, 4, 0 };
    optable[0x5A] = (opfunc_t) { &cpu_op_5a, 1, 4, 0 };
    optable[0x5B] = (opfunc_t) { &cpu_op_5b, 1, 4, 0 };
    optable[0x5C] = (opfunc_t) { &cpu_op_5c, 1, 4, 0 };
    optable[0x5D] = (opfunc_t) { &cpu_op_5d, 1, 4, 0 };
    optable[0x5E] = (opfunc_t) { &cpu_op_5e, 1, 8, 0 };
    optable[0x5F] = (opfunc_t) { &cpu_op_5f, 1, 4, 0 };

    optable[0x60] = (opfunc_t) { &cpu_op_60, 1, 4, 0 };
    optable[0x61] = (opfunc_t) { &cpu_op_61, 1, 4, 0 };
    optable[0x62] = (opfunc_t) { &cpu_op_62, 1, 4, 0 };
    optable[0x63] = (opfunc_t) { &cpu_op_63, 1, 4, 0 };
    optable[0x64] = (opfunc_t) { &cpu_op_64, 1, 4, 0 };
    optable[0x65] = (opfunc_t) { &cpu_op_65, 1, 4, 0 };
    optable[0x66] = (opfunc_t) { &cpu_op_66, 1, 8, 0 };
    optable[0x67] = (opfunc_t) { &cpu_op_67, 1, 4, 0 };
    optable[0x68] = (opfunc_t) { &cpu_op_68, 1, 4, 0 };
    optable[0x69] = (opfunc_t) { &cpu_op_69, 1, 4, 0 };
    optable[0x6A] = (opfunc_t) { &cpu_op_6a, 1, 4, 0 };
    optable[0x6B] = (opfunc_t) { &cpu_op_6b, 1, 4, 0 };
    optable[0x6C] = (opfunc_t) { &cpu_op_6c, 1, 4, 0 };
    optable[0x6D] = (opfunc_t) { &cpu_op_6d, 1, 4, 0 };
    optable[0x6E] = (opfunc_t) { &cpu_op_6e, 1, 8, 0 };
    optable[0x6F] = (opfunc_t) { &cpu_op_6f, 1, 4, 0 };

    optable[0x70] = (opfunc_t) { &cpu_op_70, 1, 8, 0 };
    optable[0x71] = (opfunc_t) { &cpu_op_71, 1, 8, 0 };
    optable[0x72] = (opfunc_t) { &cpu_op_72, 1, 8, 0 };
    optable[0x73] = (opfunc_t) { &cpu_op_73, 1, 8, 0 };
    optable[0x74] = (opfunc_t) { &cpu_op_74, 1, 8, 0 };
    optable[0x75] = (opfunc_t) { &cpu_op_75, 1, 8, 0 };
    //optable[0x76] = (opfunc_t) { &cpu_op_76, 1, 4, 0 };
    optable[0x77] = (opfunc_t) { &cpu_op_77, 1, 8, 0 };
    optable[0x78] = (opfunc_t) { &cpu_op_78, 1, 4, 0 };
    optable[0x79] = (opfunc_t) { &cpu_op_79, 1, 4, 0 };
    optable[0x7A] = (opfunc_t) { &cpu_op_7a, 1, 4, 0 };
    optable[0x7B] = (opfunc_t) { &cpu_op_7b, 1, 4, 0 };
    optable[0x7C] = (opfunc_t) { &cpu_op_7c, 1, 4, 0 };
    optable[0x7D] = (opfunc_t) { &cpu_op_7d, 1, 4, 0 };
    optable[0x7E] = (opfunc_t) { &cpu_op_7e, 1, 8, 0 };
    optable[0x7F] = (opfunc_t) { &cpu_op_7f, 1, 4, 0 };

    optable[0x77] = (opfunc_t) { &cpu_op_77, 1, 8, 0 };

    optable[0x90] = (opfunc_t) { &cpu_op_90, 1, 4, 0 };
    optable[0x91] = (opfunc_t) { &cpu_op_91, 1, 4, 0 };
    optable[0x92] = (opfunc_t) { &cpu_op_92, 1, 4, 0 };
    optable[0x93] = (opfunc_t) { &cpu_op_93, 1, 4, 0 };
    optable[0x94] = (opfunc_t) { &cpu_op_94, 1, 4, 0 };
    optable[0x95] = (opfunc_t) { &cpu_op_95, 1, 4, 0 };
    optable[0x96] = (opfunc_t) { &cpu_op_96, 1, 8, 0 };
    optable[0x97] = (opfunc_t) { &cpu_op_97, 1, 4, 0 };
    optable[0x98] = (opfunc_t) { &cpu_op_98, 1, 4, 0 };
    optable[0x99] = (opfunc_t) { &cpu_op_99, 1, 4, 0 };
    optable[0x9A] = (opfunc_t) { &cpu_op_9a, 1, 4, 0 };
    optable[0x9B] = (opfunc_t) { &cpu_op_9b, 1, 4, 0 };
    optable[0x9C] = (opfunc_t) { &cpu_op_9c, 1, 4, 0 };
    optable[0x9D] = (opfunc_t) { &cpu_op_9d, 1, 4, 0 };
    optable[0x9E] = (opfunc_t) { &cpu_op_9e, 1, 8, 0 };
    optable[0x9F] = (opfunc_t) { &cpu_op_9f, 1, 4, 0 };

    optable[0xAF] = (opfunc_t) { &cpu_op_af, 1, 4, 0 };

    optable[0xB8] = (opfunc_t) { &cpu_op_b8, 1, 4, 0 };
    optable[0xB9] = (opfunc_t) { &cpu_op_b9, 1, 4, 0 };
    optable[0xBA] = (opfunc_t) { &cpu_op_ba, 1, 4, 0 };
    optable[0xBB] = (opfunc_t) { &cpu_op_bb, 1, 4, 0 };
    optable[0xBC] = (opfunc_t) { &cpu_op_bc, 1, 4, 0 };
    optable[0xBD] = (opfunc_t) { &cpu_op_bd, 1, 4, 0 };
    optable[0xBE] = (opfunc_t) { &cpu_op_be, 1, 8, 0 };
    optable[0xBF] = (opfunc_t) { &cpu_op_bf, 1, 4, 0 };
    
    optable[0xC1] = (opfunc_t) { &cpu_op_c1, 1, 12, 0 };
    optable[0xC5] = (opfunc_t) { &cpu_op_c5, 1, 16, 0 };
    optable[0xC9] = (opfunc_t) { &cpu_op_c9, 1, 16, 0 };
    optable[0xCD] = (opfunc_t) { &cpu_op_cd, 3, 24, 0 };

    optable[0xD1] = (opfunc_t) { &cpu_op_d1, 1, 12, 0 };
    optable[0xD5] = (opfunc_t) { &cpu_op_d5, 1, 16, 0 };

    optable[0xE0] = (opfunc_t) { &cpu_op_e0, 2, 12, 1 };
    optable[0xE1] = (opfunc_t) { &cpu_op_e1, 1, 12, 0 };
    optable[0xE2] = (opfunc_t) { &cpu_op_e2, 2, 8, 0 };
    optable[0xE5] = (opfunc_t) { &cpu_op_e5, 1, 16, 0 };
    optable[0xEA] = (opfunc_t) { &cpu_op_ea, 3, 16, 2 };

    optable[0xF0] = (opfunc_t) { &cpu_op_f0, 2, 12, 1 };
    optable[0xF1] = (opfunc_t) { &cpu_op_f1, 1, 12, 0 };
    optable[0xF2] = (opfunc_t) { &cpu_op_f2, 2, 8, 0 };
    optable[0xF5] = (opfunc_t) { &cpu_op_f5, 1, 16, 0 };
    optable[0xFA] = (opfunc_t) { &cpu_op_fa, 3, 16, 2 };
    optable[0xFE] = (opfunc_t) { &cpu_op_fe, 2, 8, 1 };

    _cpu_init_table_cb();
    optable[0xCB] = (opfunc_t) { &cpu_op_cb, 0, 0, 0 };
}

void _cpu_init_table_cb()
{
    optable_cb[0x10] = (opfunc_t) { &cpu_op_cb_10, 2, 8, 0 };
    optable_cb[0x11] = (opfunc_t) { &cpu_op_cb_11, 2, 8, 0 };
    optable_cb[0x12] = (opfunc_t) { &cpu_op_cb_12, 2, 8, 0 };
    optable_cb[0x13] = (opfunc_t) { &cpu_op_cb_13, 2, 8, 0 };
    optable_cb[0x14] = (opfunc_t) { &cpu_op_cb_14, 2, 8, 0 };
    optable_cb[0x15] = (opfunc_t) { &cpu_op_cb_15, 2, 8, 0 };
    optable_cb[0x16] = (opfunc_t) { &cpu_op_cb_16, 2, 16, 0 };
    optable_cb[0x17] = (opfunc_t) { &cpu_op_cb_17, 2, 8, 0 };

    optable_cb[0x18] = (opfunc_t) { &cpu_op_cb_18, 2, 8, 0 };
    optable_cb[0x19] = (opfunc_t) { &cpu_op_cb_19, 2, 8, 0 };
    optable_cb[0x1A] = (opfunc_t) { &cpu_op_cb_1a, 2, 8, 0 };
    optable_cb[0x1B] = (opfunc_t) { &cpu_op_cb_1b, 2, 8, 0 };
    optable_cb[0x1C] = (opfunc_t) { &cpu_op_cb_1c, 2, 8, 0 };
    optable_cb[0x1D] = (opfunc_t) { &cpu_op_cb_1d, 2, 8, 0 };
    optable_cb[0x1E] = (opfunc_t) { &cpu_op_cb_1e, 2, 16, 0 };
    optable_cb[0x1F] = (opfunc_t) { &cpu_op_cb_1f, 2, 8, 0 };

    optable_cb[0x7C] = (opfunc_t) { &cpu_op_cb_7c, 2, 8, 0 };
}

inline void cpu_flag_set_zero(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_ZERO_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_ZERO_BIT);
}

inline void cpu_flag_set_sub(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_SUB_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_SUB_BIT);
}

inline void cpu_flag_set_halfcarry(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_HC_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_HC_BIT);
}

inline void cpu_flag_set_carry(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_CARRY_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_CARRY_BIT);
}

inline bool cpu_flag(cpu_t* cpu, const uint8_t flag)
{
    return util_check_bit(cpu->reg.af.lo, flag);
}

inline bool cpu_check_condition(cpu_t* cpu, condition_e condition)
{
    bool c = false;
    switch (condition)
    {
        case CPU_CONDITION_C:
            c = cpu_flag(cpu, CPU_FLAG_CARRY_BIT);
            break;
        case CPU_CONDITION_NC:
            c = !cpu_flag(cpu, CPU_FLAG_CARRY_BIT);
            break;
        case CPU_CONDITION_Z:
            c = cpu_flag(cpu, CPU_FLAG_ZERO_BIT);
            break;
        case CPU_CONDITION_NZ:
            c = !cpu_flag(cpu, CPU_FLAG_ZERO_BIT);
            break;
    }

    return c;
}

// CPU Instructions

void cpu_ins_bit(cpu_t* cpu, uint8_t bit, uint8_t bytereg)
{
    cpu_flag_set_zero(cpu, util_check_bit(bytereg, bit) == 0);
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, true);
}

void cpu_ins_rl(cpu_t* cpu, uint8_t* reg)
{
    uint8_t carry = cpu_flag(cpu, CPU_FLAG_CARRY_BIT);

    cpu_flag_set_carry(cpu, util_check_bit((*reg), 7));

    uint8_t res = ((*reg) << 1) | carry;
    cpu_flag_set_zero(cpu, res == 0);

    (*reg) = res;

    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
}

void cpu_ins_rr(cpu_t* cpu, uint8_t* reg)
{
    uint8_t carry = cpu_flag(cpu, CPU_FLAG_CARRY_BIT);

    cpu_flag_set_carry(cpu, util_check_bit((*reg), 0));

    uint8_t res = ((*reg) >> 1) | (carry << 7);
    cpu_flag_set_zero(cpu, res == 0);

    (*reg) = res;

    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
}

void cpu_ins_inc8(cpu_t* cpu, uint8_t* reg)
{
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, (((*reg) & 0xF) == 0xF));
    (*reg)++;
    cpu_flag_set_zero(cpu, ((*reg) == 0));
}

void cpu_ins_dec8(cpu_t * cpu, uint8_t * reg)
{
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, !(((*reg) & 0xF) == 0xF));
    (*reg)--;
    cpu_flag_set_zero(cpu, ((*reg) == 0));
}

void cpu_ins_sub8(cpu_t* cpu, uint8_t value)
{
    cpu_flag_set_sub(cpu, true);

    int8_t sa = (int8_t)(cpu->reg.af.hi - value);
    uint8_t a = (uint8_t)sa;

    cpu_flag_set_carry(cpu, sa < 0);
    cpu_flag_set_halfcarry(cpu, (a & 0xF) > (cpu->reg.af.hi & 0xF));
    cpu_flag_set_zero(cpu, a == 0);

    cpu->reg.af.hi = a;
}

void cpu_ins_call(cpu_t * cpu, mmu_t * mmu, uint16_t addr)
{
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.pc.word + 2);
    cpu->reg.pc.word = addr;
}

void cpu_ins_ret(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
    cpu->reg.pc.word = addr;
}

void cpu_ins_cp(cpu_t * cpu, uint8_t value)
{
    cpu_flag_set_sub(cpu, true);

    cpu_flag_set_zero(cpu, cpu->reg.af.hi == value);
    cpu_flag_set_halfcarry(cpu, ((cpu->reg.af.hi & 0xf) - (value & 0xf)) < 0);
    cpu_flag_set_carry(cpu, cpu->reg.af.hi < value);
}

void cpu_int_jr(cpu_t* cpu, int8_t offset, condition_e c)
{
    if (cpu_check_condition(cpu, c))
    {
        cpu->reg.pc.word += offset;
        cpu->currclock.t += 4;
    }
}


// OPs implementation

void cpu_op_00(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "NOP");
}

void cpu_op_01(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD BC, $%04x", word);
    cpu->reg.bc.word = word;
}

void cpu_op_02(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (BC), A");
    mmu_write_byte(mmu, cpu->reg.bc.word, cpu->reg.af.hi);
}

void cpu_op_03(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC BC");
    cpu->reg.bc.word++;
}

void cpu_op_04(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC B");
    cpu_ins_inc8(cpu, &cpu->reg.bc.hi);
}

void cpu_op_05(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC B");
    cpu_ins_dec8(cpu, &cpu->reg.bc.hi);
}

void cpu_op_0c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC C");
    cpu_ins_inc8(cpu, &cpu->reg.bc.lo);
}

void cpu_op_06(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD B, $%02X", byte);
    cpu->reg.bc.hi = byte;
}

void cpu_op_0b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC BC");
    cpu->reg.bc.word--;
}

void cpu_op_0a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (BC)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.bc.word);
}

void cpu_op_0e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD C, $%02X", byte);
    cpu->reg.bc.lo = byte;
}

void cpu_op_0d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC C");
    cpu_ins_dec8(cpu, &cpu->reg.bc.lo);
}

void cpu_op_11(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD DE, $%04x", word);
    cpu->reg.de.word = word;
}

void cpu_op_12(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (DE), A");
    mmu_write_byte(mmu, cpu->reg.de.word, cpu->reg.af.hi);
}

void cpu_op_13(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC DE");
    cpu->reg.de.word++;
}

void cpu_op_14(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC D");
    cpu_ins_inc8(cpu, &cpu->reg.de.hi);
}

void cpu_op_15(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC D");
    cpu_ins_dec8(cpu, &cpu->reg.de.hi);
}

void cpu_op_16(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD D, $%02X", byte);
    cpu->reg.de.hi = byte;
}

void cpu_op_17(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLA");
    cpu_ins_rl(cpu, &cpu->reg.af.hi);
    cpu_flag_set_zero(cpu, false);
}

void cpu_op_18(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR $%02x", (uint8_t)offset);
    cpu->reg.pc.word += offset;
}

void cpu_op_1a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (DE)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.de.word);
}

void cpu_op_1b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC DE");
    cpu->reg.de.word--;
}

void cpu_op_1c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC E");
    cpu_ins_inc8(cpu, &cpu->reg.de.lo);
}

void cpu_op_1d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC E");
    cpu_ins_dec8(cpu, &cpu->reg.de.lo);
}

void cpu_op_1e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD E, $%02X", byte);
    cpu->reg.de.lo = byte;
}

void cpu_op_20(cpu_t* cpu, mmu_t* mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR NZ, $%2X", (uint8_t)offset);
    cpu_int_jr(cpu, offset, CPU_CONDITION_NZ);
}

void cpu_op_21(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD HL, $%04X", word);
    cpu->reg.hl.word = word;
}

void cpu_op_22(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL+), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
    cpu->reg.hl.word++;
}

void cpu_op_23(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC HL");
    cpu->reg.hl.word++;
}

void cpu_op_24(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC H");
    cpu_ins_inc8(cpu, &cpu->reg.hl.hi);
}

void cpu_op_25(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC H");
    cpu_ins_dec8(cpu, &cpu->reg.hl.hi);
}

void cpu_op_26(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD H, $%02X", byte);
    cpu->reg.hl.hi = byte;
}

void cpu_op_28(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR Z, $%2X", (uint8_t)offset);
    cpu_int_jr(cpu, offset, CPU_CONDITION_Z);
}

void cpu_op_2a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (HL+)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.word++;
}

void cpu_op_2b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC HL");
    cpu->reg.hl.word--;
}

void cpu_op_2c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC L");
    cpu_ins_inc8(cpu, &cpu->reg.hl.lo);
}

void cpu_op_2d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC L");
    cpu_ins_dec8(cpu, &cpu->reg.hl.lo);
}

void cpu_op_2e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD L, $%02X", byte);
    cpu->reg.hl.lo = byte;
}

void cpu_op_30(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR NC, $%2X", (uint8_t)offset);
    cpu_int_jr(cpu, offset, CPU_CONDITION_NC);
}

void cpu_op_31(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD SP, $%04X", word);

    cpu->reg.sp.word = word;
}

void cpu_op_32(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "LD (HL-), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
    cpu->reg.hl.word--;
}

void cpu_op_33(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC SP");
    cpu->reg.sp.word++;
}

void cpu_op_34(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_inc8(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_35(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_dec8(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_36(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD (HL), $%02X", byte);
    mmu_write_byte(mmu, cpu->reg.hl.word, byte);
}

void cpu_op_38(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR C, $%2X", (uint8_t)offset);
    cpu_int_jr(cpu, offset, CPU_CONDITION_C);
}

void cpu_op_3a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (HL-)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.word--;
}

void cpu_op_3b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC SP");
    cpu->reg.sp.word--;
}

void cpu_op_3c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC A");
    cpu_ins_inc8(cpu, &cpu->reg.af.hi);
}

void cpu_op_3d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC A");
    cpu_ins_dec8(cpu, &cpu->reg.af.hi);
}

void cpu_op_3e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD A, $%02X", byte);
    cpu->reg.af.hi = byte;
}




void cpu_op_40(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, B");
    cpu->reg.bc.hi = cpu->reg.bc.hi;
}

void cpu_op_41(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, C");
    cpu->reg.bc.hi = cpu->reg.bc.lo;
}

void cpu_op_42(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, D");
    cpu->reg.bc.hi = cpu->reg.de.hi;
}

void cpu_op_43(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, E");
    cpu->reg.bc.hi = cpu->reg.de.lo;
}

void cpu_op_44(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, H");
    cpu->reg.bc.hi = cpu->reg.hl.hi;
}

void cpu_op_45(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, L");
    cpu->reg.bc.hi = cpu->reg.hl.lo;
}

void cpu_op_46(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.bc.hi = byte;
}

void cpu_op_47(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, A");
    cpu->reg.bc.hi = cpu->reg.af.hi;
}

void cpu_op_48(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, B");
    cpu->reg.bc.lo = cpu->reg.bc.hi;
}

void cpu_op_49(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, C");
    cpu->reg.bc.lo = cpu->reg.bc.lo;
}

void cpu_op_4a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, D");
    cpu->reg.bc.lo = cpu->reg.de.hi;
}

void cpu_op_4b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, E");
    cpu->reg.bc.lo = cpu->reg.de.lo;
}

void cpu_op_4c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, H");
    cpu->reg.bc.lo = cpu->reg.hl.hi;
}

void cpu_op_4d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, L");
    cpu->reg.bc.lo = cpu->reg.hl.lo;
}

void cpu_op_4e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.bc.lo = byte;
}

void cpu_op_4f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, A");
    cpu->reg.bc.lo = cpu->reg.af.hi;
}



void cpu_op_50(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, B");
    cpu->reg.de.hi = cpu->reg.bc.hi;
}

void cpu_op_51(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, C");
    cpu->reg.de.hi = cpu->reg.bc.lo;
}

void cpu_op_52(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, D");
    cpu->reg.de.hi = cpu->reg.de.hi;
}

void cpu_op_53(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, E");
    cpu->reg.de.hi = cpu->reg.de.lo;
}

void cpu_op_54(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, H");
    cpu->reg.de.hi = cpu->reg.hl.hi;
}

void cpu_op_55(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, L");
    cpu->reg.de.hi = cpu->reg.hl.lo;
}

void cpu_op_56(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.de.hi = byte;
}

void cpu_op_57(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, A");
    cpu->reg.de.hi = cpu->reg.af.hi;
}

void cpu_op_58(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, B");
    cpu->reg.de.lo = cpu->reg.bc.hi;
}

void cpu_op_59(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, C");
    cpu->reg.de.lo = cpu->reg.bc.lo;
}

void cpu_op_5a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, D");
    cpu->reg.de.lo = cpu->reg.de.hi;
}

void cpu_op_5b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, E");
    cpu->reg.de.lo = cpu->reg.de.lo;
}

void cpu_op_5c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, H");
    cpu->reg.de.lo = cpu->reg.hl.hi;
}

void cpu_op_5d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, L");
    cpu->reg.de.lo = cpu->reg.hl.lo;
}

void cpu_op_5e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.de.lo = byte;
}

void cpu_op_5f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, A");
    cpu->reg.de.lo = cpu->reg.af.hi;
}



void cpu_op_60(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, B");
    cpu->reg.hl.hi = cpu->reg.bc.hi;
}

void cpu_op_61(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, C");
    cpu->reg.hl.hi = cpu->reg.bc.lo;
}

void cpu_op_62(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, D");
    cpu->reg.hl.hi = cpu->reg.de.hi;
}

void cpu_op_63(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, E");
    cpu->reg.hl.hi = cpu->reg.de.lo;
}

void cpu_op_64(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, H");
    cpu->reg.hl.hi = cpu->reg.hl.hi;
}

void cpu_op_65(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, L");
    cpu->reg.hl.hi = cpu->reg.hl.lo;
}

void cpu_op_66(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.hi = byte;
}

void cpu_op_67(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, A");
    cpu->reg.hl.hi = cpu->reg.af.hi;
}

void cpu_op_68(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, B");
    cpu->reg.hl.lo = cpu->reg.bc.hi;
}

void cpu_op_69(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, C");
    cpu->reg.hl.lo = cpu->reg.bc.lo;
}

void cpu_op_6a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, D");
    cpu->reg.hl.lo = cpu->reg.de.hi;
}

void cpu_op_6b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, E");
    cpu->reg.hl.lo = cpu->reg.de.lo;
}

void cpu_op_6c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, H");
    cpu->reg.hl.lo = cpu->reg.hl.hi;
}

void cpu_op_6d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, L");
    cpu->reg.hl.lo = cpu->reg.hl.lo;
}

void cpu_op_6e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.lo = byte;
}

void cpu_op_6f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, A");
    cpu->reg.hl.lo = cpu->reg.af.hi;
}



void cpu_op_70(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), B");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.bc.hi);
}

void cpu_op_71(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), C");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.bc.lo);
}

void cpu_op_72(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), D");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.de.hi);
}

void cpu_op_73(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), E");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.de.lo);
}

void cpu_op_74(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), H");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.hl.hi);
}

void cpu_op_75(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), L");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.hl.lo);
}

void cpu_op_77(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
}

void cpu_op_78(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, B");
    cpu->reg.af.hi = cpu->reg.bc.hi;
}

void cpu_op_79(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, C");
    cpu->reg.af.hi = cpu->reg.bc.lo;
}

void cpu_op_7a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, D");
    cpu->reg.af.hi = cpu->reg.de.hi;
}

void cpu_op_7b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, E");
    cpu->reg.af.hi = cpu->reg.de.lo;
}

void cpu_op_7c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, H");
    cpu->reg.af.hi = cpu->reg.hl.hi;
}

void cpu_op_7d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, L");
    cpu->reg.af.hi = cpu->reg.hl.lo;
}

void cpu_op_7e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.af.hi = byte;
}

void cpu_op_7f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, A");
    cpu->reg.af.hi = cpu->reg.af.hi;
}

void cpu_op_90(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB B");
    cpu_ins_sub8(cpu, cpu->reg.bc.hi);
}

void cpu_op_91(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB C");
    cpu_ins_sub8(cpu, cpu->reg.bc.lo);
}

void cpu_op_92(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB D");
    cpu_ins_sub8(cpu, cpu->reg.de.hi);
}

void cpu_op_93(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB E");
    cpu_ins_sub8(cpu, cpu->reg.de.lo);
}

void cpu_op_94(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB H");
    cpu_ins_sub8(cpu, cpu->reg.hl.hi);
}

void cpu_op_95(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB L");
    cpu_ins_sub8(cpu, cpu->reg.hl.lo);
}

void cpu_op_96(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB (HL)");
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_sub8(cpu, value);
}

void cpu_op_97(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB A");
    cpu_ins_sub8(cpu, cpu->reg.af.hi);
}

void cpu_op_98(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, B");
    cpu_ins_sub8(cpu, cpu->reg.bc.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_99(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, C");
    cpu_ins_sub8(cpu, cpu->reg.bc.lo + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, D");
    cpu_ins_sub8(cpu, cpu->reg.de.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, E");
    cpu_ins_sub8(cpu, cpu->reg.de.lo + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, H");
    cpu_ins_sub8(cpu, cpu->reg.hl.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, L");
    cpu_ins_sub8(cpu, cpu->reg.hl.lo + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, (HL)");
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_sub8(cpu, value + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, A");
    cpu_ins_sub8(cpu, cpu->reg.af.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}



void cpu_op_af(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "XOR A");

    cpu_flag_set_carry(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
    cpu_flag_set_sub(cpu, false);

    cpu->reg.af.hi ^= cpu->reg.af.hi;

    cpu_flag_set_zero(cpu, !cpu->reg.af.hi);
}

void cpu_op_b8(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP B");
    cpu_ins_cp(cpu, cpu->reg.bc.hi);
}

void cpu_op_b9(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP C");
    cpu_ins_cp(cpu, cpu->reg.bc.lo);
}

void cpu_op_ba(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP D");
    cpu_ins_cp(cpu, cpu->reg.de.hi);
}

void cpu_op_bb(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP E");
    cpu_ins_cp(cpu, cpu->reg.de.lo);
}

void cpu_op_bc(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP H");
    cpu_ins_cp(cpu, cpu->reg.hl.hi);
}

void cpu_op_bd(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP L");
    cpu_ins_cp(cpu, cpu->reg.hl.lo);
}

void cpu_op_be(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    debug_instruction(cpu, mmu, "CP (HL)");
    cpu_ins_cp(cpu, value);
}

void cpu_op_bf(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP A");
    cpu_ins_cp(cpu, cpu->reg.af.hi);
}

void cpu_op_c1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP BC");
    cpu->reg.bc.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_c5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH BC");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.bc.word);
}

void cpu_op_c9(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RET");
    cpu_ins_ret(cpu, mmu);
}

void cpu_op_cd(cpu_t* cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "CALL $%04x", addr);

    cpu_ins_call(cpu, mmu, addr);
}

void cpu_op_d1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP DE");
    cpu->reg.de.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_d5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH DE");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.de.word);
}

void cpu_op_e0(cpu_t* cpu, mmu_t* mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD ($FF00+$%02x), A", byte);
    uint16_t addr = 0xFF00 + byte;
    mmu_write_byte(mmu, addr, cpu->reg.af.hi);
}

void cpu_op_e1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP HL");
    cpu->reg.hl.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_e2(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "LD ($FF00+C), A");
    uint16_t addr = 0xFF00 + cpu->reg.bc.lo;
    mmu_write_byte(mmu, addr, cpu->reg.af.hi);
}

void cpu_op_e5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH HL");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.hl.word);
}

void cpu_op_ea(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD ($%04x), A", addr);
    mmu_write_byte(mmu, addr, cpu->reg.af.hi);
}

void cpu_op_f0(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD A, ($FF00+$%02x)", byte);
    uint16_t addr = 0xFF00 + byte;
    cpu->reg.af.hi = mmu_read_byte(mmu, addr);
}

void cpu_op_f1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP AF");
    cpu->reg.af.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_f2(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, ($FF00+C)");
    uint16_t addr = 0xFF00 + cpu->reg.bc.lo;
    cpu->reg.af.hi = mmu_read_byte(mmu, addr);
}

void cpu_op_f5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH AF");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.af.word);
}

void cpu_op_fa(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD A, ($%04x)", addr);
    cpu->reg.af.hi = mmu_read_byte(mmu, addr);
}

void cpu_op_fe(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t v = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "CP $%02x", v);
    cpu_ins_cp(cpu, v);
}

// CB OP Codes

void cpu_op_cb_10(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL B");
    cpu_ins_rl(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_11(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL C");
    cpu_ins_rl(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_12(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL D");
    cpu_ins_rl(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_13(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL E");
    cpu_ins_rl(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_14(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL H");
    cpu_ins_rl(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_15(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL L");
    cpu_ins_rl(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_16(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_rl(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_17(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL A");
    cpu_ins_rl(cpu, &cpu->reg.af.hi);
}

void cpu_op_cb_18(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR B");
    cpu_ins_rr(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_19(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR C");
    cpu_ins_rr(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_1a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR D");
    cpu_ins_rr(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_1b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR E");
    cpu_ins_rr(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_1c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR H");
    cpu_ins_rr(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_1d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR L");
    cpu_ins_rr(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_1e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_rr(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_1f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR A");
    cpu_ins_rr(cpu, &cpu->reg.af.hi);
}

void cpu_op_cb_7c(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "BIT 7, H");
    cpu_ins_bit(cpu, 7, cpu->reg.hl.hi);
}
