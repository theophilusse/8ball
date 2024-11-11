#include "8ball.h"

void         mtp_color(uchar *color, double f)
{
    int         i;
    double      c[3];

    i = -1;
    while (++i < 3)
    {
        if ( (c[i] = (double)color[i] * f ) > 255)
            c[i] = 255;
        if (c[i] < 0)
            c[i] = 0;
    }
    color[0] = (uchar)c[0];
    color[1] = (uchar)c[1];
    color[2] = (uchar)c[2];
}
