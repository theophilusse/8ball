#include "user_interface.h"

void            floatFilter_delta(void *in, void *pmin, void *pmax)
{
    float        val;
    float        min;
    float        max;

    /*
     * Deadcode .
    */
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
