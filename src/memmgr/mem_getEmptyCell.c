#include "memmgr.h"

t_memCell           *mem_getEmptyCell(t_memPage *page) /** For cell type = 0 **/
{
    t_memCell           *ret;
    size_t              sz;
    size_t              i;

    if (!page || !(ret = mem_getPageCell(page)))
        return (NULL);
    ///DEBUG ///
    sz = page->info.sz;
    i = 0;
    while (i < sz)
    {
        if (ret->ptr == NULL)
            return (ret);
        ret++;
        i++;
    }
    ///DEBUG ///
    return (NULL);
}
