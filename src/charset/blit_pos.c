#include "alphabet_tileset.h"

/**
 ** blit_pos :
 ** Write a single tile on screen at position X and Y.
 ** Used for charset_print function.
**/
void                 blit_pos(SDL_Surface *image, SDL_Surface *screen, int x, int y)
{
    SDL_Rect    src = {0, 0, (Uint16)image->w, (Uint16)image->h};
    SDL_Rect    dst;
    Uint16      _x;
    Uint16      _y;

    _x = (Uint16)x;
    _y = (Uint16)y;
    dst.x = _x;
    dst.y = _y;
    SDL_BlitSurface(image, &src, screen, &dst);
}
