#include "user_interface.h"

void            doubleFilter_foxtrot(void *in, void *pmin, void *pmax)
{
    double        val;
    double        min;
    double        max;

    if (!in || !pmin || !pmax)
        return ;
    val = *((double *)in);
    min = *((double *)pmin);
    max = *((double *)pmax);
    if (val < min)
        *((double *)in) = min;
    if (val > max)
        *((double *)in) = max;
}
