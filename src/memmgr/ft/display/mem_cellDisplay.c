#include "memmgr.h"

void     mem_cellDisplay(t_memCell *cell)
{
    char        c[2] = { 'O', 'X' };

    if (!cell)
        return ;
    printf("-(%u:%c)", cell->lid, cell->ptr ? c[1] : c[0]);
}