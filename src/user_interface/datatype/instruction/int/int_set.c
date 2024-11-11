#include "user_interface.h"

void            int_set(char *in, void *out)
{
    if (!in || !out)
        return ;
    *((int *)out) = (int)atoi(in);
}
