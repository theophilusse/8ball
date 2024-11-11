#include "toolset.h"

struct s_tool       tool_buildRotate(t_mega *mega, int *err)
{
    struct s_hud            hud;
    struct s_tool           toolRotate;

    if (err)
        *err = 0;
    toolRotate.type = TOOLTYPE_NONE;
    toolRotate.refreshOrigin = 0;
    hud = hud_init();
    toolRotate.hud = hud;
    if (!mega)
    {
        if (err)
            *err = 1;
        return (toolRotate);
    }
    /***/
    toolRotate.hud.axis = hud_initAxis();
    toolRotate.type = TOOLTYPE_HUD_ANGLE;
    toolRotate.refreshOrigin = 0;
    toolRotate.hud.data.mouse_motion = mouse_motionAngle;
    toolRotate.proceed = tool_rotate;
    strcpy(toolRotate.name, "Rotate");
    /***/
    return (toolRotate);
}
