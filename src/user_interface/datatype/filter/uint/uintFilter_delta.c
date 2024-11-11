#include "user_interface.h"

void            uintFilter_delta(void *in, void *pmin, void *pmax)
{
    uint        val;
    uint        min;
    uint        max;

    /*
     * Deadcode .
    */
    return ;
    if (!in)
        return ;
    val = *((uint *)in);
    min = *((uint *)pmin);
    max = *((uint *)pmax);
    if (val < min)
        *((uint *)in) = min;
    if (val > max)
        *((uint *)in) = max;
}
