#include "mouse.h"

int                                 mouse_motionArrow(void *pmega, int flg)
{
    t_mega                  *mega;
    struct s_mouse          mouse;
    double            arrow_pt[2];
    double         hud_vdir[3];
    double         hud_vptx[3];
    double         hud_vm[2];

    double         arrow_vec[2];
    double         vd_len;
    double         total_drag[3];
    double         va_len;

    double         drag[2];
    double         pos_tmp[2];

    double         dragLength;
    double         dragFactor;
    double         axis_hud_reldot;
    double         axis_hud_absdot;

    t_hud               *hud;
    struct s_tool       tool;
    struct s_hud_arrow  arrow;

    if (!(mega = (t_mega *)pmega))
        return (1);
    tool = mega->tool[mega->currentTool];
    if (tool.type != TOOLTYPE_HUD_ARROW || !(hud = &tool.hud))
        return (0);
    ((t_hud_arrow *)(hud->data.buf))->factor = 0;
    arrow = *((t_hud_arrow *)(&hud->data.buf));
    if (mega->stcl->option.edit_mode == 0 ||
        hud->active != 2 ||
        !mega->selectStack)
        return (0);
    ///DEBUG ///
    mouse = mega->mouse;
    if (hud->select_index != -1) /// Drag arrow
    {
        copy_v3(tool.hud.org.vec, hud_vptx);
        /*mega->drag_v[0] = mouse.mousePos[0] - mouse.onClick[0]; /// Total Drag
        mega->drag_v[1] = mouse.mousePos[1] - mouse.onClick[1];*/
        /*total_drag[0] = (mouse.mousePos[0] - tool.hud.org.coord[0]; /// Total Drag
        total_drag[1] = (mouse.mousePos[1] - tool.hud.org.coord[1];*/
        total_drag[0] = (mouse.onClick[0] + mouse.mouseRle[0]) - tool.hud.org.coord[0]; /// Total Drag
        total_drag[1] = (mouse.onClick[1] + mouse.mouseRle[1]) - tool.hud.org.coord[1];
        switch (hud->select_index)
        {
            case 0: { /*copy_v3(tool.hud.axis.x, hud_vdir);*/ copy_v2(tool.hud.persp.x, arrow_pt); break; };
            case 1: { /*copy_v3(tool.hud.axis.y, hud_vdir);*/ copy_v2(tool.hud.persp.y, arrow_pt); break; };
            case 2: { /*copy_v3(tool.hud.axis.z, hud_vdir);*/ copy_v2(tool.hud.persp.z, arrow_pt); break; };
        }
        arrow_vec[0] = arrow_pt[0] - tool.hud.org.coord[0];
        arrow_vec[1] = arrow_pt[1] - tool.hud.org.coord[1];

        drag[0] = (double)mouse.mouseDrag[0];
        drag[1] = (double)mouse.mouseDrag[1];
        dragLength = length2(drag); /// .....?
        unit2(drag, drag, NULL);

        va_len = length2(total_drag); /// Mouse -> HUD_o
        vd_len = length2(arrow_vec); /// HUD_x -> HUD_o
        unit2(total_drag, total_drag, NULL);
        unit2(arrow_vec, arrow_vec, NULL);
        axis_hud_reldot = dot_prod2(drag, arrow_vec);
        axis_hud_absdot = dot_prod2(total_drag, arrow_vec);
        switch (mega->currentTool)
        {
            /*** Critical Section ***/
            case TOOLSET_SCALE:
            {
                if (va_len < vd_len)
                    dragFactor = 1 - ((vd_len - va_len) / vd_len);
                else
                    dragFactor = ((va_len - vd_len) / vd_len) + 1;
                dragFactor = (dragFactor * axis_hud_absdot);

                printf("Drag factor : [%f]\n", dragFactor); ///
                break;
            }
            case TOOLSET_TRANSFORM:
            {
                dragFactor = axis_hud_reldot * dragLength;
                break;
            }
            default: { dragFactor = 0; }
        }
        ///mega->dragFactor = mega->axis_hud_reldot * mega->dragLength;

        /// Marker
        ((t_hud_arrow *)(mega->tool[mega->currentTool].hud.data.buf))->factor = dragFactor; // Test
        mouse.draw_marker = 1;
        mega->mouse = mouse;
    }
    return (0);
}

///mega->tool[mega->currentTool].proceed((void *)mega, 1);
/**************/
/*if (mega->hud_arrow.active == 2)
{
    add_v3(mega->hud_arrow.vertice, mouse.drag_ac, mega->hud_arrow.vertice);
    add_v3(mega->hud_arrow.pta, mouse.drag_ac, mega->hud_arrow.pta);
    add_v3(mega->hud_arrow.ptb, mouse.drag_ac, mega->hud_arrow.ptb);
    add_v3(mega->hud_arrow.ptc, mouse.drag_ac, mega->hud_arrow.ptc);
    add_selected(mouse.drag_ac, mega->selectStack);
    //add_selected(drag_v, mega->selectStack);
    ///printf("TRIANGLE AC = [%f][%f][%f]\n", mouse.drag_ac[0], mouse.drag_ac[1], mouse.drag_ac[2]);
    if (mega->stcl->triangle_buf)
        FREE(mega->stcl->triangle_buf);
    if (push_triangle_opencl(mega->stcl, mega->camera->data))
        return (1);
    ///if ((err = clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->input_triangle,
    if ((clEnqueueWriteBuffer(mega->stcl->queue, mega->stcl->input_triangle,
            CL_TRUE, 0,  mega->stcl->triangle_bufsz, mega->stcl->triangle_buf, 0, NULL, NULL)) != CL_SUCCESS)
    {
        printf("Couldn't write buffer 1\n");
        return (1);
    }
}*/
/**************/
