#include "memmgr.h"

void             *mem_setCell_force(t_memPage *page, t_memCell *cell, size_t sz)
{
    t_memHeader      *dHead;

    if (!page || !cell)
        return (NULL);
    if (cell->lid + 1 >= (uint)page->info.sz)
        page->isFull = 1;
    dHead = CELL_ALLOC(sz);
    dHead->cellType = 0;
    dHead->srcCell = (void *)cell;
    dHead->sz = sz;
    cell->ptr = dHead;
    return ((void *)cell->ptr + sizeof(struct s_memHeader));
}

void             *mem_setCell(t_memPage *page, t_memCell *cell, size_t sz)
{
    t_memHeader      *dHead;

    if (!page || !cell || page->isFull == 1)
        return (NULL);
    if (cell->lid + 1 >= (uint)page->info.sz)
        page->isFull = 1;
    dHead = CELL_ALLOC(sz);
    dHead->cellType = 0;
    dHead->srcCell = (void *)cell;
    dHead->sz = sz;
    cell->ptr = dHead;
    return ((void *)cell->ptr + sizeof(struct s_memHeader));
}
