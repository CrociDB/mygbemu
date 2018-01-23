#ifndef _MMU_H_
#define _MMU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "cartridge.h"

typedef struct _mmu_t
{
    uint8_t* addr;
    struct
    {
        uint8_t bios[0xFF1];
        uint8_t rom[2][0x4000];
        uint8_t vram[0x2000];
        uint8_t eram[0x2000];
        uint8_t wram[0x2000];
        uint8_t oam[0xA0];
        uint8_t zram[0x7F];
        uint8_t joyflags;
        uint8_t intflags;
        uint8_t intenable;
    };

    bool inbios;
} mmu_t;

mmu_t* mmu_create();
void mmu_insert_rom(mmu_t* mmu, cartridge_t* cartridge);

uint8_t mmu_read_byte(mmu_t* mmu, uint16_t addr);
uint16_t mmu_read_word(mmu_t* mmu, uint16_t addr);

uint8_t mmu_read_addr8(mmu_t* mmu, uint16_t addr);
uint16_t mmu_read_addr16(mmu_t* mmu, uint16_t addr);

uint8_t mmu_write_byte(mmu_t* mmu, uint16_t addr, uint8_t data);
uint8_t mmu_write_word(mmu_t* mmu, uint16_t addr, uint16_t data);

void mmu_write_addr8(mmu_t* mmu, uint16_t addr, uint8_t data);
void mmu_write_addr16(mmu_t* mmu, uint16_t addr, uint16_t data);

#endif
