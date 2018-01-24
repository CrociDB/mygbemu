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
    void(*opfunc)(cpu_t* cpu, mmu_t* mmu) = CPU_OP_TABLE[op];
    cpu->reg.pc.word++;
    if (!opfunc)
    {
        log_error("Op does not exist");
        return;
    }

    (*opfunc)(cpu, mmu);
}


void cpu_init_table()
{
    log_message("Initializing CPU OP Table");

    CPU_OP_TABLE[0x00] = &cpu_op_nop;
    CPU_OP_TABLE[0x31] = &cpu_op_ld_sp_d16;
}

// OPs implementation

void cpu_op_nop(cpu_t* cpu, mmu_t* mmu) // $00
{
    log_cpu("NOP");

    cpu->clock.m = 1;
    cpu->clock.t = 4;
    cpu->reg.pc.word++;
}

void cpu_op_ld_sp_d16(cpu_t* cpu, mmu_t* mmu) // $31
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    log_cpu("LD S, $%04X", word);

    cpu->reg.sp.word = word;
    cpu->clock.m = 3;
    cpu->clock.t = 12;
    cpu->reg.pc.word += 3;
}

