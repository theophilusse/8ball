#include "user_interface.h"

void            float_add(void *val, void *out)
{
    if (!out)
        return ;
    *((float *)out) = *((float *)out) + *((float *)val);
}
