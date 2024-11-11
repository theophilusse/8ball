#include "HeightMap.h"

int         click_area(int *click, int *cx, int *cy, int x, int y, int w, int h)
{
    if (!click)
        return (0);
    if (click[0] >= x && click[0] < w + x && click[1] >= y && click[1] < h + y)
    {
        if (x < 0)
            *cx = (x * -1) + click[0];
        else
            *cx = click[0] - x;
        if (y < 0)
            *cy = (y * -1) + click[1];
        else
            *cy = click[1] - y;
        return (1);
    }
    else
        return (0);
}
