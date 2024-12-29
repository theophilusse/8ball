#include "hud.h"

void                        hud_drawArrow(SDL_Surface *viewport, struct s_hud_arrow arrow, t_tool *tool)
{
    struct s_ref        ref;
    struct s_persp      persp;

    if (!tool || !viewport)
        return ;
    ref = tool->hud.org;
    persp = tool->hud.persp;
    if (isInCanva(viewport, (int *)&ref.coord[0], (int *)&ref.coord[1], 0))
    {
        if (isInCanva(viewport, (int *)&persp.x[0], (int *)&persp.x[1], 0))
        {
            draw_line_width(viewport, (uchar *)_red, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.x[0], (int)tool->hud.persp.x[1], 3);
            square(viewport, (int)tool->hud.persp.x[0] - 5, (int)tool->hud.persp.x[1] - 5, 10, 10, (uchar *)_red);
        }
        if (isInCanva(viewport, (int *)&persp.y[0], (int *)&persp.y[1], 0))
        {
            draw_line_width(viewport, (uchar *)_green, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.y[0], (int)tool->hud.persp.y[1], 3);
            square(viewport, (int)tool->hud.persp.y[0] - 5, (int)tool->hud.persp.y[1] - 5, 10, 10, (uchar *)_green);
        }
        if (isInCanva(viewport, (int *)&persp.z[0], (int *)&persp.z[1], 0))
        {
            draw_line_width(viewport, (uchar *)_blue, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.z[0], (int)tool->hud.persp.z[1], 3);
            square(viewport, (int)tool->hud.persp.z[0] - 5, (int)tool->hud.persp.z[1] - 5, 10, 10, (uchar *)_blue);
        }
    }
}
