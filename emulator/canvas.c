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
    canvas->running = true;

    return canvas;
}

void canvas_destroy(canvas_t* canvas)
{
    SDL_FreeSurface(canvas->surface);
    canvas->surface = NULL;
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
        if (canvas->event_handler.type == SDL_QUIT)
        {
            canvas->running = false;
        }
    }
}
