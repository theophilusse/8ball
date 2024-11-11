#include "user_interface.h"

void            double_get(void *in, char *out)
{
    if (!in || !out)
        return ;
    dtoa(out, *((double *)in));
}
