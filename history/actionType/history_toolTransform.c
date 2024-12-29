#include "history.h"

void             history_toolTransform(t_mega *mega, double *vec, uint undo)
{
    double          transform[3];
    t_select_node   *sel;

    //BEEP_WARNING /// Debug
    if (!mega || !(sel = mega->selectStack) || !vec)
        return ;
    if (undo)
        inv_v3(vec, transform);
    else
        copy_v3(vec, transform);
    while (sel)
    {
        if (sel->vrt.ptr)
        {
            add_v3(sel->mem.base, transform, sel->mem.base);
            copy_v3(sel->mem.base, sel->vrt.ptr);
        }
        sel = sel->next;
    }
    gpu_modelRefresh(mega->stcl, mega->camera->data);
}
