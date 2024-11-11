#include "alphabet_tileset.h"

/**
 ** free_tileset :
 ** Dealocate 256 SDL_Surface then free
 ** the table (tileset).
 **
**/
void            free_tileset(SDL_Surface **tileset)
{
    int         i;

    if (!tileset)
        return ;
    i = -1;
    while (++i < 256)
        if (tileset[i])
            SDL_FreeSurface(tileset[i]);
    FREE(tileset);
}
