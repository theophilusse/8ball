#include "user_interface.h"

void            floatFilter_foxtrot(void *in, void *pmin, void *pmax)
{
    float        val;
    float        min;
    float        max;

    if (!in || !pmin || !pmax)
        return ;
    val = *((float *)in);
    min = *((float *)pmin);
    max = *((float *)pmax);
    if (val < min)
        *((float *)in) = min;
    if (val > max)
        *((float *)in) = max;
}
