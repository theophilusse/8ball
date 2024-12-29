#include "sdl_util.h"

void            clean_surface(SDL_Surface *surface)
{
    /*uint            i;
    uint            j;
    uchar           color[4] = { 0, 0, 0, 0 };*/

    if (!surface)
        return ;
    SDL_FillRect(surface, NULL, 0x000000);
    ///SDL_FillRect(surface, NULL, *((Uint32 *)color));
    //set_alpha(surface, SDL_ALPHA_TRANSPARENT); // TODO REMETTRE
    return ;
}
