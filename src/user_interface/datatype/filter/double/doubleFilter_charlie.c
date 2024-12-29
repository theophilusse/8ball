#include "user_interface.h"

void            doubleFilter_charlie(void *in, void *pmin, void *pmax)
{
    double             val;
    //double            min;
    //double            max;

    return ;
    if (!in)
        return ;
    val = *((double *)in);
    //min = *((double *)pmin);
    //max = *((double *)pmax);
    if (val < -1)
        *((double *)in) = (double)-1;
    if (val > 0)
        *((double *)in) = (double)0;
}
