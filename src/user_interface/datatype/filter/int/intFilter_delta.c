#include "user_interface.h"

void            intFilter_delta(void *in, void *pmin, void *pmax)
{
    int        val;
    int        min;
    int        max;

    /*
     * Deadcode .
    */
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
