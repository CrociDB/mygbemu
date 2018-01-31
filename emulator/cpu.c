#include "cpu.h"
#include "debug.h"

cpu_t* cpu_create()
{
    log_message("Creating CPU");

    cpu_t* cpu = (cpu_t*)malloc(sizeof(cpu_t));
    return cpu;
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

    // Run instruction
    opfunc_t* opfunc = &optable[op];
    cpu->reg.pc.word++;
    if (!opfunc || !opfunc->func)
    {
        log_error("Op '%02X' at 0x%04x does not exist", op, (cpu->reg.pc.word - 1));
        return;
    }

    (*opfunc->func)(cpu, mmu);
    cpu->clock.m = opfunc->m;
    cpu->clock.t = opfunc->t;
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
    cpu->clock.m = opfunc_cb->m;
    cpu->clock.t = opfunc_cb->t;
    cpu->reg.pc.word += opfunc_cb->b;
}


void cpu_init_table()
{
    log_message("Initializing CPU OP Table");

    optable[0x00] = (opfunc_t) { &cpu_op_00, 1, 4, 0 };
    optable[0x0c] = (opfunc_t) { &cpu_op_0c, 1, 4, 0 };
    optable[0x06] = (opfunc_t) { &cpu_op_06, 2, 8, 1 };
    optable[0x0e] = (opfunc_t) { &cpu_op_0e, 2, 8, 1 };

    optable[0x11] = (opfunc_t) { &cpu_op_11, 3, 12, 2 };
    optable[0x1a] = (opfunc_t) { &cpu_op_1a, 1, 8, 0 };

    optable[0x20] = (opfunc_t) { &cpu_op_20, 2, 8, 1 };
    optable[0x21] = (opfunc_t) { &cpu_op_21, 3, 12, 2 };

    optable[0x31] = (opfunc_t) { &cpu_op_31, 3, 13, 2 };
    optable[0x32] = (opfunc_t) { &cpu_op_32 , 1, 8, 0 };
    optable[0x3E] = (opfunc_t) { &cpu_op_3e, 2, 8, 1 };

    optable[0x4F] = (opfunc_t) { &cpu_op_4f, 1, 4, 0 };

    optable[0x77] = (opfunc_t) { &cpu_op_77, 1, 8, 0 };

    optable[0xAF] = (opfunc_t) { &cpu_op_af, 1, 4, 0 };
    
    optable[0xC1] = (opfunc_t) { &cpu_op_c1, 1, 12, 0 };
    optable[0xC5] = (opfunc_t) { &cpu_op_c5, 1, 16, 0 };
    optable[0xCD] = (opfunc_t) { &cpu_op_cd, 3, 24, 0 };

    optable[0xD1] = (opfunc_t) { &cpu_op_d1, 1, 12, 0 };
    optable[0xD5] = (opfunc_t) { &cpu_op_d5, 1, 16, 0 };

    optable[0xE0] = (opfunc_t) { &cpu_op_e0, 2, 12, 1 };
    optable[0xE1] = (opfunc_t) { &cpu_op_e1, 1, 12, 0 };
    optable[0xE2] = (opfunc_t) { &cpu_op_e2, 2, 8, 0 };
    optable[0xE5] = (opfunc_t) { &cpu_op_e5, 1, 16, 0 };

    optable[0xF1] = (opfunc_t) { &cpu_op_f1, 1, 12, 0 };
    optable[0xF5] = (opfunc_t) { &cpu_op_f5, 1, 16, 0 };

    _cpu_init_table_cb();
    optable[0xCB] = (opfunc_t) { &cpu_op_cb, 0, 0, 0 };
}

void _cpu_init_table_cb()
{
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
    cpu_flag_set_zero(cpu, !util_check_bit(bytereg, bit));
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, true);
}

int8_t cpu_int_jr(cpu_t* cpu, mmu_t* mmu, condition_e c)
{
    int8_t offset = 0;

    if (cpu_check_condition(cpu, c))
    {
        offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
        cpu->reg.pc.word += offset;
        cpu->clock.t += 4;
    }

    return offset;
}


// OPs implementation

void cpu_op_00(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "NOP");
}

void cpu_op_0c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC C");
    cpu->reg.bc.lo++;
}

void cpu_op_06(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD B, $%02X", byte);

    cpu->reg.bc.hi = byte;
}

void cpu_op_0e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD C, $%02X", byte);

    cpu->reg.bc.lo = byte;
}

void cpu_op_11(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD DE, $%04x", word);

    cpu->reg.de.word = word;
}

void cpu_op_1a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (DE)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.de.word);
}

void cpu_op_20(cpu_t* cpu, mmu_t* mmu)
{
    int8_t offset = cpu_int_jr(cpu, mmu, CPU_CONDITION_NZ);
    debug_instruction(cpu, mmu, "JR NZ, $%2X", (uint8_t)offset);
}

void cpu_op_21(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD HL, $%04X", word);

    cpu->reg.hl.word = word;
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

void cpu_op_3e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD A, $%02X", byte);

    cpu->reg.af.hi = byte;
}

void cpu_op_4f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, A");
    cpu->reg.bc.lo = cpu->reg.af.hi;
}

void cpu_op_77(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
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

void cpu_op_cd(cpu_t* cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "CALL $%04x", addr);

    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.pc.word + 2);
    cpu->reg.pc.word = addr;
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

    uint8_t addr = 0xFF00 + byte;
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

void cpu_op_f1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP AF");
    cpu->reg.af.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_f5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH AF");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.af.word);
}

// CB OP Codes

void cpu_op_cb_7c(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "BIT 7, H");
    cpu_ins_bit(cpu, 7, cpu->reg.hl.hi);
}
