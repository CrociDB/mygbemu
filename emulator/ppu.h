#ifndef _PPU_H_
#define _PPU_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "mmu.h"
#include "cpu.h"

#define PPU_MODE_OAM        2
#define PPU_MODE_VRAM       3
#define PPU_MODE_HBLANK     0
#define PPU_MODE_VBLANK     1

#define PPU_HLINES          144
#define PPU_VLINES          154

typedef struct _ppu_t
{
    uint8_t mode:2;
    uint16_t clockcount;
    uint8_t line;

    uint8_t* vram;
    uint8_t* oam;
} ppu_t;

ppu_t* ppu_create(mmu_t* mmu);
void ppu_destroy(ppu_t* ppu);

void ppu_tick(ppu_t* ppu, cpu_t* cpu, mmu_t* mmu);

#endif
