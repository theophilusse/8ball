#include "toolset.h"

struct s_tool       tool_buildScale(t_mega *mega, int *err)
{
    struct s_tool           toolScale;

    if (err)
        *err = 0;
    toolScale.type = TOOLTYPE_NONE;
    toolScale.refreshOrigin = 0;
    toolScale.hud.active = 0;
    if (!mega)
    {
        if (err)
            *err = 1;
        return (toolScale);
    }
    /***/
    toolScale.hud.axis = hud_initAxis();
    toolScale.type = TOOLTYPE_HUD_ARROW;
    toolScale.refreshOrigin = 0;
    toolScale.hud.data.mouse_motion = mouse_motionArrow;
    toolScale.proceed = tool_scale;
    strcpy(toolScale.name, "Scale");
    /***/
    return (toolScale);
}
