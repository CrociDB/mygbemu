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
    //void(*opfunc)(cpu_t* cpu, mmu_t* mmu) = CPU_OP_TABLE[op];
    cpu->reg.pc.word++;
    if (!opfunc || !opfunc->func)
    {
        log_error("Op '%02X'does not exist", op);
        return;
    }

    //(*opfunc)(cpu, mmu);
    (*opfunc->func)(cpu, mmu);
    cpu->clock.m = opfunc->m;
    cpu->clock.t = opfunc->t;
    cpu->reg.pc.word += opfunc->b;
}


void cpu_init_table()
{
    log_message("Initializing CPU OP Table");

    optable[0x00] = (opfunc_t) { &cpu_op_nop, 1, 4, 0 };
    optable[0x31] = (opfunc_t) { &cpu_op_ld_sp_d16, 3, 13, 2 };
}

// OPs implementation

void cpu_op_nop(cpu_t* cpu, mmu_t* mmu) // $00
{
    log_cpu("NOP");
}

void cpu_op_ld_sp_d16(cpu_t* cpu, mmu_t* mmu) // $31
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    log_cpu("LD S, $%04X", word);

    cpu->reg.sp.word = word;
}

