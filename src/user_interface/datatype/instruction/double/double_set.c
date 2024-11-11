#include "user_interface.h"

void            double_set(char *in, void *out)
{
    if (!in || !out)
        return ;
    *((double *)out) = atof(in);
}
