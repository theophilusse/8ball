#include "HeightMap.h"

int         on_surface(SDL_Surface *s, int *click)
{
    struct SDL_Rect        clip_rect;

    if (!click || !s)
        return (0);
    clip_rect = s->clip_rect;
    if (click[0] >= clip_rect.x && click[0] < (clip_rect.x + clip_rect.w) &&
        click[1] >= clip_rect.y && click[1] < (clip_rect.y + clip_rect.h))
        return (1);
    return (0);
}
