#include "memmgr.h"

void            page_set_empty_cells(t_memPage *page)
{
    t_memCell           *cel;
    size_t              sz;
    size_t              i;

    if (!page)
        return ;
    cel = (t_memCell *)((void *)page + sizeof(struct s_memPage));
    sz = page->info.sz;
    i = 0;
    while (i < sz)
    {
        cel->ptr = NULL;
        cel->lid = i;
        cel++;
        i++;
    }
}