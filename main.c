#include <SDL2/SDL.h>
#include <stdlib.h>

#include "include/app.h"


int
main (void)
{
    SDL_Window *window = set_window ();

    if (!window)
    {
        return EXIT_FAILURE;
    }

    if (app (window))
    {
        return EXIT_FAILURE;
    }

    SDL_DestroyWindow (window);
    SDL_Quit ();

    return EXIT_SUCCESS;
}
