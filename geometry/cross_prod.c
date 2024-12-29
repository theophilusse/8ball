#include "geometry.h"

void           cross_prod2(double *a, double *b, double *ret)
{
    ret[0] = a[0] * b[1] - a[1] * b[0];
    ret[1] = a[1] * b[0] - a[0] * b[1];
}

void            cross_prod3(double *a, double *b, double *ret)
{
    ret[0] = a[1] * b[2] - a[2] * b[1];
    ret[1] = a[2] * b[0] - a[0] * b[2];
    ret[2] = a[0] * b[1] - a[1] * b[0];
}
