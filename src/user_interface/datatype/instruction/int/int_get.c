#include "user_interface.h"

void            int_get(void *in, char *out)
{
    if (!in || !out)
        return ;
    itoa(*((int *)in), out, 10);
}
