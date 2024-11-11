#include "memmgr.h"

void            mem_cleanPage(t_memPage *page) /** For cell type = 0 **/
{
    t_memCell           *cell;
    size_t              sz;
    size_t              i;

    if (!page)
        return ;
    ///DEBUG ///
    if (!(cell = mem_getPageCell(page))) /** First Page wouldn't be removed so ... **/
        return ;
    sz = page->info.sz;
    i = 0;
    while (i < sz)
    {
        CELL_FREE(cell->ptr);
        cell->ptr = NULL;
        cell++;
        i++;
    }
    page->isFull = 0;
}
