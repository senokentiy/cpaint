#include <SDL2/SDL.h>

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1000
#define HEIGHT 800
#define PEN_SIZE 5
#define COLOR 0xFF0000

#define FPS 60
#define DELAY (1.0 / FPS) * 1000

#define distance(inix, iniy, x, y)                                            \
    (sqrt (pow (inix - x, 2) + pow (iniy - y, 2)))


int
draw_circle (SDL_Surface *surface, int inix, int iniy, int radius,
             Uint32 color)
{
    SDL_Rect pix = { 0, 0, 1, 1 };

    for (int x = 0; x < inix + radius; x++)
    {
        for (int y = 0; y < iniy + radius; y++)
        {
            if (distance (inix, iniy, x, y) < radius)
            {
                pix.x = x;
                pix.y = y;

                if (SDL_FillRect (surface, &pix, color))
                {
                    fprintf (stderr, "[x] fill error: %s\n", SDL_GetError ());
                    return EXIT_FAILURE;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}


int
draw (SDL_Window *window, SDL_Surface *surface, SDL_Event *event, Uint32 color)
{
    if (draw_circle (surface, event->motion.x, event->motion.y, PEN_SIZE,
                     color))
    {
        return EXIT_FAILURE;
    }

    // SDL_Rect rect = { event->motion.x, event->motion.y, 1, 1 };

    // if (SDL_FillRect (surface, &rect, color))
    // {
    //     fprintf (stderr, "[x] fill error: %s\n", SDL_GetError ());
    //     return EXIT_FAILURE;
    // }

    if (SDL_UpdateWindowSurface (window))
    {
        fprintf (stderr, "[x] update error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int
setup_default_surface (SDL_Window *window, SDL_Surface *surface)
{
    if (SDL_SetSurfaceColorMod (surface, 0xED, 0xED, 0xED))
    {
        fprintf (stderr, "[x] fill error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    if (SDL_UpdateWindowSurface (window))
    {
        fprintf (stderr, "[x] update error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int
main (int argc, char **argv)
{
    SDL_Window *window = NULL;

    if (SDL_Init (SDL_INIT_VIDEO))
    {
        fprintf (stderr, "[x] init error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow ("cpaint", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if (window == NULL)
    {
        fprintf (stderr, "[x] window error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    SDL_Surface *surface = SDL_GetWindowSurface (window);

    if (surface == NULL)
    {
        fprintf (stderr, "[x] surface error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    if (setup_default_surface (window, surface))
    {
        return EXIT_FAILURE;
    }

    int running = 1;

    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent (&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_MOUSEMOTION:
                if (draw (window, surface, &event, COLOR))
                {
                    return EXIT_FAILURE;
                }
            }
        }
        SDL_Delay (DELAY);
    }

    SDL_DestroyWindow (window);
    SDL_Quit ();
    return 0;
}
