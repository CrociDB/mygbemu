#include "ppu.h"
#include "log.h"

#include <memory.h>

ppu_t* ppu_create(mmu_t* mmu)
{
    log_message("Creating PPU");

    ppu_t* ppu = (ppu_t*)malloc(sizeof(ppu_t));
    ppu->vram = mmu->vram;
    ppu->oam = mmu->oam;

    ppu->control = mmu->ppu;

    ppu->mode = PPU_MODE_OAM;
    ppu->clockcount = 0;

    ppu->scroll_y = mmu->ppu + 0x02;
    ppu->scroll_x = mmu->ppu + 0x03;
    ppu->line = mmu->ppu + 0x04;
    ppu->window_y = mmu->ppu + 0x0a;
    ppu->window_x = mmu->ppu + 0x0b;

    ppu->scroll_x->value = ppu->scroll_y->value = ppu->line->value = 0;

    ppu->colors[0] = 0xFFFFFFFF;
    ppu->colors[1] = 0xFFC0C0C0;
    ppu->colors[2] = 0xFF606060;
    ppu->colors[3] = 0xFF000000;

    // Init framebuffer
    ppu->canrender = true;
    ppu_reset_framebuffer(ppu);

    memset(ppu->tileset, 0, sizeof(ppu->tileset));

    return ppu;
}

void ppu_destroy(ppu_t* ppu)
{
    free(ppu);
    ppu = NULL;
}

void ppu_update_memory(ppu_t* ppu, mmu_t* mmu)
{
    if (mmu->last_written.empty) return;

    if (mmu->last_written.addr == 0xFF47)
    {
        // Update palette
        ppu->palette[3] = (mmu->last_written.d8 & 0xc0) >> 6;
        ppu->palette[2] = (mmu->last_written.d8 & 0x30) >> 4;
        ppu->palette[1] = (mmu->last_written.d8 & 0x0c) >> 2;
        ppu->palette[0] = (mmu->last_written.d8 & 0x03);
        mmu->last_written.empty = true;
    }
    else if (mmu->last_written.addr >= 0x8000 && mmu->last_written.addr < 0xA000)
    {
        // Update tileset
        ppu_update_tile(ppu, mmu->last_written.addr, mmu->last_written.d8);
        mmu->last_written.empty = true;
    }
}

void ppu_update_tile(ppu_t* ppu, uint16_t addr, uint8_t data)
{
    uint16_t vaddr = addr & 0x1FFE;
    uint16_t index = (vaddr >> 4);
    uint8_t y = (vaddr >> 1) & 7;

    uint8_t v = data;
    uint8_t v1 = ppu->vram[vaddr + 1];

    uint8_t sx, x;

    for (x = 0; x < 8; x++)
    {
        sx = 1 << (7 - x);
        ppu->tileset[index][y][x] = (v & sx ? 1 : 0) + (v1 & sx ? 2 : 0);
    }
}

void ppu_tick(ppu_t* ppu, cpu_t* cpu, mmu_t* mmu)
{
    ppu_update_memory(ppu, mmu);
    //if (!ppu->control->lcd_display) return;

    ppu->clockcount += cpu->currclock.t;

    switch (ppu->mode)
    {
        case PPU_MODE_OAM:
            if (ppu->clockcount >= (uint16_t)(PPU_TIMES[0] * PPU_SCALE))
            {
                ppu->clockcount %= (uint16_t)(PPU_TIMES[0] * PPU_SCALE);
                ppu->mode = PPU_MODE_VRAM;
            }
            break;
        case PPU_MODE_VRAM:
            if (ppu->clockcount >= (uint16_t)(PPU_TIMES[1] * PPU_SCALE))
            {
                ppu->clockcount %= (uint16_t)(PPU_TIMES[1] * PPU_SCALE);
                ppu->mode = PPU_MODE_HBLANK;

                ppu_render_line(ppu, mmu);
            }
            break;
        case PPU_MODE_HBLANK:
            if (ppu->clockcount >= (uint16_t)(PPU_TIMES[2] * PPU_SCALE))
            {
                ppu->clockcount %= (uint16_t)(PPU_TIMES[2] * PPU_SCALE);
                ppu->line->value++;

                if (ppu->line->value == PPU_HLINES)
                {
                    ppu->mode = PPU_MODE_VBLANK;
                    ppu->canrender = true;
                    (*mmu->intflags) |= CPU_INT_VBLANK;
                }
                else
                {
                    ppu->mode = PPU_MODE_OAM;
                }
            }
            break;
        case PPU_MODE_VBLANK:
            if (ppu->clockcount >= (uint16_t)(PPU_TIMES[3] * PPU_SCALE))
            {
                ppu->clockcount %= (uint16_t)(PPU_TIMES[3] * PPU_SCALE);
                ppu->line->value++;
                

                if (ppu->line->value >= PPU_VLINES)
                {
                    //log_message("[PPU] Leaving VBLANK");
                    ppu->mode = PPU_MODE_OAM;
                    ppu->line->value = 0;
                }
            }
            break;
    }
}

void ppu_render_line(ppu_t* ppu, mmu_t* mmu)
{
    uint16_t mapoffset = ppu->control->bg_win_tiledata_select ? 0x1C00 : 0x1800;
    mapoffset += (((ppu->line->value + ppu->scroll_y->value) & 255) >> 3) << 5;

    uint8_t lineoffset = (ppu->scroll_x->value >> 3);

    uint8_t y = (ppu->line->value + ppu->scroll_y->value) & 7;
    
    uint8_t x;
    int8_t tile;
    uint32_t color;

    for (x = 0; x < PPU_BUFFER_WIDTH; x++)
    {
        tile = (int8_t)ppu->vram[mapoffset + lineoffset + (x / 8)];
        if (ppu->control->bg_tilemap_select && tile < 128) tile += 0x100;

        if (tile != 0)
        {
            int a = 0;
        }

        color = ppu->colors[ppu->palette[ppu->tileset[tile][y][x % 8]]];
        ppu->framebuffer[ppu->line->value][x] = color;
    }
}

void ppu_reset_framebuffer(ppu_t* ppu)
{
    memset(ppu->framebuffer, 0, PPU_BUFFER_HEIGHT * PPU_BUFFER_WIDTH * sizeof(uint32_t));
}
