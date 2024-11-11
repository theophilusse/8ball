#include "user_interface.h"

void            uintFilter_foxtrot(void *in, void *pmin, void *pmax)
{
    uint        val;
    uint        min;
    uint        max;

    if (!in || !pmin || !pmax)
        return ;
    val = *((uint *)in);
    min = *((uint *)pmin);
    max = *((uint *)pmax);
    if (val < min)
        *((uint *)in) = min;
    if (val > max)
        *((uint *)in) = max;
}
