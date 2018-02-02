#ifndef _PPU_H_
#define _PPU_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "mmu.h"

typedef struct _ppu_t
{
    uint8_t* vram;
    uint8_t* oam;
} ppu_t;

ppu_t* ppu_create(mmu_t* mmu);
void ppu_destroy(ppu_t* ppu);

#endif
