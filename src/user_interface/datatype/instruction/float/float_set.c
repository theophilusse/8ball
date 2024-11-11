#include "user_interface.h"

void            float_set(char *in, void *out)
{
    if (!in || !out)
        return ;
    *((float *)out) = (float)atof(in);
}
