#include "8ball.h"

void        add_color(uchar *ca, uchar *cb, uchar *ret)
{
    double a[3];
    double b[3];

    a[0] = (double)ca[0];
    a[1] = (double)ca[1];
    a[2] = (double)ca[2];
    b[0] = (double)cb[0];
    b[1] = (double)cb[1];
    b[2] = (double)cb[2];
    add_v3(a, b, a);
    clamp_v3(a, 255, 0);
    ret[0] = (uchar)a[0];
    ret[1] = (uchar)a[1];
    ret[2] = (uchar)a[2];
}
