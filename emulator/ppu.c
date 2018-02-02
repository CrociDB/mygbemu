#include "ppu.h"
#include "log.h"

ppu_t* ppu_create(mmu_t* mmu)
{
    log_message("Creating PPU");

    ppu_t* ppu = (ppu_t*)malloc(sizeof(ppu_t));
    ppu->vram = mmu->vram;
    ppu->oam = mmu->oam;

    ppu->mode = PPU_MODE_OAM;
    ppu->clockcount = 0;
    ppu->line = 0;

    return ppu;
}

void ppu_destroy(ppu_t* ppu)
{
    free(ppu);
    ppu = NULL;
}

void ppu_tick(ppu_t* ppu, cpu_t* cpu, mmu_t* mmu)
{
    ppu->clockcount += cpu->currclock.t;

    switch (ppu->mode)
    {
        case PPU_MODE_OAM:
            if (ppu->clockcount >= 80)
            {
                ppu->clockcount = 0;
                ppu->mode = PPU_MODE_VRAM;
            }
            break;
        case PPU_MODE_VRAM:
            if (ppu->clockcount >= 172)
            {
                ppu->clockcount = 0;
                ppu->mode = PPU_MODE_HBLANK;

                // Now render a scanline
            }
            break;
        case PPU_MODE_HBLANK:
            if (ppu->clockcount >= 204)
            {
                ppu->clockcount = 0;
                ppu->line++;

                if (ppu->line >= PPU_HLINES - 1)
                {
                    ppu->line = 0;
                    ppu->mode = PPU_MODE_VBLANK;
                    
                    // Draw to screen
                }
                else
                {
                    ppu->mode = PPU_MODE_OAM;
                }
            }
            break;
        case PPU_MODE_VBLANK:
            if (ppu->clockcount += 456)
            {
                ppu->clockcount = 0;
                ppu->line++;

                if (ppu->line >= PPU_VLINES)
                {
                    ppu->mode = PPU_MODE_OAM;
                    ppu->line = 0;
                }
            }
            break;
    }
}
