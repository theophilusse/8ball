#include "user_interface.h"

void            uint_get(void *in, char *out)
{
    uint        val;
    int         val_;

    if (!in || !out)
        return ;
    val = *((uint *)in);
    val_ = (int)val;
    itoa(val_, out, 10);
}
