#include "memmgr.h"

t_memCell           *mem_getPageCell(t_memPage *page)
{
    if (!page)
        return (NULL);
    return ((t_memCell *)((void *)page + sizeof(struct s_memPage)));
}
