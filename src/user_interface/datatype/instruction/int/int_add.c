#include "user_interface.h"

void            int_add(void *val, void *out)
{
    if (!out)
        return ;
    *((int *)out) = *((int *)out) + *((int *)val);
}
