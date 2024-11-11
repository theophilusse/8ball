#include "user_interface.h"

void            uintFilter_bravo(void *in, void *pmin, void *pmax)
{
    int         val;

    if (!in)
        return ;
    val = *((int *)in);
    if ((int)val < 0)
        *((uint *)in) = 0;
}
