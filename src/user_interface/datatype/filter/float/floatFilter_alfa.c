#include "user_interface.h"

void            floatFilter_alfa(void *in, void *pmin, void *pmax)
{
    float        val;
    float        min;
    float        max;

    if (!in)
        return ;
    if (val < 0)
        *((float *)in) = 0;
    if (val > 1)
        *((float *)in) = 1;
}
