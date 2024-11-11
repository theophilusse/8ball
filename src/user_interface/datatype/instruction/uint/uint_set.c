#include "user_interface.h"

void            uint_set(char *in, void *out)
{
    int             val;

    if (!in || !out)
        return ;
    *((uint *)out) = (uint)atoi(in);
}
