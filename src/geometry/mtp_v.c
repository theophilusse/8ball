#include "geometry.h"

void        mtp_v2(const double *a, const double *b, double *ret)
{
    ret[0] = a[0] * b[0];
    ret[1] = a[1] * b[1];
}

void        mtp_v2_by(const double *a, const double b, double *ret)
{
    ret[0] = a[0] * b;
    ret[1] = a[1] * b;
}

void        mtp_v3(const double *a, const double *b, double *ret)
{
    ret[0] = a[0] * b[0];
    ret[1] = a[1] * b[1];
    ret[2] = a[2] * b[2];
}

void        mtp_v3_by(const double *a, const double b, double *ret)
{
    ret[0] = a[0] * b;
    ret[1] = a[1] * b;
    ret[2] = a[2] * b;
}
