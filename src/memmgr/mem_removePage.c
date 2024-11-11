#include "memmgr.h"

static int      isSystemPage(t_memPage *page)
{
    if (page && (!page->chain.next && !page->chain.prev))
        return (1);
    return (0);
}

void        mem_removePage(t_memPage *page)
{
    t_memPage       **core_pointer;
    t_memPage       *next;
    t_memPage       *prev;

    if (!page || isSystemPage(page))
        return ;
    next = page->chain.next;
    prev = page->chain.prev;
    if (next && prev)
    {
        prev->chain.next = next;
        next->chain.prev = prev;
    }
    if (next && !prev)
    {
        return ; /** DeadCode **/
        if (!(core_pointer = CORE_ACCESSION(0)))
            return ;
        next->chain.prev = NULL;
        *core_pointer = next;
    }
    if (!next && prev)
        prev->chain.next = NULL;
    PAGE_FREE(page);
}
