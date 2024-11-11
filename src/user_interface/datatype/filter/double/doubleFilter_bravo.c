#include "user_interface.h"

void            doubleFilter_bravo(void *in, void *pmin, void *pmax)
{
    double         val;

    if (!in)
        return ;
    val = *((double *)in);
    if ((double)val < 0)
        *((double *)in) = 0;
}
