#include "user_interface.h"

void            uintFilter_alfa(void *in, void *pmin, void *pmax)
{
    uint        val;
    uint        min;
    uint        max;

    if (!in)
        return ;
    if (val < 0)
        *((uint *)in) = 0;
    if (val > 1)
        *((uint *)in) = 1;
}
