#include "canvas.h"
#include "sys.h"

canvas_t* canvas_init()
{
    log_message("Creating Canvas Module");

    canvas_t* canvas = (canvas_t*)malloc(sizeof(canvas_t));

    // Init video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        sys_error("Couldn't init video. SDL Error: %s", SDL_GetError());
    }
    
    canvas->scale = 2;
    canvas->window = SDL_CreateWindow(
        "MyGBEmu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        PPU_BUFFER_WIDTH * canvas->scale,
        PPU_BUFFER_HEIGHT * canvas->scale,
        SDL_WINDOW_SHOWN);

    if (canvas->window == NULL)
    {
        sys_error("Couldn't create window. SDL Error: %s", SDL_GetError());
    }

    canvas->dbg_window = SDL_CreateWindow(
        "Debug",
        300,
        SDL_WINDOWPOS_CENTERED,
        CANVAS_DEBUG_WINDOW_W,
        CANVAS_DEBUG_WINDOW_H,
        SDL_WINDOW_SHOWN);

    if (canvas->dbg_window == NULL)
    {
        sys_error("Couldn't create debug window. SDL Error: %s", SDL_GetError());
    }

    canvas->renderer = SDL_CreateRenderer(canvas->window, -1, SDL_RENDERER_ACCELERATED);
    canvas->dbg_renderer = SDL_CreateRenderer(canvas->dbg_window, -1, SDL_RENDERER_SOFTWARE);
    canvas->dbg_draw = false;
    canvas->running = true;

    SDL_RenderSetScale(canvas->renderer, canvas->scale, canvas->scale);
    SDL_RenderSetScale(canvas->dbg_renderer, CANVAS_DEBUG_SCALE, CANVAS_DEBUG_SCALE);

    return canvas;
}

void canvas_destroy(canvas_t* canvas)
{
    SDL_DestroyRenderer(canvas->renderer);
    canvas->renderer = NULL;
    SDL_DestroyWindow(canvas->window);
    canvas->window = NULL;

    SDL_Quit();

    free(canvas);
    canvas = NULL;
}

void canvas_event_loop(canvas_t* canvas)
{
    while (SDL_PollEvent(&canvas->event_handler) != 0)
    {
        if (canvas->event_handler.type == SDL_WINDOWEVENT)
        {
            if (canvas->event_handler.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                canvas->running = false;
            }
        }
        if (canvas->event_handler.type == SDL_QUIT)
        {
            canvas->running = false;
        }
        else if (canvas->event_handler.type == SDL_KEYDOWN)
        {
            if (canvas->event_handler.key.keysym.sym == SDLK_SPACE)
            {
                canvas->dbg_draw = true;
            }
        }
    }
}

void canvas_update(canvas_t* canvas, ppu_t* ppu)
{
    canvas_update_debug(canvas, ppu);

    if (ppu->canrender)
    {
        /*static c = 0;
        log_message("[CANVAS] Printing to screen: %d", c++);*/

        int x, y;
        for (y = 0; y < PPU_BUFFER_HEIGHT; y++)
        {
            for (x = 0; x < PPU_BUFFER_WIDTH; x++)
            {
                int col = ppu->framebuffer[y][x];

                SDL_SetRenderDrawColor(canvas->renderer, col >> 16, col >> 8, col, 0xff);
                SDL_RenderDrawPoint(canvas->renderer, x, y);
            }
        }

        ppu->canrender = false;
        ppu_reset_framebuffer(ppu);
        SDL_RenderPresent(canvas->renderer);
    }
}

void canvas_update_debug(canvas_t* canvas, ppu_t* ppu)
{
    if (!canvas->dbg_draw) return;

    canvas->dbg_draw = false;

    SDL_Rect rect = { 0, 0, CANVAS_DEBUG_WINDOW_W, CANVAS_DEBUG_WINDOW_H };
    SDL_SetRenderDrawColor(canvas->dbg_renderer, 33, 88, 22, 0xff);
    SDL_RenderFillRect(canvas->dbg_renderer, &rect);

    int y, x;

    int i;
    for (i = 0; i < 0x200; i++)
    {
        for (y = 0; y < 8; y++)
        {
            for (x = 0; x < 8; x++)
            {
                int col = ppu->colors[ppu->palette[ppu->tileset[i][y][x]]];

                uint16_t wx = ((i % (CANVAS_DEBUG_WINDOW_W / (CANVAS_DEBUG_TILE_PAD * CANVAS_DEBUG_SCALE)))) * CANVAS_DEBUG_TILE_PAD + (CANVAS_DEBUG_TILE_PAD / CANVAS_DEBUG_SCALE / 2);
                uint16_t wy = ((i / (CANVAS_DEBUG_WINDOW_W / (CANVAS_DEBUG_TILE_PAD * CANVAS_DEBUG_SCALE)))) * CANVAS_DEBUG_TILE_PAD + (CANVAS_DEBUG_TILE_PAD / CANVAS_DEBUG_SCALE / 2);
                
                SDL_SetRenderDrawColor(canvas->dbg_renderer, col >> 16, col >> 8, col & 0xff, 0xff);
                SDL_RenderDrawPoint(canvas->dbg_renderer, x + wx, y + wy);
            }
        }
    }
    
    SDL_RenderPresent(canvas->dbg_renderer);
}
