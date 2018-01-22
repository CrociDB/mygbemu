#ifndef _MMU_H_
#define _MMU_H_

#define MEMORY_ADDRESSES 65536

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "cartridge.h"

typedef struct _mmu_t
{
    bool inbios;
    uint8_t addr[MEMORY_ADDRESSES];
} mmu_t;

mmu_t* mmu_create();
void mmu_insert_rom(mmu_t* mmu, cartridge_t* cartridge);

uint8_t mmu_read_addr8(mmu_t* mmu, uint16_t addr);
uint16_t mmu_read_addr16(mmu_t* mmu, uint16_t addr);

#endif
