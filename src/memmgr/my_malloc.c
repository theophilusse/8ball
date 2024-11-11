#include "memmgr.h"

void            *my_malloc(size_t sz)
{
    void        *pRet;
    t_memPage   *page;
    t_memPage   *root;
    t_memCell   *cell;

    if (sz == 0)
        return (NULL);
    root = mem_getRoot();
    /** Find Page **/
    if (!(page = page_getAvailable(&root, UI_DATATYPE_POINTER)))
    {
        DEBUG ///
        if (!(page = mem_newPage(default_page_dim()))) /** Init **/
        {
            DEBUG ///
            return (NULL);
        }
    }

    /** Find Cell **/
    if (!(cell = mem_getEmptyCell(page)))
        if (!(page = mem_newPage(default_page_dim())) ||
            !(cell = mem_getEmptyCell(page)))
            {
                if (page)
                    mem_releasePage(page);
                return (NULL);
            }

    /**  Set Cell **/
    if (!(pRet = mem_setCell(page, cell, sz)))
        return (NULL);
    return (pRet);
}
