#include "sdl_util.h"

struct s_ftData_zone        zone_upLeftCorner(void)
{
    struct s_ftData_zone        zone;

    zone.dim[0] = 16 * 16;
    zone.dim[1] = 16;
    zone.pos[0] = 0;
    zone.pos[1] = 0;
    zone.maxDim[0] = 16 * 16;
    zone.maxDim[1] = 16;
    zone.minDim[0] = 16 * 16;
    zone.minDim[1] = 16;
    return (zone);
}