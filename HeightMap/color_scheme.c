#include "HeightMap.h"

void            color_height(uchar *color, double *h)
{
    double       height;

    if (!color || !h)
        return ;
    height = *h;
    if (height > 0 && height < 255)
    {
        if (height >= 0 && height < 64) // Blue
        {
            color[0] = 0;
            color[1] += (uchar)((double)height * 4);
            //color[1] += adj < 1024 ? (uchar)((double)height * 4);
            color[2] = 255;
        }
        if (height >= 64 && height < 128)
        {
            color[0] = 0;
            color[1] = 255;
            color[2] = 255 - (uchar)(((double)height - 64) * 4);
        }
        if (height >= 128 && height < 192)
        {
            color[0] += (uchar)(((double)height - 128) * 4);
            color[1] = 255;
            color[2] = 0;
        }
        if (height >= 192 && height < 255)
        {
            color[0] = 255;
            color[1] += 255 - (uchar)(((double)height - 192) * 4);
            color[2] = 0;
        }
        return ;
    }
    color[0] = 121;
    color[1] = 45;
    color[2] = 147;
}

void            color_scheme(uchar *color, int i, void *data)
{
    if (color)
    {
        color[0] = DEFAULT_R;
        color[1] = DEFAULT_G;
        color[2] = DEFAULT_B;
        color[3] = DEFAULT_A;
    }
    if (!color || i < 0 || i > N_COLOR_SCHEME)
        return ;
    switch (i)
    {
        case 0: color_height(color, (double *)data); break;
    }
}
