#include "sys.h"
#include "log.h"
#include "mmu.h"
#include "cpu.h"
#include "debug.h"
#include "cartridge.h"

void emu_run(cpu_t* cpu, mmu_t* mmu);

int main(int argc, const char* argv[]) 
{
    if (argc < 2)
    {
        sys_usage();
        exit(-1);
    }

    log_set_level(LOG_VERBOSE);

    cpu_init_table();

    mmu_t* mmu = mmu_create();
    cpu_t* cpu = cpu_create();

    debugger_t* debugger = debug_get(cpu);
    debugger->printall = false;

    debug_breakpoint_addr(cpu, 0x00a3);

    //cartridge_t* rom = cartridge_load(argv[1]);
    //mmu_load_rom(mmu, rom);
    //cartridge_free(rom);

    mmu_load_bios(mmu);
    cpu_reset(cpu);

    emu_run(cpu, mmu);

    return 0;
}

void emu_run(cpu_t * cpu, mmu_t * mmu)
{
    while (1)
    {
        cpu_tick(cpu, mmu);
    }
}
