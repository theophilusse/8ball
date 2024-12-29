#include "HeightMap.h"

int         click_surface(SDL_Surface *s, int *click, int *cx, int *cy)
{
    int                     tmp;
    struct SDL_Rect        clip_rect;

    if (!click || !s)
        return (0);
    clip_rect = s->clip_rect;
    if (click[0] >= clip_rect.x && click[0] < (clip_rect.x + clip_rect.w) &&
        click[1] >= clip_rect.y && click[1] < (clip_rect.y + clip_rect.h))
    {
        if (cx)
        {
            tmp = click[0];
            if (clip_rect.x < 0)
                *cx = (clip_rect.x * -1) + tmp;
            else
                *cx = tmp - clip_rect.x;
        }
        if (cy)
        {
            tmp = click[1];
            if (clip_rect.y < 0)
                *cy = (clip_rect.y * -1) + tmp;
            else
                *cy = tmp - clip_rect.y;
        }
        //printf("Touch at [%d][%d]\n", click[0], click[1]);
        return (1);
    }
    return (0);
}
