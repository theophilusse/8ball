#include "hud.h"

struct s_hud_arrow          hud_newArrow(t_hud *hud, t_select_node *selectStack)
{
    struct s_hud_arrow      arrow;
    double                  org[3];

    arrow.factor = 0;
    if (!hud || !selectStack)
        arrow.max_adj = 0;
    else
    {
        copy_v3(hud->org.vec, org);
        switch (hud->select_index)
        {
            case 0: { arrow.max_adj = selection_measureAdj(org, hud->axis.x, selectStack); break; }
            case 1: { arrow.max_adj = selection_measureAdj(org, hud->axis.y, selectStack); break; }
            case 2: { arrow.max_adj = selection_measureAdj(org, hud->axis.z, selectStack); break; }
            default: { arrow.max_adj = 0; }
        }
    }
    return (arrow);
}
