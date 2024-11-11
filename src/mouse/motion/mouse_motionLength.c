#include "mouse.h"

int             mouse_motionLength(void *pmega, int flg)
{
    t_mega                  *mega;
    t_hud_length            *length;
    t_tool                  *tool;
    struct s_mouse          mouse;
    double                  axis_hud_absdot;
    double                  hud_vd[2];
    double                  drag_va[2];
    double                  vd_len;
    double                  va_len;

    if (!(mega = (t_mega *)pmega))
        return (1);
    tool = &mega->tool[mega->currentTool];
    length = ((t_hud_length *)tool->hud.data.buf);
    if (mega->stcl->option.edit_mode == 0 ||
        ///mega->hud_arrow.active != 2 ||
        mega->mouse.mouseButtonUp != 0 ||
        /** mega->mouse.mouseLeftButtonUp != 0 || **/ // Do this.
        !mega->selectStack ||
        tool->hud.active == 0)
        return (0);
    mouse = mega->mouse;
    //printf("MOUSEPOS[%d][%d] :::::: COORD[%f][%f]\n", mouse.mousePos[0], mouse.mousePos[1], tool->hud.org.coord[0], tool->hud.org.coord[1]); ///
    drag_va[0] = mouse.mousePos[0] - (int)tool->hud.org.coord[0]; /// Total Drag
    drag_va[1] = mouse.mousePos[1] - (int)tool->hud.org.coord[1];

    hud_vd[0] = (double)1;
    hud_vd[1] = (double)0;
    va_len = length2(drag_va); /// Mouse -> HUD_o
    vd_len = length->onClick;///mouse.cacheLengthClick; /// onClick -> HUD_o
    unit2(drag_va, drag_va, NULL);
    ///mega->axis_hud_reldot = dot_prod2(drag_tmp, hud_vd);

    if (va_len < vd_len)
        length->factor = 1 / (vd_len / va_len);
    else
        length->factor = 1 + ((va_len - vd_len) / vd_len);
    axis_hud_absdot = dot_prod2(drag_va, hud_vd);
    if (axis_hud_absdot < 0)
    ///if (axis_hud_absdot < 0 && length->side == 1)
        length->factor *= -1;
    if (length->side == 0)
        length->factor *= -1;
    mega->mouse = mouse;
    ///
    return (0);
}
