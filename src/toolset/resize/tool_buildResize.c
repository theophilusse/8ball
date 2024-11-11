#include "toolset.h"

struct s_tool       tool_buildResize(t_mega *mega, int *err)
{
    struct s_tool           toolResize;

    if (err)
        *err = 0;
    toolResize.type = TOOLTYPE_NONE;
    toolResize.refreshOrigin = 0;
    toolResize.hud.active = 0;
    if (!mega)
    {
        if (err)
            *err = 1;
        return (toolResize);
    }
    /***/
    ///toolResize.hud.axis = hud_initAxis();
    toolResize.type = TOOLTYPE_HUD_LENGTH;
    toolResize.refreshOrigin = 0;
    toolResize.hud.data.mouse_motion = mouse_motionLength;
    toolResize.proceed = tool_resize;
    strcpy(toolResize.name, "Resize");
    /***/
    return (toolResize);
}
