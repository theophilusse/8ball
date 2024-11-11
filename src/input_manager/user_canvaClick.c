#include "input_manager.h"

int             user_canvaClick(t_mega *mega, int flg)
{
    int                     err;
    int                     hudClick;
    t_tool                  *tool;
    struct s_hud_arrow      tmparrows;
    struct s_mouse          mouse;

    if (!mega || !mega->camera || !mega->viewport)
        return (1);
    tool = &mega->tool[mega->currentTool];
    if (mega->stcl->option.edit_mode == 1)
    {
        if (mega->currentTool != TOOLSET_NONE)
        /*{== NONE
            mega->tool[TOOLSET_SELECT].proceed((void *)mega, 0);
            return (0);
        }
        else*/
        { // Marker

            hud_project(mega->camera, &tool->hud, 1);
            //if ((tool->hud.active != 2 || hudClick == 1) &&
            ///if (mouse_clickHUD(tool, mega->mouse.onClick) || tool->hud.active == 2)
            if (mouse_clickHUD(tool, mega->mouse.onClick))
            {
                ///(tool->type == TOOLTYPE_HUD_ARROW || tool->type == TOOLTYPE_HUD_ANGLE))
                tool->proceed((void *)mega, 0);
            }
            else
                mega->tool[TOOLSET_SELECT].proceed((void *)mega, 0);
        }
    }
    return (0);
}
