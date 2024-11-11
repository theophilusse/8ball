#include "geometry.h"

void            clamp_v3(double *v, int max_value, int min_value)
{
    if (v[0] > max_value)
        v[0] = max_value;
    if (v[1] > max_value)
        v[1] = max_value;
    if (v[2] > max_value)
        v[2] = max_value;

    if (v[0] < min_value)
        v[0] = min_value;
    if (v[1] < min_value)
        v[1] = min_value;
    if (v[2] < min_value)
        v[2] = min_value;
}
