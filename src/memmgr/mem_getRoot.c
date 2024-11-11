#include "memmgr.h"

t_memPage       *mem_getRoot(void)
{
    t_memPage       **core;

    if ((core = CORE_ACCESSION(0)))
        return (*core);
    return (NULL);
}