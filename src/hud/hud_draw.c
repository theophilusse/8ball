#include "hud.h"

static void                        hud_drawGeneric(SDL_Surface *viewport, t_cam *c, t_tool *tool)
{
    int                 size;

    draw_line_width(viewport, (uchar *)_red, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.x[0], (int)tool->hud.persp.x[1], 3);
    draw_line_width(viewport, (uchar *)_green, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.y[0], (int)tool->hud.persp.y[1], 3);
    draw_line_width(viewport, (uchar *)_blue, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.z[0], (int)tool->hud.persp.z[1], 3);
    square(viewport, (int)tool->hud.persp.x[0] - 5, (int)tool->hud.persp.x[1] - 5, 10, 10, (uchar *)_red);
    square(viewport, (int)tool->hud.persp.y[0] - 5, (int)tool->hud.persp.y[1] - 5, 10, 10, (uchar *)_green);
    square(viewport, (int)tool->hud.persp.z[0] - 5, (int)tool->hud.persp.z[1] - 5, 10, 10, (uchar *)_blue);
    return ;
}

///void                        hud_draw(SDL_Surface *s, t_cam *c, int w, int h, struct s_hud_arrow hud_arrow, t_ref *toolRef)
void                        hud_draw(SDL_Surface *viewport, t_cam *camera, t_tool *tool, int *mousePos)
{
    struct s_hud_arrow hud_arrow;
    struct s_tool           projection; /// TEST

    if (!viewport || !camera || !tool ||
        tool->hud.active == 0)
        return ;
    switch (tool->type)
    {
        case TOOLTYPE_HUD_ARROW: { hud_drawArrow(viewport, *((t_hud_arrow *)tool->hud.data.buf), tool); break; }
        case TOOLTYPE_HUD_ANGLE: { hud_drawAngle(viewport, *((t_hud_angle *)tool->hud.data.buf), tool); break; }
        case TOOLTYPE_HUD_LENGTH: { hud_drawLength(viewport, *((t_hud_length *)tool->hud.data.buf), tool, mousePos); break; }
        default: break;
    }
    /*if (tool->hud.active != 0)
        hud_drawGeneric(viewport, camera, tool);*/
    /**
    printf("HUD active = [%d]\n", (int)tool->hud.active); ///
    if (tool->type == TOOLTYPE_HUD_ARROW && tool->hud.active != 0)
        hud_drawArrow(viewport, camera, viewport->w, viewport->h, *((t_hud_arrow *)tool->hud.data.buf), &tool->hud.org);
    if (tool->type == TOOLTYPE_HUD_ANGLE && tool->hud.active != 0)
        hud_drawAngle(viewport, camera, viewport->w, viewport->h, *((t_hud_angle *)tool->hud.data.buf), &tool->hud.org);
    **/
}
