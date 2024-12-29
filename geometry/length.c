#include "geometry.h"

double           length3(const double *v)
{
    double       tmp;

    if ((tmp = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])) < 0)
        tmp *= -1.0;
    return (sqrt(tmp));
}

double           length2(const double *v)
{
    double       tmp;

    if ((tmp = (v[0] * v[0]) + (v[1] * v[1])) < 0)
        tmp *= -1.0;
    return (sqrt(tmp));}

double           fast_length3(const double *v)
{
    double       tmp;

    if ((tmp = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])) < 0)
        tmp *= -1.0;
    return (tmp);
}

double           fast_length2(const double *v)
{
    double       tmp;

    if ((tmp = (v[0] * v[0]) + (v[1] * v[1])) < 0)
        tmp *= -1.0;
    return (tmp);
}
