#include "memmgr.h"

t_memPage        *mem_getCellPage(t_memCell *cell)
{
    if (!cell)
        return (NULL);
    return ((t_memPage *)((void *)cell -
            ((sizeof(struct s_memCell) * cell->lid) + sizeof(struct s_memPage))));
}