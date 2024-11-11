#include "geometry.h"

void        add_v3(double *a, double *b, double *ret)
{
    ret[0] = a[0] + b[0];
    ret[1] = a[1] + b[1];
    ret[2] = a[2] + b[2];
}

void        add_v2(const double *a, const double *b, double *ret)
{
    ret[0] = a[0] + b[0];
    ret[1] = a[1] + b[1];
}
