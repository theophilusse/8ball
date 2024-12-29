#include "hud.h"

struct s_hud         hud_init(void)
{
    struct s_hud        hud;

    hud.active = 0;
    hud.axis = hud_initAxis();
    hud.data.mouse_motion = (int (*)(void *, int))user_idle;
    ///memset((void *)hud.data.buf, 0, 64);
    hud.org.coord[0] = -1;
    hud.org.coord[1] = -1;
    hud.org.vec[0] = 0;
    hud.org.vec[1] = 0;
    hud.org.vec[2] = 0;
    hud.org.vec[3] = 0;
    hud.persp = hud_initPersp();
    hud.type = -1;
    return (hud);
}
