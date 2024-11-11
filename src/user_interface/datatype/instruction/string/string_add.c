#include "user_interface.h"

void            string_add(void *in, void *out)
{
    size_t            len;

    if (!in || !out)
            return ;
    len = strlen((const char *)in);
    strncat(out, in, STRING_SIZE - len);
}
