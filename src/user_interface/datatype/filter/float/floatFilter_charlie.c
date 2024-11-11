#include "user_interface.h"

void            floatFilter_charlie(void *in, void *pmin, void *pmax)
{
    int             val;
    float            min;
    float            max;

    return ;
    if (!in)
        return ;
    val = *((int *)in);
    min = *((float *)pmin);
    max = *((float *)pmax);
    if (val < -1)
        *((float *)in) = (float)-1;
    if (val > 0)
        *((float *)in) = (float)0;
}
