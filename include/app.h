#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "pen.h"
#include "window.h"

#define FPS 60
#define DELAY (1.0 / FPS) * 1000


int app (SDL_Window *window);


int
app (SDL_Window *window)
{
    SDL_Surface *surface = SDL_GetWindowSurface (window);

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
            if (draw (surface, &pos, pen_size, color))
            {
                return EXIT_FAILURE;
            }

            if (SDL_UpdateWindowSurface (window))
            {
                fprintf (stderr, "[x] draw error: %s\n", SDL_GetError ());
                return EXIT_FAILURE;
            }
            SDL_Delay (DELAY);
        }
    }

    return EXIT_SUCCESS;
}

