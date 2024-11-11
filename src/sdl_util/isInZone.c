#include "sdl_util.h"

int          isInZone(int *point, uint *dim, int *pos)
{
    if (!dim || !pos || !point)
        return (0);
    if (point[0] >= pos[0]
        && point[1] >= pos[1]
        && point[0] <= pos[0] + (int)dim[0]
        && point[1] <= pos[1] + (int)dim[1])
        return (1);
    return (0);
}
