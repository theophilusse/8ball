#include "hud.h"

struct s_persp          hud_initPersp(void)
{
    struct s_persp          persp;

    persp.w[0] = -1;
    persp.w[1] = -1;
    persp.z[0] = -1;
    persp.z[1] = -1;
    persp.y[0] = -1;
    persp.y[1] = -1;
    persp.x[0] = -1;
    persp.x[1] = -1;
    return (persp);
}
