#include "memmgr.h"

void            my_free(void *ptr)
{
    struct s_memHeader      mHead;
    t_memCell               *cell;
    t_memPage               *page;

    if (!ptr)
        return ;
    if (!(cell = mem_getDataCell(ptr)))
        return ;
    if (!(page = mem_getCellPage(cell)))
        return ;
    if (page->info.sz == cell->lid + 1)
        page->isFull = 0;
    CELL_FREE(cell->ptr);
    cell->ptr = NULL;
    if (cell->lid = 0)
        mem_removePage(page);
}
