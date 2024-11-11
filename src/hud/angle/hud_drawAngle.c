#include "hud.h"

static void                 draw_angle_axis(SDL_Surface *viewport, int *a, int *b, int *c, int ray)
{
    if (!viewport)
        return ;
    while (ray > 0)
    {
        if (a)
            circle(viewport, (uchar *)_blue, a[0], a[1], ray);
        if (b)
            circle(viewport, (uchar *)_red, b[0], b[1], ray);
        if (c)
            circle(viewport, (uchar *)_green, c[0], c[1], ray);
        ray--;
    }
}

void                        hud_drawAngle(SDL_Surface *viewport, struct s_hud_angle angle, t_tool *tool)
{
    int                   a[2];
    int                   b[2];
    int                   c[2];
    int                   *p[3] = { NULL, NULL, NULL };
    struct s_ref          ref;
    struct s_persp        persp;

    if (!tool || !viewport)
        return ;
    ref = tool->hud.org;
    persp = tool->hud.persp;
    if (isInCanva(viewport, (int *)&ref.coord[0], (int *)&ref.coord[1], 0))
    {
        if (isInCanva(viewport, (int *)&persp.x[0], (int *)&persp.x[1], 0))
        {
            draw_line_width(viewport, (uchar *)_red, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.x[0], (int)tool->hud.persp.x[1], 3);
            a[0] = (int)persp.x[0];
            a[1] = (int)persp.x[1];
            p[0] = (int *)a;
        }
        if (isInCanva(viewport, (int *)&persp.y[0], (int *)&persp.y[1], 0))
        {
            draw_line_width(viewport, (uchar *)_green, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.y[0], (int)tool->hud.persp.y[1], 3);
            b[0] = (int)persp.y[0];
            b[1] = (int)persp.y[1];
            p[1] = (int *)b;
        }
        if (isInCanva(viewport, (int *)&persp.z[0], (int *)&persp.z[1], 0))
        {
            draw_line_width(viewport, (uchar *)_blue, (int)tool->hud.org.coord[0], (int)tool->hud.org.coord[1], (int)tool->hud.persp.z[0], (int)tool->hud.persp.z[1], 3);
            c[0] = (int)persp.z[0];
            c[1] = (int)persp.z[1];
            p[2] = (int *)c;
        }
        square(viewport, (int)ref.coord[0] - 5, (int)ref.coord[1] - 5, 10, 10, (uchar *)_blue);
    }
    draw_angle_axis(viewport, p[0], p[1], p[2], 5);
}
