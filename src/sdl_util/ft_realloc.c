#include "sdl_util.h"

void         *ft_realloc(void *src, size_t bSz, size_t new_bSz)
{
    void            *ret;

    if (new_bSz == 0 ||
        !(ret = ALLOC(new_bSz)))
    {
        if (src)
            FREE(src);
        return (NULL);
    }
    if (new_bSz <= bSz)
        memcpy(ret, src, new_bSz);
    else
    {
        memcpy(ret, src, bSz);
        memset(ret + bSz, 0, new_bSz - bSz);
    }
    FREE(src);
    return (ret);
}
