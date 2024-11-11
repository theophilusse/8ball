#include "memmgr.h"

static int      memMgr_error(const char *str)
{
    printf("%s\n", str);
    return (1);
}

int        memMgr_init(void)
{
    t_memPage       **core_pointer;
    t_memPage       *sysPage;
    void            *magik;

    printf("Init core... ");
    if (!(core_pointer = CORE_ACCESSION(0)))    /** get core pointer **/
        return (memMgr_error("Error."));
    /*
        if (*core_pointer)
            *core_pointer = NULL;                   /// !!! possible leaks !!! ///
    */
    if (!(magik = ALLOC(42)))                   /** Bulk data **/
        return (memMgr_error("Error."));
    if (!(sysPage = mem_getCellPage(mem_getDataCell(magik)))) /** First Page wouldn't be removed so ... **/
        return (memMgr_error("Error."));
    *core_pointer = sysPage; /** ... link it to the core pointer **/
    printf("Success. CORE[%p][%p]\n", core_pointer, *core_pointer);
    return (0);
}

int        memMgr_release(void)
{
    t_memPage       **core_pointer;
    t_memPage       *sysPage;
    t_memPage       *page;
    t_memCell       *cell;

    printf("Release core... ");
    ///return (1); /** DeadCode :: TODO **/
    if (!(core_pointer = CORE_ACCESSION(0)))    /** get core pointer **/
        return (memMgr_error("Error."));
    if ((sysPage = *core_pointer))
    {
        page = sysPage;
        while (page)
        {
            mem_releasePage(page);
            page = page->chain.next;
        }
        *core_pointer = sysPage; /** ... link it to the core pointer **/
    }
    else
        return (memMgr_error("Error."));
    printf("Success.\n");
    return (0);
}
