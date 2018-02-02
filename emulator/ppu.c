#include "ppu.h"
#include "log.h"

ppu_t* ppu_create(mmu_t* mmu)
{
    log_message("Creating PPU");

    ppu_t* ppu = (ppu_t*)malloc(sizeof(ppu_t));
    ppu->vram = mmu->vram;
    ppu->oam = mmu->oam;

    return ppu;
}

void ppu_destroy(ppu_t* ppu)
{
    free(ppu);
    ppu = NULL;
}
