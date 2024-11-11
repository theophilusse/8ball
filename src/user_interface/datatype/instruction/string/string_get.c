#include "user_interface.h"

void            string_get(void *in, char *out)
{
    uint        val;
    int         val_;

    if (!in || !out)
        return ;
    strncpy((char *)in, (const char *)out, STRING_SIZE);
}
