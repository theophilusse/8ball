#include "user_interface.h"

void            int_copy(void *in, void *out)
{
    if (!in || !out)
        return ;
    *((int *)in) = *((int *)out);
}
