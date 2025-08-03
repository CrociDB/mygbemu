#include "canvas.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "log.h"
#include "sys.h"

canvas_t* canvas_init()
{
  log_message("Creating Canvas Module");

  canvas_t* canvas = (canvas_t*)malloc(sizeof(canvas_t));

  // Init video
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    sys_error("Couldn't init video. SDL Error: %s", SDL_GetError());
  }

#ifdef CANVAS_THREAD
  log_message("Creating Canvas thread");
  canvas->init_mutex = SDL_CreateMutex();
  canvas->thread =
      SDL_CreateThread(_canvas_thread_update, "canvas_thread", (void*)canvas);

  // This mutex will make sure the window is properly initiated before
  // continuing
  SDL_Delay(10);
  SDL_LockMutex(canvas->init_mutex);
  SDL_UnlockMutex(canvas->init_mutex);
  SDL_DestroyMutex(canvas->init_mutex);
#else
  _canvas_initialize_windows(canvas);
#endif

  return canvas;
}

void _canvas_initialize_windows(canvas_t* canvas)
{
#ifdef CANVAS_THREAD
  SDL_LockMutex(canvas->init_mutex);
#endif

  canvas->scale = 2;
  canvas->window = SDL_CreateWindow("MyGBEmu", PPU_BUFFER_WIDTH * canvas->scale,
                                    PPU_BUFFER_HEIGHT * canvas->scale,
                                    SDL_EVENT_WINDOW_SHOWN);

  if (canvas->window == NULL)
  {
    sys_error("Couldn't create window. SDL Error: %s", SDL_GetError());
  }

  canvas->dbg_window =
      SDL_CreateWindow("Debug", CANVAS_DEBUG_WINDOW_W, CANVAS_DEBUG_WINDOW_H,
                       SDL_EVENT_WINDOW_SHOWN);

  if (canvas->dbg_window == NULL)
  {
    sys_error("Couldn't create debug window. SDL Error: %s", SDL_GetError());
  }

  canvas->renderer = SDL_CreateRenderer(canvas->window, NULL);
  if (!canvas->renderer)
  {
    sys_error("Couldn't create renderer: %s", SDL_GetError());
  }

  canvas->dbg_renderer = SDL_CreateRenderer(canvas->dbg_window, NULL);
  if (!canvas->dbg_renderer)
  {
    sys_error("Couldn't create renderer: %s", SDL_GetError());
  }

  canvas->dbg_draw = false;
  canvas->running = true;

  SDL_SetRenderScale(canvas->renderer, canvas->scale, canvas->scale);
  SDL_SetRenderScale(canvas->dbg_renderer, CANVAS_DEBUG_SCALE,
                     CANVAS_DEBUG_SCALE);

#ifdef CANVAS_THREAD
  SDL_UnlockMutex(canvas->init_mutex);
#endif
}

void canvas_destroy(canvas_t* canvas)
{
#ifdef CANVAS_THREAD
  int status;
  SDL_WaitThread(canvas->thread, &status);
  log_message("Canvas thread finished with status: %d", status);
#endif

  SDL_DestroyRenderer(canvas->renderer);
  canvas->renderer = NULL;
  SDL_DestroyWindow(canvas->window);
  canvas->window = NULL;

  SDL_Quit();

  free(canvas);
  canvas = NULL;
}

int _canvas_thread_update(void* data)
{
  canvas_t* canvas = (canvas_t*)data;
  _canvas_initialize_windows(canvas);

  while (canvas->running)
  {
    _canvas_event_loop(canvas);
  }

  return 0;
}

void canvas_event_loop(canvas_t* canvas)
{
#ifndef CANVAS_THREAD
  _canvas_event_loop(canvas);
#endif
}

void _canvas_event_loop(canvas_t* canvas)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
      canvas->running = false;
    }
    else if (event.type == SDL_EVENT_QUIT)
    {
      canvas->running = false;
    }
    else if (event.type == SDL_EVENT_KEY_DOWN)
    {
      if (event.key.key == SDLK_SPACE)
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

        SDL_SetRenderDrawColor(canvas->renderer, col >> 16, col >> 8, col,
                               0xff);
        if (!SDL_RenderPoint(canvas->renderer, x, y))
        {
          log_message("ERROR RENDERING %s", SDL_GetError());
        }
      }
    }

    ppu->canrender = false;
    ppu_reset_framebuffer(ppu);
    SDL_RenderPresent(canvas->renderer);
  }
}

void canvas_update_debug(canvas_t* canvas, ppu_t* ppu)
{
  if (!canvas->dbg_draw)
    return;

  canvas->dbg_draw = false;

  SDL_Rect rect = {0, 0, CANVAS_DEBUG_WINDOW_W, CANVAS_DEBUG_WINDOW_H};
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

        uint16_t wx = ((i % (CANVAS_DEBUG_WINDOW_W /
                             (CANVAS_DEBUG_TILE_PAD * CANVAS_DEBUG_SCALE)))) *
                          CANVAS_DEBUG_TILE_PAD +
                      (CANVAS_DEBUG_TILE_PAD / CANVAS_DEBUG_SCALE / 2);
        uint16_t wy = ((i / (CANVAS_DEBUG_WINDOW_W /
                             (CANVAS_DEBUG_TILE_PAD * CANVAS_DEBUG_SCALE)))) *
                          CANVAS_DEBUG_TILE_PAD +
                      (CANVAS_DEBUG_TILE_PAD / CANVAS_DEBUG_SCALE / 2);

        SDL_SetRenderDrawColor(canvas->dbg_renderer, col >> 16, col >> 8,
                               col & 0xff, 0xff);
        SDL_RenderPoint(canvas->dbg_renderer, x + wx, y + wy);
      }
    }
  }

  SDL_RenderPresent(canvas->dbg_renderer);
}
