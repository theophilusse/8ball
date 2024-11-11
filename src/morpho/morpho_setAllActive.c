#include "morpho.h"

void            morpho_setAllActive(t_morpho_group *part, uchar active)
{
    uchar       index;

    if (!part)
        return ;
    index = -1;
    while (++index < MORPHO_PARTS_NUM)
    {
        part->active = active;
        part++;
    }
}
