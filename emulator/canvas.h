#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "ppu.h"

// A specific thread for canvas is created if this is set
#define CANVAS_THREAD  1

#define CANVAS_DEBUG_WINDOW_W   810
#define CANVAS_DEBUG_WINDOW_H   600

#define CANVAS_DEBUG_TILE_PAD   10
#define CANVAS_DEBUG_SCALE      3

typedef struct _canvas_t
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event_handler;
    uint8_t scale;

    // Debug
    SDL_Window* dbg_window;
    SDL_Renderer* dbg_renderer;
    bool dbg_draw;

#ifdef CANVAS_THREAD
    SDL_Thread* thread;
    SDL_Mutex* init_mutex;
#endif

    bool running;
} canvas_t;

canvas_t* canvas_init();
static void _canvas_initialize_windows(canvas_t* canvas);
void canvas_destroy(canvas_t* canvas);

static int _canvas_thread_update(void* data);

void _canvas_event_loop(canvas_t* canvas);
void canvas_event_loop(canvas_t* canvas);

void canvas_update(canvas_t* canvas, ppu_t* ppu);
void canvas_update_debug(canvas_t* canvas, ppu_t* ppu);

#endif
