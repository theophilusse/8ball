#include "memmgr.h"

void     mem_display(void)
{
    t_memPage   **core;
    t_memPage   *page;

    if (!(core = CORE_ACCESSION(0)))
        return ;
    if (!(page = *core))
        return ;
    printf("CORE_DUMP:\n");
    while (page)
    {
        mem_pageDisplay(page);
        page = page->chain.next;
    }
}