#include "memmgr.h"

uint            mem_pageCount(t_memPage *root)
{
    t_memPage       *page;
    uint            counter;

    counter = 0;
    if ((page = root))
        while (page)
        {
            counter++;
            if (!(page = page->chain.next))
                return (counter);
        }
    page = mem_getRoot();
    while (page)
    {
        counter++;
        page = page->chain.next;
    }
    return (counter);
}
