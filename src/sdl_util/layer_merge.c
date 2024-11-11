#include "sdl_util.h"

/**
 ** Note: It WILL crash if frameBuffer_stack has an empty SDL_Surface *pointer in his list.
*/
SDL_Surface *layer_merge(SDL_Surface **layer_stack, int sz, void (*func)(SDL_Surface *, SDL_Surface *)) /// Recursive test
{
    if (--sz > 0) /// Stop condition.
        func(*layer_stack, layer_merge(layer_stack + 1, sz, func));
    return (*layer_stack);
}
