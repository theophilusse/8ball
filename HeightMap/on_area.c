#include "HeightMap.h"

int         on_area(int *click, int x, int y, int w, int h)
{
    if (!click)
        return (0);
    if (click[0] >= x && click[0] < w + x && click[1] >= y && click[1] < h + y)
        return (1);
    else
        return (0);
}
