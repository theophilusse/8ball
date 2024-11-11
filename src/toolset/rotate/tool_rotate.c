#include "toolset.h"

/**
 ** chooseColor :
 ** Takes index X=0 Y=1 Z=2 W=? and a valid color pointer.
 ** color would be filled with the right color index. (RGBW)
 **
**/
static void         chooseColor(int axis_index, uchar *color)
{
    if (!color)
        return ;
    switch (axis_index)
    {
        case 0:
        {
            color[0] = 0;
            color[1] = 0;
            color[2] = 255;
            break;
        }
        case 1:
        {
            color[0] = 255;
            color[1] = 0;
            color[2] = 0;
            break;
        }
        case 2:
        {
            color[0] = 0;
            color[1] = 255;
            color[2] = 0;
            break;
        }
        default:
        {
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
            break;
        }
    }
}

static int          tool_applyRotate(t_mega *mega, t_tool *tool, struct s_mouse mouse, int preview)
{
    struct s_hud_angle  angle;
    uchar       lineColor[3];

    if (!mega || !tool)
        return (1);
    angle = *((t_hud_angle *)tool->hud.data.buf);
    if (tool->hud.select_index == -1)
        return (0);
    if (preview == 1)
    {
        chooseColor(tool->hud.select_index, lineColor);
        draw_line_width(mega->viewport, (uchar *)lineColor,
                        tool->hud.org.coord[0], tool->hud.org.coord[1], mega->mouse.mousePos[0], mega->mouse.mousePos[1], 2);
    }
    switch (tool->hud.select_index)
    {
        case 0: { copy_v3(tool->hud.axis.x, tool->hud.axis.w); break; }
        case 1: { copy_v3(tool->hud.axis.y, tool->hud.axis.w); break; }
        case 2: { copy_v3(tool->hud.axis.z, tool->hud.axis.w); break; }
    }
    rotate_selected(angle.degrees, tool->hud.axis.w, tool->hud.org.vec, mega->selectStack, preview, &mega->timeMachine);
    gpu_modelRefresh(mega->stcl, mega->camera->data); //
    return (0); /// Test.
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

int                 tool_rotate(void *mega, int flg)
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
        return (tool_applyRotate(pmega, tool, mouse, 1));
    if (flg == 2) /// Push new data
        return (tool_applyRotate(pmega, tool, mouse, 0));
    return (0);
}
