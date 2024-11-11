#include "user_interface.h"

void            ui_releaseAssets(t_ui_assets *assets)
{
    if (!assets)
        return ;
    if (assets->spKill)
        SDL_FreeSurface(assets->spKill);
    assets->spKill = NULL;
    if (assets->cross)
        SDL_FreeSurface(assets->cross);
    assets->cross = NULL;
    if (assets->button_on)
        SDL_FreeSurface(assets->button_on);
    assets->button_on = NULL;
    if (assets->button_off)
        SDL_FreeSurface(assets->button_off);
    assets->button_off = NULL;
    if (assets->grid)
        SDL_FreeSurface(assets->grid);
    assets->grid = NULL;
    if (assets->scroller)
        SDL_FreeSurface(assets->scroller);
    assets->scroller = NULL;
    if (assets->arrow_u)
        SDL_FreeSurface(assets->arrow_u);
    assets->arrow_u = NULL;
        if (assets->arrow_r)
        SDL_FreeSurface(assets->arrow_r);
    assets->arrow_r = NULL;
    if (assets->arrow_l)
        SDL_FreeSurface(assets->arrow_l);
    assets->arrow_l = NULL;
    if (assets->arrow_d)
        SDL_FreeSurface(assets->arrow_d);
    assets->arrow_d = NULL;
    if (assets->save)
        SDL_FreeSurface(assets->save);
    assets->save = NULL;

    if (assets->bye)
        SDL_FreeSurface(assets->bye);
    assets->bye = NULL;
    if (assets->azerty)
        SDL_FreeSurface(assets->azerty);
    assets->azerty = NULL;
    if (assets->nagscreen)
        SDL_FreeSurface(assets->nagscreen);
    assets->nagscreen = NULL;
}
