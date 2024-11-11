#include "toolset.h"

static int          tool_applyScale(t_mega *mega, t_tool *tool, struct s_mouse mouse, int preview)
{
    double              axis[3];
    struct s_hud_arrow  arrow;

    if (!tool || tool->hud.active != 2)
        return (0);
    arrow = *((t_hud_arrow *)tool->hud.data.buf);
    switch (tool->hud.select_index)
    {
        case 0: { copy_v3(tool->hud.axis.x, axis); break; };
        case 1: { copy_v3(tool->hud.axis.y, axis); break; };
        case 2: { copy_v3(tool->hud.axis.z, axis); break; };
    }
    if (arrow.max_adj != 0)
        mtp_selected(arrow.factor, axis, tool->hud.org.vec, arrow.max_adj, mega->selectStack, preview, &mega->timeMachine);
    if (preview == 0) // Obsolete?
    {
        tool->hud.axis.w[0] = 0;
        tool->hud.axis.w[1] = 0;
        tool->hud.axis.w[2] = 0;
        tool->hud.axis.w[3] = 1;
    }
    if (mega->stcl->triangle_buf)
        FREE(mega->stcl->triangle_buf);
    if (push_triangle_opencl(mega->stcl, mega->camera->data))
        return (1);
    if ((clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->input_triangle,
            CL_TRUE, 0,  mega->stcl->triangle_bufsz, mega->stcl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1\n");
        return (1);
    }
    return (0);
}

int                 tool_scale(void *mega, int flg)
{
    t_mega              *pmega;
    t_tool              *tool;
    struct s_mouse      mouse;
    int                 err;
    ///static double       max_adj;

    if (!(pmega = (t_mega *)mega))
        return (1);
    tool = &pmega->tool[pmega->currentTool];
    mouse = pmega->mouse;
    if (flg == 0) /// Pop arrows
        return (tool_init(pmega, 0));
    if (flg == 1) /// Push new data
        return (tool_applyScale(pmega, tool, mouse, 1));
    if (flg == 2) /// Push new data
        return (tool_applyScale(pmega, tool, mouse, 0));
    return (0);
}
