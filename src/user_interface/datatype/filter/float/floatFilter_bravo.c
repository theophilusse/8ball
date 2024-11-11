#include "user_interface.h"

void            floatFilter_bravo(void *in, void *pmin, void *pmax)
{
    int         val;

    if (!in)
        return ;
    val = *((float *)in);
    if ((float)val < 0)
        *((float *)in) = 0;
}
