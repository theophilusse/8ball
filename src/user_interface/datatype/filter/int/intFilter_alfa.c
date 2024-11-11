#include "user_interface.h"

void            intFilter_alfa(void *in, void *pmin, void *pmax)
{
    int        val;
    int        min;
    int        max;

    if (!in)
        return ;
    if (val < 0)
        *((int *)in) = 0;
    if (val > 1)
        *((int *)in) = 1;
}
