#include "user_interface.h"

void            floatFilter_echo(void *in, void *pmin, void *pmax)
{
    float        val;
    float        min;
    float        max;

    return ;
    if (!in)
        return ;
    val = *((float *)in);
    min = *((float *)pmin);
    max = *((float *)pmax);
    if (val < min)
        *((float *)in) = min;
    if (val > max)
        *((float *)in) = max;
}
