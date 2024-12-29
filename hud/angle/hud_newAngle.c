#include "hud.h"

///struct s_hud_angle          new_hud_angle(SDL_Surface *s, t_cam *c, int w, int h, t_vselection *selectStack, t_pt_ref *ptorg)
struct s_hud_angle          hud_newAngle(void)
{
    struct s_hud_angle      angle;

    angle.ringRayLength = 25;
    /*angle.oppositeAxis[0] = 0;
    angle.oppositeAxis[1] = 0;*/
    ///angle.select_index = -1;
    ///copy_v3(ptorg->org, angle.vertice);
    /*add_v3(tool->hud.org.vec, tool->hud.axis.x, angle.pta);
    add_v3(tool->hud.org.vec, tool->hud.axis.y, angle.ptb);
    add_v3(tool->hud.org.vec, tool->hud.axis.z, angle.ptc);*/
    return (angle);
}
