#include "mmu.h"

mmu_t* mmu_create()
{
    log_message("Creating MMU");

    mmu_t* mmu = (mmu_t*)malloc(sizeof(mmu_t));
    mmu->joyflags = mmu->addr + 0xFF00;
    mmu->intflags = mmu->addr + 0xFF0F;

#ifdef _DEBUG_MEM
    // This will fill memory with specific values for each "block"
    memset(mmu->addr, 0xAA, sizeof(mmu->addr));
    memset(mmu->rom, 0x11, sizeof(mmu->rom));
    memset(mmu->vram, 0x22, sizeof(mmu->vram));
    memset(mmu->eram, 0x33, sizeof(mmu->eram));
    memset(mmu->wram, 0x44, sizeof(mmu->wram));
    memset(mmu->wrams, 0xBB, sizeof(mmu->wrams));
    memset(mmu->oam, 0x55, sizeof(mmu->oam));
    memset(mmu->empty, 0x66, sizeof(mmu->empty));
    memset(mmu->io, 0x77, sizeof(mmu->io));
    memset(mmu->zram, 0x88, sizeof(mmu->zram));
#endif

    return mmu;
}

void mmu_destroy(mmu_t* mmu)
{
    free(mmu);
    mmu = NULL;
}

void mmu_load_rom(mmu_t* mmu, cartridge_t* cartridge)
{
    memcpy((void*)mmu->addr, (const void*)cartridge->rom, cartridge->size);
}

void mmu_load_bios(mmu_t* mmu)
{
    memcpy((void*)mmu->bios, (const void*)BIOS, sizeof(BIOS));
    mmu->inbios = true;
}

// Reading routines

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
                        return mmu->intenable;
                    else
                    {
                        // Memory-mapped IO
                        switch (addr & 0x00F0)
                        {
                            case 0x00:
                                return mmu->io[addr & 0xFF];

                            // PPU
                            case 0x40: case 0x50: case 0x60: case 0x70:
                                return mmu->ppu[addr - 0xFF40];

                            case 0x80: case 0x90: case 0xA0: case 0xB0:
                            case 0xC0: case 0xD0: case 0xE0: case 0xF0:
                                return mmu->zram[addr & 0x7F];
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
    if (mmu->inbios && addr >= 0x00 && addr <= 0xFF)
        return mmu->bios[addr];

    return *(mmu->addr + addr);
}

uint16_t mmu_read_addr16(mmu_t* mmu, uint16_t addr)
{
    return *((uint16_t*)(mmu->addr + addr));
}


// Writing routines

/**
  * Return list:
  *   0 - did not write
  *   1 - wrote to vram
  *   2 - wrote to eram
  *   3 - wrote to wram
  *   4 - wrote to wram shadow
  *   5 - wrote to oam
  *   6 - wrote to io
  *   7 - wrote to ppu regs
  *   8 - wrote to zram
  *   0xA - wrote to intenable
  */
uint8_t mmu_write_byte(mmu_t* mmu, uint16_t addr, uint8_t data)
{
    if (mmu->inbios && addr >= 0x00 && addr <= 0xFF)
        return 0;

    mmu->last_written.addr = addr;
    mmu->last_written.d8 = data;

    switch ((addr & 0xF000) >> 12)
    {
        // ROM BANKS are read only
        case 0x0: case 0x1: case 0x2: case 0x3:
        case 0x4: case 0x5: case 0x6: case 0x7:
            return 0;

        // Video RAM
        case 0x8:
        case 0x9:
            mmu->vram[addr - 0x8000] = data;
            return 1;

        // External RAM
        case 0xA:
        case 0xB:
            mmu->eram[addr - 0xA000] = data;
            return 2;

        // Working RAM
        case 0xC:
        case 0xD:
            mmu->wram[addr - 0xC000] = data;
            return 3;

        // Working RAM Shadow
        case 0xE:
            mmu->wram[addr - 0xC000] = data;
            return 4;

        case 0xF:
            switch (addr & 0x0F00)
            {
                // More Working RAM Shadow
                case 0x000: case 0x100: case 0x200: case 0x300:
                case 0x400: case 0x500: case 0x600: case 0x700:
                case 0x800: case 0x900: case 0xA00: case 0xB00:
                case 0xC00: case 0xD00:
                    mmu->wram[addr - 0x1FFF] = data;
                    return 4;

                // Sprite information
                case 0xE00:
                    if (addr < 0xFEA0)
                    {
                        mmu->oam[addr & 0xFF] = data;
                        return 5;
                    }
                    else
                    {
                        return 0;
                    }

                case 0xF00:
                    if (addr == 0xFFFF)
                    {
                        mmu->intenable = data;
                        return 0xA;
                    }
                    else
                    {
                        // Memory-mapped IO
                        switch (addr & 0x00F0)
                        {
                            case 0x00:
                                mmu->io[addr & 0xFF] = data;
                                return 6;

                             // PPU
                            case 0x40: case 0x50: case 0x60: case 0x70:
                                mmu->ppu[addr - 0xFF40] = data;
                                return 7;

                            case 0x80: case 0x90: case 0xA0: case 0xB0:
                            case 0xC0: case 0xD0: case 0xE0: case 0xF0:
                                mmu->zram[addr & 0x7F] = data;
                                return 8;
                        }
                    }
            }
    }
}

uint8_t mmu_write_word(mmu_t* mmu, uint16_t addr, uint16_t data)
{
    uint8_t r = mmu_write_byte(mmu, addr, data & 0xFF) & mmu_write_byte(mmu, addr + 1, data >> 8);
    mmu->last_written.addr = addr;
    mmu->last_written.d16 = data;
    return r;
}

void mmu_write_addr8(mmu_t* mmu, uint16_t addr, uint8_t data)
{
    mmu->last_written.addr = addr;
    mmu->last_written.d8 = data;
    return mmu->addr[addr] = data;
}

void mmu_write_addr16(mmu_t* mmu, uint16_t addr, uint16_t data)
{
    mmu->last_written.addr = addr;
    mmu->last_written.d16 = data;
    uint16_t* pos = ((uint16_t*)(mmu->addr + addr));
    return *pos = data;
}
