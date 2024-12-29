#include "geometry.h"

void           unit3(const double *v, double *ret, double *length)
{
    double          l;

    if (length)
        l = *length;
    else
        l = length3(v);
    if (l <= EPSILON)
        return ;
    ret[0] = v[0] / l;
    ret[1] = v[1] / l;
    ret[2] = v[2] / l;
}

void           unit2(const double *v, double *ret, double *length)
{
    double          l;

    if (length)
        l = *length;
    else
        l = length2(v);
    if (l <= EPSILON)
        return ;
    ret[0] = v[0] / l;
    ret[1] = v[1] / l;
}
