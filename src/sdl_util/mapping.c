#include "sdl_util.h"

uint            getpixel_index(SDL_Surface *surface, int x, int y)
{
    int         bpp;

    if (x < 0 || y < 0)
        return (0);
    if (!surface || x >= surface->w || y >= surface->h)
        return (0);
    bpp = surface->pitch / surface->w;
    return (y * surface->pitch + x * bpp);
}

void            *getpixel_addr(SDL_Surface *surface, int x, int y)
{
    int         bpp;

    if (x < 0 || y < 0)
        return (NULL);
    if (!surface || x >= surface->w || y >= surface->h)
        return (NULL);
    bpp = surface->pitch / surface->w;
    ///printf("Gp:[%p]\n", surface->pixels); /// DEBUG /// ponc_space->pixels == NULL
    return ((Uint8 *)surface->pixels + y * surface->pitch + x * bpp);
}

void    put_pixel_dim(SDL_Surface *s, uchar *rgb, int x, int y, int *maxDim, int *minDim)
{
    uchar *pixl;

    if (!s)
    {
        return ;
    }
    if (maxDim)
    {
        if (maxDim[0] <= x)
            return ;
        if (maxDim[1] <= y)
            return ;
    }
    if (minDim)
    {
        if (minDim[0] > x)
            return ;
        if (minDim[1] > y)
            return ;
    }
    if (!(pixl = (uchar *)getpixel_addr(s, x, y)))
        return ;
    *pixl = *rgb;
    *(pixl + 1) = *(rgb + 1);
    *(pixl + 2) = *(rgb + 2);
    *(pixl + 3) = *(rgb + 3);
}

void    put_pixel_dim_noAlpha(SDL_Surface *s, uchar *rgb, int x, int y, int *maxDim, int *minDim)
{
    uchar *pixl;

    if (!s)
    {
        return ;
    }
    if (maxDim)
    {
        if (maxDim[0] <= x)
            return ;
        if (maxDim[1] <= y)
            return ;
    }
    if (minDim)
    {
        if (minDim[0] > x)
            return ;
        if (minDim[1] > y)
            return ;
    }
    if (!(pixl = (uchar *)getpixel_addr(s, x, y)))
        return ;

    *pixl = *rgb;
    *(pixl + 1) = *(rgb + 1);
    *(pixl + 2) = *(rgb + 2);
    /*
    *pixl = *(rgb + 2);
    *(pixl + 1) = *(rgb + 1);
    *(pixl + 2) = *rgb;
    */
}

////void    put_pixel_rgba(SDL_Surface *s, uchar *rgba, int x, int y)
void    put_pixel(SDL_Surface *s, uchar *rgb, int x, int y)
{
    uchar *pixl;

    /*
    if (!s)
    {
        return ;
    }*/
    if (!(pixl = (uchar *)getpixel_addr(s, x, y)))
        return ;
    *pixl = *rgb;
    *(pixl + 1) = *(rgb + 1);
    *(pixl + 2) = *(rgb + 2);
    *(pixl + 3) = *(rgb + 3);
}

void    put_pixel_noAlpha(SDL_Surface *s, uchar *rgb, int x, int y)
{
    uchar *pixl;

    if (!s)
    {
        return ;
    }
    if (!(pixl = (uchar *)getpixel_addr(s, x, y)))
        return ;
    *pixl = *rgb;
    *(pixl + 1) = *(rgb + 1);
    *(pixl + 2) = *(rgb + 2);
}
