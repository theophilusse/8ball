#include "hud.h"

///struct s_hud_arrow          new_hud_arrows(SDL_Surface *s, t_cam *c, int w, int h, double *point)
///struct s_hud_arrow          new_hud_arrows(SDL_Surface *s, t_cam *c, int w, int h, t_vselection *selectStack, t_pt_ref *ptorg)
struct s_hud_length          hud_newLength(struct s_mouse mouse, t_tool *tool)
{
    struct s_hud_length      length;
    double                vMouse[2];
    double                vScreen[2];

    vScreen[0] = (double)1;
    vScreen[1] = (double)0;
    vMouse[0] = mouse.onClick[0] - tool->hud.org.coord[0]; /// Total Drag
    vMouse[1] = mouse.onClick[1] - tool->hud.org.coord[1];
    length.onClick = mouse.cacheLengthClick; /// On-Click length.
    unit2(vMouse, vMouse, &mouse.cacheLengthClick);
    if (dot_prod2(vMouse, vScreen) <= -DBL_EPSILON)
        length.side = 0;
    else
        length.side = 1;
    length.factor = 0;
    return (length);
}
