#include "user_interface.h"

void            double_add(void *val, void *out)
{
    if (!out)
        return ;
    *((double *)out) = *((double *)out) + *((double *)val);
}
