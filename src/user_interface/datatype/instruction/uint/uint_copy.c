#include "user_interface.h"

void            uint_copy(void *in, void *out)
{
    if (!in || !out)
        return ;
    *((uint *)in) = *((uint *)out);
}
