#include "input_manager.h"

int user_mouseButtonUp(t_mega *mega, int flg)
{
    t_tool                  *tool;
    struct s_mouse          mouse;

    if (!mega)
        return (1);
    mouse = mega->mouse;
    if (mouse.mouseButtonUp == 1)
        return (0);
    /// Marker
    tool = &mega->tool[mega->currentTool];
    ///refreshOrigin = tool.refreshOrigin;
    if (mega->stcl->option.edit_mode == 1 && mouse.leftButton == 1)
    {
        /*if (tool.hud.active != 0)
            hud_project(mega, mega->camera, &tool.hud);*/ /// Test
        /**
        if (mega->selectStack && tooltype == TOOLTYPE_HUD_ARROW)
            currentTool.hud.active = 1;
        else
            currentTool.hud.active = 0;
        if (mega->selectStack && tooltype == TOOLTYPE_HUD_ANGLE)
            currentTool.hud.active = 1;
        else
            currentTool.hud.active = 0;
            **/
        if (tool->hud.active == 2)/* &&
            (tooltype == TOOLTYPE_HUD_ANGLE ||
            tooltype == TOOLTYPE_HUD_ARROW ||
            tooltype == TOOLTYPE_HUD_LENGTH))*/
        {
            tool->proceed((void *)mega, 2);
            tool->hud.active = 1;
            tool->hud.select_index = -1;
        }
        //tool.hud.active = 1;
    }

    /************** UI onRelease *************/
    struct s_ui_event       event;
    if (mouse.leftButton == 1 && mega->ui->active != 0)
    {
        event = ui_interfaceOnRelease(mega);
    }
    mega->ui->sigFrame = 1;
    mega->ui->sigRefresh = 1;
    /*ui_main(mega, mega->ui);
    super_blit(mega); /// Test
    */
    /* // Org.
        blit_mergeAlpha(mega->camera->data->backbuffer, mega->viewport);//Test
        blit_mergeAlpha(mega->hud_viewport, mega->viewport);
        blit_mergeAlpha(mega->log_viewport, mega->viewport);
        blit_mergeAlpha(mega->ui_viewport, mega->viewport);
        refresh(mega->viewport, mega->screen); // Render !
    */
    /************** UI onRelease *************/

    mouse.mouseRle[0] = 0;
    mouse.mouseRle[1] = 0;
    mouse.mouseDrag[0] = 0;
    mouse.mouseDrag[1] = 0;
        mouse.cacheClick[0] = 0;
        mouse.cacheClick[1] = 0;
    mouse.motion_ft = USER_MOUSE_MOTION_IDLE;
    mouse.leftButton = 0;
    mouse.mouseButtonUp = 1;
    mouse.drag_ac[0] = 0;
    mouse.drag_ac[1] = 0;
    mouse.drag_ac[2] = 0;
    /// mega->tool[mega->currentTool] = tool; ///
    mega->ui->event = event;
    mega->mouse = mouse;
    return (0);
}
