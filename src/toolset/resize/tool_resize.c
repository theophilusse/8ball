#include "toolset.h"

static void         colorizeLine(double factor, uchar *color)
{
    /*if (!color)
        return;
    color[0] = (uchar)((double)_orange[0] * fabs(factor);
    color[1] = ;
    color[2] = ;
    color[3] = 255;*/
    /*
    f = ;
    squareSize[0] = (int)(f * 6);
    squareSize[1] = squareSize[0] / 2;
    squareSize[0] += 1;
    if (f <= 0.2)
        f = 0.2;
    k = -1;
    while (++k < 3)
        if ((c_val = (double)_blue_crystal[k] * f) < 255 - DBL_EPSILON)
            color[k] = (uchar)c_val;
        else
            color[k] = 255;
    */
}

static int          tool_applyResize(t_mega *mega, t_tool *tool, struct s_mouse mouse, int preview)
{
    struct s_hud_length         length;
    uchar       lineColor[3];

    if (!mega || !tool)
        return (1);
    length = *((t_hud_length *)tool->hud.data.buf);
    if (length.factor == 0 || (length.factor >= -DBL_EPSILON && length.factor <= DBL_EPSILON)) // Click but no motion.
        return (0);
    ///printf("Base mouse factor : [%f]\n", length.factor); ///
    ///mtp_selected((0.02 * mega->dragLength) * mega->dragFactor, mega->axis, mega->axis_hud_dot, mega->hud_arrow.vertice, mega->selectStack, preview);
    ///mtp_selected(mega->dragFactor, mega->axis, mega->axis_hud_reldot, mega->axis_hud_absdot, mega->hud_arrow.vertice, mega->selectStack, preview);
    ///mtp_selected(mega->dragFactorScale, mega->axis, mega->axis_hud_reldot, mega->axis_hud_absdot, mega->hud_arrow.vertice, mega->selectStack, preview);
    //resize_selected(mega->dragFactorScale, tool->hud.axis.w, mega->axis_hud_reldot, mega->axis_hud_absdot, tool->hud.org.vec, mega->selectStack, preview);
    resize_selected(length.factor, tool->hud.org.vec, mega->selectStack, preview, &mega->timeMachine);
    /*if (preview == 0)
    {
        tool->hud.axis.w[0] = 0;
        tool->hud.axis.w[1] = 0;
        tool->hud.axis.w[2] = 0;
        tool->hud.axis.w[3] = 1;
    }*/
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

int                 tool_resize(void *mega, int flg)
{
    t_mega          *pmega;
    t_tool          *tool;
    struct s_mouse        mouse;

    if (!(pmega = (t_mega *)mega))
        return (1);
    tool = &pmega->tool[pmega->currentTool];
    mouse = pmega->mouse;
    if (flg == 0) /// Pop arrows
        return (tool_init(pmega, 1));
    if (flg == 1) /// Push new data
        return (tool_applyResize(pmega, tool, mouse, 1));
    if (flg == 2) /// Push new data
        return (tool_applyResize(pmega, tool, mouse, 0));
    return (0);
}
