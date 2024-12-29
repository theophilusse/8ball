#include "mouse.h"

int             mouse_motionAngle(void *pmega, int flg) /// Taken from HUD ClickDrage
{
    t_mega                  *mega;
    t_tool                  *tool;
    //struct s_ref            org;
    struct s_mouse          mouse;
    //double         vd_len;
    double         drag_vo[3]; /// Obsolete ?
    double         drag_va[3];
    double         drag_vp[3];
    double         drag_tmp[2];

    if (!(mega = (t_mega *)pmega))
        return (1);
    tool = &mega->tool[mega->currentTool];
    //org = tool->hud.org;
    if (mega->stcl->option.edit_mode == 0 ||
        tool->hud.active != 2 ||
        0)///!mega->hud_angle.selection)
        return (0);
    mouse = mega->mouse;

    drag_va[0] = (double)mouse.mouseRle[0]; /// Total Drag
    drag_va[1] = (double)mouse.mouseRle[1];

    // Org.
    /*
    drag_va[0] = mouse.mousePos[0] - (double)org.coord[0]; /// Total Drag
    drag_va[1] = mouse.mousePos[1] - (double)org.coord[1];*/

    drag_tmp[0] = (double)mouse.mouseDrag[0];
    drag_tmp[1] = (double)mouse.mouseDrag[1];
    unit2(drag_tmp, drag_tmp, NULL);

    //vd_len = mouse.cacheLengthClick; /// onClick -> HUD_o
    unit2(drag_va, drag_va, NULL);

    ///axis_hud_absdot = dot_prod2(drag_va, mouse.cacheUnitClick);

    /** Mouse Motion Rotate **/
        double 		a;
        double 		b;
        double 		c;
        double 		d;

        /*d = dot_prod2(mega->drag_va, drag_vp);
        a = dot_prod2(mega->drag_va, mouse.cacheUnitClick);*/

        inv_v3(mouse.cacheUnitClick, drag_vp);
        a = dot_prod2(drag_va, drag_vp);
        rot_vec2(mouse.cacheUnitClick, 90, drag_tmp); /// TESTING
        b = dot_prod2(drag_va, drag_tmp);
        c = (a + 1.0) * 90;
        if (b > 0)
            d = c * -1;
        else
            d = c;
    /** Mouse Motion Rotate **/
    ((t_hud_angle *)tool->hud.data.buf)->degrees = d; /// Testing
    mega->mouse = mouse;
    ///

    tool->proceed((void *)mega, 1);
    return (0);
}
