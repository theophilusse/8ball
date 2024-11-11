#include "memmgr.h"

struct s_memPageDim          default_page_dim(void)
{
    struct s_memPageDim     dim;

    dim.sz = 16 * 16;
    dim.szCell = sizeof(struct s_memCell);
    dim.pitch = 16;
    return (dim);
}
