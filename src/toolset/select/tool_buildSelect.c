#include "toolset.h"

struct s_tool           tool_buildSelect(t_mega *mega, int *err)
{
    struct s_hud_arrow          hud;
    struct s_tool               toolSelect;

    if (err)
        *err = 0;
    toolSelect.type = TOOLTYPE_NONE;
    toolSelect.refreshOrigin = 0;
    toolSelect.hud.active = 0;
    if (!mega)
    {
        if (err)
            *err = 1;
        return (toolSelect);
    }

    /***/
    ///toolSelect.hud.axis = hud_initAxis();
    toolSelect.type = TOOLTYPE_PROJECTIVE;
    toolSelect.refreshOrigin = 1;
    toolSelect.hud.data.mouse_motion = user_idle;
    toolSelect.proceed = tool_select;
    strcpy(toolSelect.name, "Vertice Select");
    /***/
    return (toolSelect);
}
