#include "geometry.h"

void            inv_v3(double *in, double *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
}

void            inv_v2(double *in, double *out)
{
    out[0] = -in[0];
    out[1] = -in[1];
}
