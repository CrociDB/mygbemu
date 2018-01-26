#include "cpu.h"

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

    optable[0x00] = (opfunc_t) { &cpu_op_nop, 1, 4, 0 };

    optable[0x21] = (opfunc_t) { &cpu_op_ld_hl_d16, 3, 12, 2 };

    optable[0x31] = (opfunc_t) { &cpu_op_ld_sp_d16, 3, 13, 2 };
    optable[0x32] = (opfunc_t) { &cpu_op_ld_hlm_a , 1, 8, 0 };

    optable[0xAF] = (opfunc_t) { &cpu_op_xor_a, 1, 4, 0 };

    _cpu_init_table_cb();
    optable[0xCB] = (opfunc_t) { &cpu_op_cb, 0, 0, 0 };
}

void _cpu_init_table_cb()
{
    optable_cb[0x7C] = (opfunc_t) { &cpu_op_cb_bit_7_h, 2, 8, 0 };
}


// Set the specified bit of the flag to one
inline void cpu_flag_set_bit(cpu_t* cpu, const uint8_t bit)
{
    cpu->reg.af.lo |= bit;
}

// Set the specified bit of the flag to zero
inline void cpu_flag_unset_bit(cpu_t* cpu, const uint8_t bit)
{
    cpu->reg.af.lo &= bit;
}

inline void cpu_flag_set_zero(cpu_t* cpu, const bool value)
{
    if (!value)
        cpu_flag_unset_bit(cpu, CPU_FLAG_ZERO_BIT);
    else
        cpu_flag_set_bit(cpu, CPU_FLAG_ZERO_BIT);
}

inline void cpu_flag_set_sub(cpu_t* cpu, const bool value)
{
    if (!value)
        cpu_flag_unset_bit(cpu, CPU_FLAG_SUB_BIT);
    else
        cpu_flag_set_bit(cpu, CPU_FLAG_SUB_BIT);
}

inline void cpu_flag_set_halfcarry(cpu_t* cpu, const bool value)
{
    if (!value)
        cpu_flag_unset_bit(cpu, CPU_FLAG_HC_BIT);
    else
        cpu_flag_set_bit(cpu, CPU_FLAG_HC_BIT);
}

inline void cpu_flag_set_carry(cpu_t* cpu, const bool value)
{
    if (!value)
        cpu_flag_unset_bit(cpu, CPU_FLAG_CARRY_BIT);
    else
        cpu_flag_set_bit(cpu, CPU_FLAG_CARRY_BIT);
}

// CPU Instructions

void cpu_ins_bit(cpu_t* cpu, uint8_t bit, uint8_t bytereg)
{
    cpu_flag_set_zero(cpu, !util_check_bit(bytereg, bit));
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, true);
}


// OPs implementation

void cpu_op_nop(cpu_t* cpu, mmu_t* mmu) // $00
{
    log_cpu("NOP");
}

void cpu_op_ld_hl_d16(cpu_t * cpu, mmu_t * mmu) // $21
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    log_cpu("LD HL, $%04X", word);

    cpu->reg.hl.word = word;
}

void cpu_op_ld_sp_d16(cpu_t* cpu, mmu_t* mmu) // $31
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    log_cpu("LD S, $%04X", word);

    cpu->reg.sp.word = word;
}

void cpu_op_ld_hlm_a(cpu_t* cpu, mmu_t* mmu) // $32
{
    log_cpu("LD (HL-), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
    cpu->reg.hl.word--;
}

void cpu_op_xor_a(cpu_t* cpu, mmu_t * mmu) // $AF
{
    log_cpu("XOR A");

    cpu_flag_unset_bit(cpu, CPU_FLAG_CARRY_BIT);
    cpu_flag_unset_bit(cpu, CPU_FLAG_HC_BIT);
    cpu_flag_unset_bit(cpu, CPU_FLAG_SUB_BIT);

    cpu->reg.af.hi ^= cpu->reg.af.hi;

    if (!cpu->reg.af.hi)
        cpu_flag_set_bit(cpu, CPU_FLAG_ZERO_BIT);
    else
        cpu_flag_unset_bit(cpu, CPU_FLAG_ZERO_BIT);
}

// CB OP Codes

void cpu_op_cb_bit_7_h(cpu_t* cpu, mmu_t * mmu) // $CB7C
{
    log_cpu("BIT 7, H");
    cpu_ins_bit(cpu, 7, cpu->reg.hl.hi);
}
