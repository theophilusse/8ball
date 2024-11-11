#include "sdl_util.h"

void        square_dim(SDL_Surface *s, int x, int y, int w, int h, uchar *rgb, int *maxDim, int *minDim)
{
    int     i;
    int     j;

    if (w < 1 || h < 1)
        return ;
    j = -1;
    while (++j < h)
    {
        i = -1;
        while (++i < w)
            put_pixel_dim(s, rgb, x + i, y + j, maxDim, minDim);
    }
}

void        square_dim_noAlpha(SDL_Surface *s, int x, int y, int w, int h, uchar *rgb, int *maxDim, int *minDim)
{
    int     i;
    int     j;

    if (w < 1 || h < 1)
        return ;
    j = -1;
    while (++j < h)
    {
        i = -1;
        while (++i < w)
            put_pixel_dim_noAlpha(s, rgb, x + i, y + j, maxDim, minDim);
    }
}
