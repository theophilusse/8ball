#include "user_interface.h"

void            doubleFilter_alfa(void *in, void *pmin, void *pmax)
{
    double        val;
    double        min;
    double        max;

    if (!in)
        return ;
    if (val < 0)
        *((double *)in) = 0;
    if (val > 1)
        *((double *)in) = 1;
}
