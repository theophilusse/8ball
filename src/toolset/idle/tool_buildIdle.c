#include "toolset.h"

struct s_tool   tool_buildIdle(t_mega *mega, int *err)
{
    struct s_tool       tool;

    tool.type = TOOLTYPE_NONE;
    tool.name[0] = '\0';
    tool.proceed = tool_idle;
    tool.refreshOrigin = 0;
    tool.hud.active = 0;
    if (err)
        *err = 0;
    return (tool);
}
