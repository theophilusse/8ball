#include "memmgr.h"

static void         page_set_matrix(double *m, uint sz, double value)
{
    uint i;

    if (!m)
        return ;
    i = -1;
    while (++i < sz)
        m[i] = value;
}

t_memPage       *mem_newPage(struct s_memPageDim dim)
{
    t_memPage               *pPage;
    t_memPage               *page;

    if (!(page = PAGE_ALLOC(dim)))
        return (NULL);
    page->chain.next = NULL;
    if ((pPage = mem_getRoot()))
    {
        while (pPage->chain.next)
            pPage = pPage->chain.next;
        pPage->chain.next = page;
    }
    page->chain.prev = pPage;
    page->info = dim;
    page->def.datatype = UI_DATATYPE_POINTER;
    page_set_matrix(page->def.identy, 4, 0);
    page_set_matrix(page->def.transf, 4, 0);
    page_set_empty_cells(page);
    page->isFull = 0;
    return (page);
}
