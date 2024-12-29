#include "geometry.h"

double           dot_prod3(double *a, double *b)
{
    double           c;

    c = a[0] * b[0];
    c += a[1] * b[1];
    c += a[2] * b[2];
    return (c);
}

double           dot_prod2(double *a, double *b)
{
    double           c;

    c = a[0] * b[0];
    c += a[1] * b[1];
    return (c);
}
