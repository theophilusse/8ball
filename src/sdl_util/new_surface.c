#include "sdl_util.h"

//Uint32          rmask, gmask, bmask, amask;

SDL_Surface             *new_surface32(uint width, uint height)
{
    SDL_Surface         *pSurf;
    SDL_Surface         *pRet;

    /*** crmask
    if (!(ret = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, 16, 16, 32, crmask, cgmask, cbmask, camask))) /// Old
    if (!(urf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, 16, 16, 32, rmask, gmask, bmask, amask)))
    ***/ /// COMP
    if (!(pSurf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, (int)width, (int)height, 32, rmask, gmask, bmask, amask)))
        return (NULL);
    ///
    //SDL_SetAlpha(pSurf, SDL_SRCALPHA | SDL_RLEACCEL , SDL_ALPHA_OPAQUE);
    SDL_SetAlpha(pSurf, SDL_SRCALPHA | SDL_RLEACCEL , SDL_ALPHA_OPAQUE);
    pRet = SDL_DisplayFormatAlpha(pSurf);
    SDL_FreeSurface(pSurf);
    return (pRet);
    ///
    return (pSurf);
}
