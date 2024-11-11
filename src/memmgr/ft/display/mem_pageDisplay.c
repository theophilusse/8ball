#include "memmgr.h"

void     mem_pageDisplay(t_memPage *page)
{
    uint            i;
    t_memCell       *cell;

    printf("[");
    if (page /*&& page->def.datatype != UI_DATATYPE_POINTER*/)
    {
        cell = (t_memCell *)((void *)page + sizeof(struct s_memPage));
        i = -1;
        while (++i < page->info.sz)
        {
            mem_cellDisplay(cell);
            cell++;
        }
    }
    printf("]\n");
}