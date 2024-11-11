#include "history.h"

void             history_toolScale(t_mega *mega, t_history *timeMachine, uint undo)
{
    t_select_node   *sel;

    float       max_dist;
    double      v;
    double hyp[3];
    double vec[3];
    double org[3];
    double axis[3];
    struct s_ref        ref;

    if (!mega || !(sel = mega->selectStack) || !vec)
        return ;
    copy_v3(timeMachine->param.vec, axis); /// Axis.
    selection_center(sel, &ref); /// Org. (center)
    copy_v3(ref.vec, org); /// Copy Org.
    max_dist = timeMachine->param._f32; /// Max_dist.
    v = timeMachine->param._f64; /// Factor.
    if (v != 0)
        while (undo-- != 0)
            v = 1 / v;
    while (sel)
    {
        if (sel->vrt.ptr)
        {
            sub_v3(sel->mem.base, org, hyp);

            /** Scaling **/
            hyp[0] += hyp[0] * ((v - 1) * axis[0]);
            hyp[1] += hyp[1] * ((v - 1) * axis[1]);
            hyp[2] += hyp[2] * ((v - 1) * axis[2]);

            add_v3(hyp, org, vec);
            /** Scaling **/

            /** Dump **/
            copy_v3(vec, sel->mem.base);
            copy_v3(sel->mem.base, sel->vrt.ptr);
        }
        sel = sel->next;
    }
    gpu_modelRefresh(mega->stcl, mega->camera->data);
}
