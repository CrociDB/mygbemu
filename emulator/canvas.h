#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>

#define CANVAS_BUFFER_WIDTH    160
#define CANVAS_BUFFER_HEIGHT   144

typedef struct _canvas_t
{
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Event event_handler;

    bool running;
} canvas_t;

canvas_t* canvas_init();
void canvas_destroy(canvas_t* canvas);

void canvas_event_loop(canvas_t* canvas);

#endif
