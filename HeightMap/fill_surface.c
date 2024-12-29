#include "HeightMap.h"

void                fill_surface(SDL_Surface *s, uchar *color)
{
    SDL_Rect        clip_rect;
    int             i;
    int             j;

    if (!s)
        return ;
    j = -1;
    clip_rect = s->clip_rect;
    while (++j < clip_rect.h)
    {
        i = -1;
        while (++i < clip_rect.w)
            put_pixel(s, color, i, j);
    }
}
