#include "canvas.h"
#include "sys.h"

canvas_t* canvas_init()
{
    canvas_t* canvas = (canvas_t*)malloc(sizeof(canvas_t));

    // Init video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        sys_error("Couldn't init video. SDL Error: %s", SDL_GetError());
    }
    
    canvas->window = SDL_CreateWindow(
        "MyGBEmu",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        CANVAS_BUFFER_WIDTH,
        CANVAS_BUFFER_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (canvas->window == NULL)
    {
        sys_error("Couldn't create window. SDL Error: %s", SDL_GetError());
    }

    canvas->surface = SDL_GetWindowSurface(canvas->window);

    return canvas;
}
