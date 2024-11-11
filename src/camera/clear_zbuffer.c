#include "camera.h"

/**
 ** clear_zbuffer :
 ** Reset zbuffer to DBL_MAX (clean).
 ** Takes a double pointer to your zbuffer of
 ** width w and height h, of length (w * h) * 4.
 **
**/
void            clear_zbuffer(double *zbuffer, int w, int h)
{
    int             i;
    int             j;

    if (!zbuffer)
        return;
    i = -1;
    j = (h * w) * 4;
    while (++i < j)
        zbuffer[i] = DBL_MAX;
}