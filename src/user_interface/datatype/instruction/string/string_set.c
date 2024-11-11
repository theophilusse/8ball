#include "user_interface.h"

void            string_set(char *in, void *out)
{
    int             val;

    if (!in || !out)
        return ;
    strncpy((char *)out, (const char *)in, STRING_SIZE);
}
