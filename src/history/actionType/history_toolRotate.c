#include "history.h"

void             history_toolRotate(t_mega *mega, t_history *timeMachine, uint undo)
{
    t_select_node   *sel;

    double      v;
    double org[3];
    double axis[3];
    double drag_vec[3];
    struct s_ref        ref;

    if (!mega || !(sel = mega->selectStack))
        return ;
    copy_v3(timeMachine->param.vec, axis); /// Axis.
    selection_center(sel, &ref); /// Org. (center)
    copy_v3(ref.vec, org); /// Copy Org.
    selection_resetCache(sel, org); // Test.
    if (undo == 1) /// Factor.
        v = timeMachine->param._f64 * -1;
    else
        v = timeMachine->param._f64;
    while (sel)
    {
        if (sel->vrt.ptr)
        {
            copy_v3(sel->mem.cache, drag_vec);
            rot_vec3(axis, deg_to_rad(v), drag_vec);
            add_v3(drag_vec, org, sel->mem.base);
            copy_v3(sel->mem.base, sel->vrt.ptr);
            sel->mem.cache[0] = sel->mem.base[0] - org[0];
            sel->mem.cache[1] = sel->mem.base[1] - org[1];
            sel->mem.cache[2] = sel->mem.base[2] - org[2];
        }
        sel = sel->next;
    }
    gpu_modelRefresh(mega->stcl, mega->camera->data);
}
