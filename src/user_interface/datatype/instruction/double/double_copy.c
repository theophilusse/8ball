#include "user_interface.h"

void            double_copy(void *in, void *out)
{
    if (!in || !out)
        return ;
    *((double *)in) = *((double *)out);
}
