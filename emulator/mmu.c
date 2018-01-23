#include "mmu.h"

mmu_t* mmu_create()
{
    mmu_t* mmu = (mmu_t*)malloc(sizeof(mmu_t));
    mmu->addr = mmu->rom;
    return mmu;
}

void mmu_insert_rom(mmu_t* mmu, cartridge_t* cartridge)
{
    memcpy((void*)mmu->addr, (const void*)cartridge->rom, cartridge->size);
}

uint8_t mmu_read_byte(mmu_t * mmu, uint16_t addr)
{
    if (mmu->inbios && addr >= 0x00 && addr <= 0xFF)
        return mmu->bios[addr];

    // Read fragmented memory
    switch ((addr & 0xF000) >> 12)
    {
        // ROM BANK 0
        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
            return mmu->rom[0][addr];

        // ROM BANK 1
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
            return mmu->rom[1][addr - 0x4000];

        // Video RAM
        case 0x8:
        case 0x9:
            return mmu->vram[addr - 0x8000];

        // External RAM
        case 0xA:
        case 0xB:
            return mmu->eram[addr - 0xA000];

        // Working RAM
        case 0xC:
        case 0xD:
            return mmu->wram[addr - 0xC000];

        // Working RAM Shadow
        case 0xE:
            return mmu->wram[addr - 0xC000];

        case 0xF:
            switch (addr & 0x0F00)
            {
                // More Working RAM Shadow
                case 0x000: case 0x100: case 0x200: case 0x300:
                case 0x400: case 0x500: case 0x600: case 0x700:
                case 0x800: case 0x900: case 0xA00: case 0xB00:
                case 0xC00: case 0xD00:
                    return mmu->wram[addr - 0x1FFF];

                // Sprite information
                case 0xE00:
                    if (addr < 0xFEA0)
                        return mmu->oam[addr & 0xFF];
                    else
                        return 0;

                case 0xF00:
                    if (addr == 0xFFFF)
                        return 0; // This is something with the last interruption. TODO later
                    else
                    {
                        // Memory-mapped IO
                        switch (addr & 0x00F0)
                        {
                            case 0x00:
                                if (addr == 0xFF00)
                                    return mmu->joyflags;
                                if (addr == 0XFF0F)
                                    return 0; // This is the flags of the last interruption. TODO later

                            // GPU
                            case 0x40: case 0x50: case 0x60: case 0x70:
                                return 0; // Read GPU registers. TODO later

                            case 0x80: case 0x90: case 0xA0: case 0xB0:
                            case 0xC0: case 0xD0: case 0xE0: case 0xF0:
                                return mmu->zram[addr & 0x7f];
                        }
                    }
            }
    }

    return ;
}

uint16_t mmu_read_word(mmu_t * mmu, uint16_t addr)
{
    return (mmu_read_byte(mmu, addr) | (mmu_read_byte(mmu, addr + 1) << 8));
}

uint8_t mmu_read_addr8(mmu_t* mmu, uint16_t addr)
{
    return *(mmu->addr + addr);
}

uint16_t mmu_read_addr16(mmu_t* mmu, uint16_t addr)
{
    return *((uint16_t*)(mmu->addr + addr));
}
