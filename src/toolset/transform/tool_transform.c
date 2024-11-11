#include "toolset.h"

static int          tool_applyTransform(t_mega *mega, t_tool *tool, struct s_mouse mouse, int preview)
{
    struct s_hud_arrow  arrow;
    double              axis[3];
    double              vec[3];

    if (!tool || tool->hud.active != 2)
        return (0);
    arrow = *((t_hud_arrow *)tool->hud.data.buf);
    switch (tool->hud.select_index)
    {
        case 0: { copy_v3(tool->hud.axis.x, axis); break; };
        case 1: { copy_v3(tool->hud.axis.y, axis); break; };
        case 2: { copy_v3(tool->hud.axis.z, axis); break; };
        default: { return (0); }
    }
    mtp_v3_by(axis, 0.03 * arrow.factor, vec);
    add_v3(tool->hud.org.vec, vec, tool->hud.org.vec);
    add_selected(vec, mega->selectStack, preview, preview == 0 ? &mega->timeMachine : NULL);

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
    if (preview == 0)
    {
        tool->hud.select_index = -1; /// Test
        selection_center(mega->selectStack, &tool->hud.org);
    }
    *((t_hud_arrow *)tool->hud.data.buf) = arrow;
    return (0);
}

int                 tool_transform(void *mega, int flg)
{
    t_mega          *pmega;
    t_tool          *tool;
    struct s_mouse        mouse;

    if (!(pmega = (t_mega *)mega))
        return (1);
    tool = &pmega->tool[pmega->currentTool];
    mouse = pmega->mouse;
    if (flg == 0) /// Pop arrows
        return (tool_init(pmega, 0));
    if (flg == 1) /// Push new data
        return (tool_applyTransform(pmega, tool, mouse, 1));
    if (flg == 2) /// Push new data
        return (tool_applyTransform(pmega, tool, mouse, 0));
    return (0);
}
