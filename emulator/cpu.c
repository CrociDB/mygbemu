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
    // Fetch instruction
    uint8_t op = mmu_read_byte(mmu, cpu->reg.pc.word);

    // Run instruction

    opfunc_t* opfunc = &optable[op];
    cpu->reg.pc.word++;
    if (!opfunc || !opfunc->func)
    {
        log_error("Op '%02X' does not exist", op);
        return;
    }

    //(*opfunc)(cpu, mmu);
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

    optable[0x20] = (opfunc_t) { &cpu_op_20, 2, 8, 1 };
    optable[0x21] = (opfunc_t) { &cpu_op_21, 3, 12, 2 };

    optable[0x31] = (opfunc_t) { &cpu_op_31, 3, 13, 2 };
    optable[0x32] = (opfunc_t) { &cpu_op_32 , 1, 8, 0 };

    optable[0xAF] = (opfunc_t) { &cpu_op_af, 1, 4, 0 };

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

void cpu_op_20(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = cpu_int_jr(cpu, mmu, CPU_CONDITION_NZ);
    debug_instruction(cpu, mmu, "JR NZ, $%2X", (uint8_t)offset);
}

void cpu_op_21(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD HL, $%04X", word);

    cpu->reg.hl.word = word;
}

void cpu_op_31(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD S, $%04X", word);

    cpu->reg.sp.word = word;
}

void cpu_op_32(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "LD (HL-), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
    cpu->reg.hl.word--;
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

// CB OP Codes

void cpu_op_cb_7c(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "BIT 7, H");
    cpu_ins_bit(cpu, 7, cpu->reg.hl.hi);
}
