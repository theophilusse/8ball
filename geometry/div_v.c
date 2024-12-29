#include "geometry.h"

void        div_v2(const double *a, const double *b, double *ret)
{
    if (b[0] == 0 || b[1] == 0)
        return ;
    ret[0] = a[0] / b[0];
    ret[1] = a[1] / b[1];
}

void        div_v3(const double *a, const double *b, double *ret)
{
    if (b[0] == 0 || b[1] == 0 || b[2] == 0)
        return ;
    ret[0] = a[0] / b[0];
    ret[1] = a[1] / b[1];
    ret[2] = a[2] / b[2];
}

void        div_v3_by(const double *a, const double b, double *ret)
{
    if (b == 0)
        return ;
    ret[0] = a[0] / b;
    ret[1] = a[1] / b;
    ret[2] = a[2] / b;
}
