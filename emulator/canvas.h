#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <SDL.h>

#define CANVAS_BUFFER_WIDTH    160
#define CANVAS_BUFFER_HEIGHT   144

typedef struct _canvas_t
{
    SDL_Window* window;
    SDL_Surface* surface;
} canvas_t;

canvas_t* canvas_init();
void canvas_destroy(canvas_t* canvas);

#endif
