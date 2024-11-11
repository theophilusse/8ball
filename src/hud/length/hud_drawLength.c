#include "hud.h"

void                        hud_drawLength(SDL_Surface *viewport, struct s_hud_length length, t_tool *tool, int *mousePos)
{
    struct s_ref        ref;

    if (!tool || !viewport)
        return ;
    ref = tool->hud.org;
    ///charset_print(mega->screen, mega->charset, (mega->viewport->w / 2) - (7*16), (mega->viewport->h / 2) + 75, " Press Any key ");
    if (isInCanva(viewport, (int *)&ref.coord[0], (int *)&ref.coord[1], 0))
    {
        square(viewport, ref.coord[0] - 5, ref.coord[1] - 5, 10, 10, (uchar *)_orange);
        if (tool->hud.active == 2 && mousePos)
            draw_line_width(viewport, (uchar *)_black,
                        tool->hud.org.coord[0], tool->hud.org.coord[1], mousePos[0], mousePos[1], 2);
    }
}
