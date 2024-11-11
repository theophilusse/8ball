#include "user_interface.h"

void            uint_add(void *val, void *out)
{
    if (!out)
        return ;
    *((uint *)out) = *((uint *)out) + *((uint *)val);
}
