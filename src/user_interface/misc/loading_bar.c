#include "user_interface.h"

void            loading_bar(SDL_Surface *surface, float from_percent, float percent)
{
    uchar           rgbBar[3];
    uint            dTo;
    uint            i;
    int            width;
    int            height;
    int             vPos[2];

    if (!surface || surface->h < 64 || percent > 1.0 || percent < 0.0)
        return ;
    width = surface->w;
    height = surface->h - 1;
    rgbBar[0] = 255;
    rgbBar[1] = 0;
    rgbBar[2] = 0;
    rgbBar[3] = 255;
    dTo = (uint)((float)surface->w * percent);
    vPos[0] = (uint)((float)surface->w * from_percent);;
    while (vPos[0] < dTo)
    {
        vPos[1] = height;
        i = -1;
        while (++i < 10)
            if (vPos[0] < width)
                put_pixel(surface, rgbBar, vPos[0], vPos[1] - i); //// CRASH !!!
        vPos[0]++;
    }
}
