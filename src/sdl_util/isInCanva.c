#include "sdl_util.h"

int      isInCanva(SDL_Surface *canva, int *px, int *py, int isInt)
{
    double         dx;
    double         dy;
    int            x;
    int            y;

    if (!canva || !px || !py)
        return (0);
    if (isInt)
    {
        x = *px - canva->clip_rect.x;
        y = *py - canva->clip_rect.y;
        if (x < 0 || y < 0)
            return (0);
        if (y > canva->clip_rect.h || x > canva->clip_rect.w)
            return (0);
        return (1);
    }
    dx = *((double *)px) - (double)canva->clip_rect.x;
    dy = *((double *)py) - (double)canva->clip_rect.y;
    if (dx < 0 || dy < 0)
        return (0);
    if ((int)dy > canva->clip_rect.h || (int)dx > canva->clip_rect.w)
        return (0);
    return (1);
}
