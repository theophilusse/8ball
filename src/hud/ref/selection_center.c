#include "hud.h"

int         selection_center(t_select_node *selectStack, t_ref *center)
{
    uint                        i;
    double                      ac[3];
    struct s_select_vertice     vrt;

    if (!selectStack || !center)
        return (1);
    ac[0] = 0;
    ac[1] = 0;
    ac[2] = 0;
    center->vec[0] = 0;
    center->vec[1] = 0;
    center->vec[2] = 0;
    i = 0;
    while (selectStack)
    {
        vrt = selectStack->vrt;
        if (vrt.ptr)
        {
            add_v3(ac, vrt.ptr, ac);
        }
        selectStack = selectStack->next;
        i++;
    }
    if (i == 0)
        return (1);
    div_v3_by(ac, i, center->vec);
    return (0);
}
