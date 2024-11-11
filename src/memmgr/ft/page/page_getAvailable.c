#include "memmgr.h"

t_memPage        *page_getAvailable(t_memPage **prev, uint datatype)
{
    t_memPage   *page;
    t_mega      *mega;

    if (!(page = mem_getRoot()))
        return (NULL);
    if (prev)
        while (page->chain.next && (page->def.datatype != datatype || page->isFull == 1)) /** Get Garbage bin **/
        {
            *prev = page;
            page = (t_memPage *)(page->chain.next);
        }
    else
        while (page->chain.next && (page->def.datatype != datatype || page->isFull == 1)) /** Get Garbage bin **/
            page = (t_memPage *)(page->chain.next);
    return (page);
}
