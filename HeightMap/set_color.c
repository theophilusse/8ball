#include "HeightMap.h"

int         set_color4(uchar *dst, uchar *src)
{
    if (!dst)
        return (-1);
    if (!src)
    {
        dst[0] = DEFAULT_R;
        dst[1] = DEFAULT_G;
        dst[2] = DEFAULT_B;
        dst[3] = DEFAULT_A;
        return (1);
    }
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    return (0);
}
