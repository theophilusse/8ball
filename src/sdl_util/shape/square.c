#include "sdl_util.h"

void        square(SDL_Surface *s, int x, int y, int w, int h, uchar *rgb)
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
            put_pixel(s, rgb, x + i, y + j); /// Keep ?
            ///put_pixel_dim(s, rgb, x + i, y + j, NULL, NULL); /// Crash ?
    }
}
