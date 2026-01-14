#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "type.h"

#define PEN_SIZE 10
#define RUBBER_SIZE 40

#define distance(inix, iniy, x, y)                                            \
    (sqrt (pow (inix - x, 2) + pow (iniy - y, 2)))


int draw_circle (SDL_Surface *surface, int inix, int iniy, int radius,
                 Uint32 color);
int draw (SDL_Surface *surface, coords *pos, int pen_size, Uint32 color);
void change_pen (SDL_Event *event, Uint32 *color, int *pen_size);


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
                    fprintf (stderr, "[x] draw circle error: %s\n",
                             SDL_GetError ());
                    return EXIT_FAILURE;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}


int
draw (SDL_Surface *surface, coords *pos, int pen_size, Uint32 color)
{
    if (draw_circle (surface, pos->x, pos->y, pen_size, color))
    {
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
        *pen_size = PEN_SIZE;
        *color = RED;
        break;
    case SDLK_2:
        *pen_size = PEN_SIZE;
        *color = GREEN;
        break;
    case SDLK_3:
        *pen_size = PEN_SIZE;
        *color = BLUE;
        break;
    case SDLK_4:
        *pen_size = PEN_SIZE;
        *color = WHITE;
        break;
    case SDLK_5:
        *pen_size = PEN_SIZE;
        *color = YELLOW;
        break;
    case SDLK_6:
        *pen_size = PEN_SIZE;
        *color = PINK;
    }
}



