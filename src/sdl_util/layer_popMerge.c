#include "sdl_util.h"

///SDL_Surface *layer_popMerge(SDL_Surface **layer_stack, int sz, void (*func)(SDL_Surface *, SDL_Surface *)) /// Recursive test
SDL_Surface *layer_popMerge(SDL_Surface **__restrict__ layer_stack, int sz, void (*func)(SDL_Surface *, SDL_Surface *)) /// Recursive test
{
    int            i;

    sz--;
    i = -1;
    while (++i < sz)
        func(*layer_stack, layer_stack[i + 1]);
    return (*layer_stack);
}
