#include "sdl_util.h"

int              isInTile(int x, int y, int *tileDim, int *onClick)
{
    if (!tileDim || !onClick)
        return (0);
    if (onClick[0] < x || onClick[0] > x + tileDim[0])
        return (0);
    if (onClick[1] < y || onClick[1] > y + tileDim[1])
        return (0);
    return (1);
}
