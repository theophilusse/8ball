#include "toolset.h"

/**
 ** tool_init :
 ** Sub selection - toolRef.org in to cache
 **
**/
int          tool_init(t_mega *mega, int flg)
{
    t_tool                  *tool;
    t_select_node           *selectStack;
    int                     err;

    if (!mega || !(selectStack = mega->selectStack))
        return (0);
    tool = &mega->tool[mega->currentTool];
    ///tool_projectRef(mega, mega->camera, &mega->toolRef); /// Test
    selection_resetCache(selectStack, flg ? tool->hud.org.vec : NULL);
    selection_center(mega->selectStack, &tool->hud.org);
    ///hud_project(mega, mega->camera, &tool->hud, 1);
    if (tool->type == TOOLTYPE_NONE ||
        tool->type == TOOLTYPE_PROJECTIVE)
    {
        tool->hud.active = 0;
    }
    else
    {
        // Marker
        if (tool->type == TOOLTYPE_HUD_ANGLE)
            *((t_hud_angle *)tool->hud.data.buf) = hud_newAngle();
        if (tool->type == TOOLTYPE_HUD_ARROW)
            *((t_hud_arrow *)tool->hud.data.buf) = hud_newArrow(&tool->hud, mega->selectStack);
        if (tool->type == TOOLTYPE_HUD_LENGTH)
            *((t_hud_length *)tool->hud.data.buf) = hud_newLength(mega->mouse, tool);
        ///hud_project(mega, mega->camera, &tool->hud, 1);
        ///tool->hud.active = 1;
    }
    return (0);
}
