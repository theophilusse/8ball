#include "user_interface.h"

void            float_get(void *in, char *out)
{
    if (!in || !out)
        return ;
    dtoa(out, *((float *)in));
}
