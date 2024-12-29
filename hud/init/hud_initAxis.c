#include "hud.h"

struct s_axis        hud_initAxis(void)
{
    struct s_axis       axis;

    axis.w[0] = 0;
    axis.w[1] = 0;
    axis.w[2] = 0;
    axis.w[3] = 0;
    axis.z[0] = 0;
    axis.z[1] = 0;
    axis.z[2] = 1;
    axis.z[3] = 1;
    axis.y[0] = 0;
    axis.y[1] = 1;
    axis.y[2] = 0;
    axis.y[3] = 1;
    axis.x[0] = 1;
    axis.x[1] = 0;
    axis.x[2] = 0;
    axis.x[3] = 1;
    return (axis);
}
