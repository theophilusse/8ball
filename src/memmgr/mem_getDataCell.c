#include "memmgr.h"

t_memCell        *mem_getDataCell(void *ptr)
{
    struct s_memHeader      mHead;
    t_memCell               *cell;

    if (!ptr)
        return (NULL);
    mHead = *((t_memHeader *)(ptr - sizeof(struct s_memHeader)));
    if (mHead.cellType != 0)
        return (NULL);
    if (!(cell = (t_memCell *)mHead.srcCell))
        return (NULL);
    return (cell);
}