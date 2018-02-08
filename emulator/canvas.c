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
        PPU_BUFFER_WIDTH,
        PPU_BUFFER_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (canvas->window == NULL)
    {
        sys_error("Couldn't create window. SDL Error: %s", SDL_GetError());
    }

    canvas->surface = SDL_GetWindowSurface(canvas->window);
    canvas->renderer = SDL_CreateRenderer(canvas->window, -1, SDL_RENDERER_ACCELERATED);
    canvas->running = true;

    return canvas;
}

void canvas_destroy(canvas_t* canvas)
{
    SDL_FreeSurface(canvas->surface);
    canvas->surface = NULL;
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
    if (SDL_PollEvent(&canvas->event_handler) != 0)
    {
        if (canvas->event_handler.type == SDL_QUIT)
        {
            canvas->running = false;
        }
    }
}

void canvas_update(canvas_t* canvas, ppu_t* ppu)
{
    if (ppu->canrender)
    {
        int size = PPU_BUFFER_WIDTH * PPU_BUFFER_HEIGHT;
        int i;
        for (i = 0; i < size; i++)
        {
            int x = i / PPU_BUFFER_HEIGHT;
            int y = i % PPU_BUFFER_HEIGHT;

            int col = ppu->framebuffer[i];
            
            SDL_SetRenderDrawColor(canvas->renderer, col >> 16, col >> 8, col, 0xff);
            SDL_RenderDrawPoint(canvas->renderer, x, y);
        }

        ppu->canrender = false;
        SDL_RenderPresent(canvas->renderer);
    }
}
