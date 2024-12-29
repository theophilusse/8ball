#include "user_interface.h"

void            intFilter_charlie(void *in, void *pmin, void *pmax)
{
    int             val;
    //int            min;
    //int            max;

    return ;
    if (!in)
        return ;
    val = *((int *)in);
    //min = *((int *)pmin);
    //max = *((int *)pmax);
    if (val < -1)
        *((int *)in) = (int)-1;
    if (val > 0)
        *((int *)in) = (int)0;
}
