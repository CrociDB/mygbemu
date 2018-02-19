#include "sys.h"
#include "log.h"
#include "mmu.h"
#include "cpu.h"
#include "ppu.h"
#include "debug.h"
#include "cartridge.h"

#include "canvas.h"

void emu_run(cpu_t * cpu, mmu_t * mmu, ppu_t* ppu, canvas_t* canvas);

int main(int argc, const char* argv[]) 
{
    if (argc < 2)
    {
        sys_usage();
        exit(-1);
    }

    log_set_level(LOG_VERBOSE);

    canvas_t* canvas = canvas_init();

    mmu_t* mmu = mmu_create();
    cpu_t* cpu = cpu_create();
    ppu_t* ppu = ppu_create(mmu);

    cpu_init_table();

    debugger_t* debugger = debug_get(cpu);
    debugger->printall = false;

    debug_breakpoint_addr(cpu, 0x00f1);

    cartridge_t* rom = cartridge_load(argv[1]);
    mmu_load_rom(mmu, rom);
    cartridge_free(rom);

    mmu_load_bios(mmu);
    cpu_reset(cpu);

    debugger_init_loop(debugger, mmu, ppu);
    emu_run(cpu, mmu, ppu, canvas);
    debugger_end_loop(debugger);

    // Destroy everything
    canvas_destroy(canvas);
    ppu_destroy(ppu);
    cpu_destroy(cpu);
    mmu_destroy(mmu);

    return 0;
}

void emu_run(cpu_t* cpu, mmu_t* mmu, ppu_t* ppu, canvas_t* canvas)
{
    debugger_t* debugger = debug_get(cpu);

    while (canvas->running)
    {
        canvas_event_loop(canvas);

        if (!debugger->debug)
        {
            cpu_tick(cpu, mmu);
            ppu_tick(ppu, cpu, mmu);
        }

        canvas_update(canvas, ppu);
    }
}
