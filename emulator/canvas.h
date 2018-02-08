#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>

#include "ppu.h"

#define CANVAS_DEBUG_WINDOW_W   810
#define CANVAS_DEBUG_WINDOW_H   600

#define CANVAS_DEBUG_TILE_PAD   10
#define CANVAS_DEBUG_SCALE      3

typedef struct _canvas_t
{
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    SDL_Event event_handler;

    // Debug
    SDL_Window* dbg_window;
    SDL_Renderer* dbg_renderer;
    bool dbg_draw;

    bool running;
} canvas_t;

canvas_t* canvas_init();
void canvas_destroy(canvas_t* canvas);

void canvas_event_loop(canvas_t* canvas);
void canvas_update(canvas_t* canvas, ppu_t* ppu);
void canvas_update_debug(canvas_t* canvas, ppu_t* ppu);

#endif
