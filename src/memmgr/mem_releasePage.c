#include "memmgr.h"

void         mem_releasePage(t_memPage *page)
{
    if (!page)
        return ;
    mem_cleanPage(page);
    mem_removePage(page);
}
