#include "toolset.h"

struct s_tool       tool_buildTransform(t_mega *mega, int *err)
{
    struct s_tool           toolTransform;

    if (err)
        *err = 0;
    toolTransform.type = TOOLTYPE_NONE;
    toolTransform.refreshOrigin = 0;
    toolTransform.hud.active = 0;
    if (!mega)
    {
        if (err)
            *err = 1;
        return (toolTransform);
    }
    /***/
    toolTransform.hud.axis = hud_initAxis();
    toolTransform.type = TOOLTYPE_HUD_ARROW;
    toolTransform.refreshOrigin = 1;
    toolTransform.hud.data.mouse_motion = mouse_motionArrow;
    toolTransform.proceed = tool_transform;
    strcpy(toolTransform.name, "Transform");
    /***/
    return (toolTransform);
}
