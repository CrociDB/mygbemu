#include "cpu.h"
#include "cpu_opcodes.h"
#include "debug.h"

cpu_t* cpu_create()
{
    log_message("Creating CPU");

    cpu_t* cpu = (cpu_t*)malloc(sizeof(cpu_t));
    cpu_init_table();
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
    cpu->ime = false;
    cpu->currclock = (clck_t){ 0,0 };
    cpu->totalclock = (clck_t){ 0,0 };
}

void cpu_run_cartridge(cpu_t* cpu, mmu_t* mmu, ppu_t* ppu)
{
    (*mmu->finished_bios) = true;
    cpu->reg.pc.word = 0x0100;
    cpu->reg.sp.word = 0xFFFE;
    cpu->reg.af.word = 0x01B0;
    cpu->reg.bc.word = 0x0013;
    cpu->reg.de.word = 0x00d8;
    cpu->reg.hl.word = 0x014d;

    // Reset VRAM
    memset((void*)(mmu->vram), 0, sizeof(mmu->vram));

    // Enable LCD
    ppu->control->lcd_display = true;
}

void cpu_enable_int(cpu_t* cpu)
{
    cpu->ime = true;
    cpu->currclock = (clck_t) { 1, 4 };
}

void cpu_disable_int(cpu_t* cpu)
{
    cpu->ime = false;
    cpu->currclock = (clck_t) { 1, 4 };
}

void cpu_handle_int(cpu_t* cpu, mmu_t* mmu, uint8_t in)
{
    if (in & CPU_INT_VBLANK)
        cpu_handle_int_vblank(cpu, mmu);
}

void cpu_handle_int_vblank(cpu_t* cpu, mmu_t* mmu)
{
    debug_interruption(cpu, mmu, "VBLANK");
    cpu->ime = false;
    (*mmu->intflags) &= ~CPU_INT_VBLANK;

    cpu_ins_call(cpu, mmu, 0x0040, 0);

    cpu->currclock.m += 4;
    cpu->currclock.t += 16;
}

void cpu_tick(cpu_t* cpu, mmu_t* mmu)
{
    // Fetch instruction
    uint8_t op = mmu_read_byte(mmu, cpu->reg.pc.word);
    cpu->currop = op << 8;
    cpu->curropaddr = cpu->reg.pc.word;

    // Run instruction
    opfunc_t* opfunc = &optable[op];
    cpu->reg.pc.word++;
    if (!opfunc || !opfunc->func)
    {
        debug_opcode_error(cpu);
        return;
    }

    (*opfunc->func)(cpu, mmu);
    cpu->currclock.m = opfunc->m;
    cpu->currclock.t = opfunc->t;
    cpu->reg.pc.word += opfunc->b;

    // Checking Interruptions
    if (cpu->ime && mmu->intenable && (*mmu->intflags))
    {
         uint8_t fired = mmu->intenable & (*mmu->intflags);

         cpu_handle_int(cpu, mmu, fired);
    }

    cpu->totalclock.m += cpu->currclock.m;
    cpu->totalclock.t += cpu->currclock.t;
}

// This is the caller for CB op code functions
void cpu_op_cb(cpu_t* cpu, mmu_t* mmu)
{
    // Fetch instruction
    uint8_t op = mmu_read_byte(mmu, cpu->reg.pc.word);
    cpu->currop += op;

    // Run instruction
    opfunc_t* opfunc_cb = &optable_cb[op];
    cpu->reg.pc.word++;
    if (!opfunc_cb || !opfunc_cb->func)
    {
        debug_opcode_error(cpu);
        return;
    }

    (*opfunc_cb->func)(cpu, mmu);
    cpu->currclock.m = opfunc_cb->m;
    cpu->currclock.t = opfunc_cb->t;
    cpu->reg.pc.word += opfunc_cb->b;
}

void cpu_flag_set_zero(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_ZERO_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_ZERO_BIT);
}

void cpu_flag_set_sub(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_SUB_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_SUB_BIT);
}

void cpu_flag_set_halfcarry(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_HC_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_HC_BIT);
}

void cpu_flag_set_carry(cpu_t* cpu, const bool value)
{
    if (value)
        util_set_bit(&cpu->reg.af.lo, CPU_FLAG_CARRY_BIT);
    else
        util_unset_bit(&cpu->reg.af.lo, CPU_FLAG_CARRY_BIT);
}

bool cpu_flag(cpu_t* cpu, const uint8_t flag)
{
    return util_check_bit(cpu->reg.af.lo, flag);
}

bool cpu_check_condition(cpu_t* cpu, condition_e condition)
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
        case CPU_CONDITION_ALWAYS:
            c = true;
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

void cpu_ins_rlc(cpu_t * cpu, uint8_t * reg)
{
    cpu_flag_set_carry(cpu, util_check_bit((*reg), 7));
    uint8_t carry = cpu_flag(cpu, CPU_FLAG_CARRY_BIT);

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

void cpu_ins_rrc(cpu_t * cpu, uint8_t * reg)
{
    cpu_flag_set_carry(cpu, util_check_bit((*reg), 0));
    uint8_t carry = cpu_flag(cpu, CPU_FLAG_CARRY_BIT);

    uint8_t res = ((*reg) >> 1) | (carry << 7);
    cpu_flag_set_zero(cpu, res == 0);

    (*reg) = res;

    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
}

void cpu_ins_sla(cpu_t * cpu, uint8_t * reg)
{
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);

    cpu_flag_set_carry(cpu, util_check_bit((*reg), 0));

    (*reg) <<= 1;

    cpu_flag_set_zero(cpu, (*reg) == 0);
}

void cpu_ins_sra(cpu_t * cpu, uint8_t * reg)
{
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);

    cpu_flag_set_carry(cpu, util_check_bit((*reg), 0));

    uint8_t top = util_check_bit((*reg), 7);
    (*reg) >>= 1;
    (*reg) |= top;

    cpu_flag_set_zero(cpu, (*reg) == 0);
}

void cpu_ins_srl(cpu_t * cpu, uint8_t * reg)
{
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);

    uint8_t top = util_check_bit((*reg), 7);
    (*reg) >>= 1;
    util_unset_bit(reg, 7);

    cpu_flag_set_carry(cpu, top);
    cpu_flag_set_zero(cpu, (*reg) == 0);
}

void cpu_ins_swap(cpu_t * cpu, uint8_t * reg)
{
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
    cpu_flag_set_carry(cpu, false);

    uint8_t lower = (*reg) & 0xF;
    uint8_t higher = (*reg) >> 4;

    (*reg) = lower << 4 | higher;

    cpu_flag_set_zero(cpu, (*reg) == 0);
}

void cpu_ins_and(cpu_t * cpu, const uint8_t value)
{
    cpu_flag_set_carry(cpu, false);
    cpu_flag_set_halfcarry(cpu, true);
    cpu_flag_set_sub(cpu, false);

    cpu->reg.af.hi &= value;

    cpu_flag_set_zero(cpu, !cpu->reg.af.hi);
}

void cpu_ins_xor(cpu_t* cpu, const uint8_t value)
{
    cpu_flag_set_carry(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
    cpu_flag_set_sub(cpu, false);

    cpu->reg.af.hi ^= value;

    cpu_flag_set_zero(cpu, !cpu->reg.af.hi);
}

void cpu_ins_or(cpu_t * cpu, const uint8_t value)
{
    cpu_flag_set_carry(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
    cpu_flag_set_sub(cpu, false);

    cpu->reg.af.hi |= value;

    cpu_flag_set_zero(cpu, !cpu->reg.af.hi);
}

void cpu_ins_inc8(cpu_t* cpu, uint8_t* reg)
{
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, (((*reg) & 0xF) == 0xF));
    (*reg)++;
    cpu_flag_set_zero(cpu, ((*reg) == 0));
}

void cpu_ins_add8(cpu_t* cpu, uint8_t* reg, const uint8_t value)
{
    cpu_flag_set_sub(cpu, false);

    uint8_t res = (*reg) + value;

    cpu_flag_set_zero(cpu, res == 0);
    cpu_flag_set_carry(cpu, ((*reg) + value) > 0xFF);
    cpu_flag_set_halfcarry(cpu, (((*reg) & 0xF) + (value & 0xF)) > 0xF);

    (*reg) = res;
}

void cpu_ins_add16(cpu_t* cpu, uint16_t* reg, const uint16_t value, bool zero)
{
    cpu_flag_set_sub(cpu, false);

    uint16_t res = (*reg) + value;

    if (zero) cpu_flag_set_zero(cpu, res == 0);
    cpu_flag_set_carry(cpu, ((*reg) + value) > 0xFFFF);
    cpu_flag_set_halfcarry(cpu, (((*reg) & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF);

    (*reg) = res;
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

void cpu_ins_adc(cpu_t* cpu, const uint8_t value)
{
    cpu_ins_add8(cpu, &cpu->reg.af.hi, value + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_ins_call(cpu_t * cpu, mmu_t * mmu, uint16_t addr, const uint8_t offset)
{
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.pc.word + offset);
    cpu->reg.pc.word = addr;
}

void cpu_ins_ret(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
    cpu->reg.pc.word = addr;
}

void cpu_ins_ret_condition(cpu_t * cpu, mmu_t * mmu, condition_e c)
{
    if (cpu_check_condition(cpu, c))
    {
        cpu_ins_ret(cpu, mmu);
        cpu->currclock.m += 3;
        cpu->currclock.t += 12;
    }
}

void cpu_ins_cp(cpu_t* cpu, const uint8_t value)
{
    cpu_flag_set_sub(cpu, true);

    cpu_flag_set_zero(cpu, cpu->reg.af.hi == value);
    cpu_flag_set_halfcarry(cpu, ((cpu->reg.af.hi & 0xf) - (value & 0xf)) < 0);
    cpu_flag_set_carry(cpu, cpu->reg.af.hi < value);
}

void cpu_ins_jr(cpu_t* cpu, int8_t offset, condition_e c)
{
    if (cpu_check_condition(cpu, c))
    {
        cpu->reg.pc.word += offset;
        cpu->currclock.m += 1;
        cpu->currclock.t += 4;
    }
}

void cpu_ins_jp(cpu_t* cpu, uint16_t addr, condition_e c)
{
    if (cpu_check_condition(cpu, c))
    {
        cpu->reg.pc.word = addr - 0x02;
        cpu->currclock.m += 1;
        cpu->currclock.t += 4;
    }
}
