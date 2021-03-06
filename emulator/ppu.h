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

#define PPU_BUFFER_WIDTH    160
#define PPU_BUFFER_HEIGHT   144

#define PPU_HLINES          143
#define PPU_VLINES          153

static const uint16_t PPU_TIMES[4] = { 80, 172, 204, 456};
static const float PPU_SCALE = 1.0f;

typedef struct __ppu_reg_t
{
    uint8_t value;
} _ppu_reg_t;

typedef struct _ppu_t
{
    uint8_t mode:2;
    uint32_t clockcount;

    struct
    {
        union
        {
            uint8_t value;
            struct
            {
                bool lcd_display:1;
                bool window_tilemap_select:1;
                bool window_display:1;
                bool bg_win_tiledata_select:1;
                bool bg_tilemap_select:1;
                bool sprite_size:1;
                bool sprite_display:1;
                bool bg_win_priority:1;
            };
        };
    } *control;
    
    _ppu_reg_t* scroll_y;
    _ppu_reg_t* scroll_x;
    _ppu_reg_t* line;
    _ppu_reg_t* window_y;
    _ppu_reg_t* window_x;

    uint32_t colors[4];
    uint8_t palette[4];
    uint8_t tileset[0x200][8][8];

    bool canrender;
    uint32_t framebuffer[PPU_BUFFER_HEIGHT][PPU_BUFFER_WIDTH];

    uint8_t* vram;
    uint8_t* oam;
} ppu_t;

ppu_t* ppu_create(mmu_t* mmu);
void ppu_destroy(ppu_t* ppu);

void ppu_update_memory(ppu_t* ppu, mmu_t* mmu);
void ppu_update_tile(ppu_t* ppu, uint16_t addr, uint8_t data);
void ppu_tick(ppu_t* ppu, cpu_t* cpu, mmu_t* mmu);
void ppu_render_line(ppu_t* ppu, mmu_t* mmu);
void ppu_reset_framebuffer(ppu_t* ppu);

#endif
