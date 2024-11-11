#include "user_interface.h"

void            float_copy(void *in, void *out)
{
    if (!in || !out)
        return ;
    *((float *)in) = *((float *)out);
}
