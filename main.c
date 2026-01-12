#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define FPS 60
#define DELAY (1.0 / FPS) * 1000


int
main (int argc, char **argv)
{
    SDL_Window *window = NULL;

    if (SDL_Init (SDL_INIT_VIDEO) != 0)
    {
        fprintf (stderr, "[x] init error: %s\n", SDL_GetError ());
        return 1;
    }

    window = SDL_CreateWindow ("cpaint", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if (window == NULL)
    {
        fprintf (stderr, "[x] window error: %s\n", SDL_GetError ());
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface (window);
    SDL_Rect rect = { 0, 0, 50, 50 };
    SDL_FillRect (surface, &rect, 0xFFFF00);
    SDL_UpdateWindowSurface (window);

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent (&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        SDL_Delay (DELAY);
    }

    SDL_DestroyWindow (window);
    SDL_Quit ();
    return 0;
}
