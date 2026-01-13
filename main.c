#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/color.h"

#define WIDTH 1000
#define HEIGHT 800
#define PEN_SIZE 10
#define RUBBER_SIZE 40

#define FPS 60
#define DELAY (1.0 / FPS) * 1000

#define distance(inix, iniy, x, y)                                            \
    (sqrt (pow (inix - x, 2) + pow (iniy - y, 2)))


typedef struct
{
    int x, y;
} coords;


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


// int
// rubber (SDL_Window *window, SDL_Surface *surface, coords *pos, Uint32 color)
// {
//     SDL_Rect rect = { pos->x, pos->y, RUBBER_SIZE, RUBBER_SIZE };

//     if (SDL_FillRect (surface, &rect, color))
//     {
//         fprintf (stderr, "[x] rubber error: %s\n", SDL_GetError ());
//         return EXIT_FAILURE;
//     }

//     if (SDL_UpdateWindowSurface (window))
//     {
//         fprintf (stderr, "[x] rubber update error: %s\n", SDL_GetError ());
//         return EXIT_FAILURE;
//     }

//     return EXIT_SUCCESS;
// }


int
draw (SDL_Window *window, SDL_Surface *surface, coords *pos, int pen_size,
      Uint32 color)
{
    if (draw_circle (surface, pos->x, pos->y, pen_size, color))
    {
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
setup_default_surface (SDL_Window *window, SDL_Surface *surface)
{
    if (SDL_FillRect (surface, NULL, BACKGROUND))
    {
        fprintf (stderr, "[x] default setup error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    if (SDL_UpdateWindowSurface (window))
    {
        fprintf (stderr, "[x] update error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


void
change_pen (SDL_Event *event, Uint32 *color, int *pen_size)
{
    switch (event->key.keysym.sym)
    {
    case SDLK_0:
        *pen_size = RUBBER_SIZE;
        *color = BACKGROUND;
        break;
    case SDLK_1:
        *color = RED;
        break;
    case SDLK_2:
        *color = GREEN;
        break;
    case SDLK_3:
        *color = BLUE;
        break;
    case SDLK_4:
        *color = WHITE;
        break;
    case SDLK_5:
        *color = YELLOW;
        break;
    case SDLK_6:
        *color = PINK;
    }
}


int
app (SDL_Window *window, SDL_Surface *surface)
{
    int running = 1;
    int drawing = 0;

    coords pos = {};
    Uint32 color = RED;
    int pen_size = PEN_SIZE;

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
            case SDL_KEYDOWN:
                if (event.key.keysym.sym >= SDLK_0
                    && event.key.keysym.sym <= SDLK_9)
                {
                    change_pen (&event, &color, &pen_size);
                }
                break;

            case SDL_MOUSEMOTION:
                pos.x = event.motion.x;
                pos.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                drawing = 1;
                pos.x = event.motion.x;
                pos.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONUP:
                drawing = 0;
            }
        }

        if (drawing)
        {
            if (draw (window, surface, &pos, pen_size, color))
            {
                return EXIT_FAILURE;
            }
            // SDL_Delay (DELAY);
        }
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

    if (app (window, surface))
    {
        return EXIT_FAILURE;
    }

    SDL_DestroyWindow (window);
    SDL_Quit ();
    return 0;
}
