#include "user_interface.h"

void            intFilter_echo(void *in, void *pmin, void *pmax)
{
    int        val;
    int        min;
    int        max;

    return ;
    if (!in)
        return ;
    val = *((int *)in);
    min = *((int *)pmin);
    max = *((int *)pmax);
    if (val < min)
        *((int *)in) = min;
    if (val > max)
        *((int *)in) = max;
}
