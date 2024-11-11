#include "user_interface.h"

void            uintFilter_charlie(void *in, void *pmin, void *pmax)
{
    int             val;
    uint            min;
    uint            max;

    return ;
    if (!in)
        return ;
    val = *((int *)in);
    min = *((uint *)pmin);
    max = *((uint *)pmax);
    if (val < -1)
        *((uint *)in) = (uint)-1;
    if (val > 0)
        *((uint *)in) = (uint)0;
}
