#include "user_interface.h"

void            intFilter_bravo(void *in, void *pmin, void *pmax)
{
    int         val;

    if (!in)
        return ;
    val = *((int *)in);
    if ((int)val < 0)
        *((int *)in) = 0;
}
