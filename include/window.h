#pragma once

#include <SDL2/SDL.h>

#include "color.h"

#define WIDTH 1000
#define HEIGHT 800


int setup_default_surface (SDL_Window *window, SDL_Surface *surface);
SDL_Window *set_window ();


SDL_Window *
set_window ()
{
    SDL_Window *window = NULL;

    if (SDL_Init (SDL_INIT_VIDEO))
    {
        fprintf (stderr, "[x] init error: %s\n", SDL_GetError ());
        return NULL;
    }

    window = SDL_CreateWindow ("cpaint", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    if (window == NULL)
    {
        fprintf (stderr, "[x] window error: %s\n", SDL_GetError ());
        return NULL;
    }

    SDL_Surface *surface = SDL_GetWindowSurface (window);

    if (surface == NULL)
    {
        fprintf (stderr, "[x] surface error: %s\n", SDL_GetError ());
        return NULL;
    }

    if (setup_default_surface (window, surface))
    {
        return NULL;
    }

    return window;
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
        fprintf (stderr, "[x] default setup error: %s\n", SDL_GetError ());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


