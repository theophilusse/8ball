#include "sdl_util.h"

struct s_scanline       new_scanline(int pos, int xFrom, int xTo, int *width)
{
    struct s_scanline       lin;

    lin.range[0] = xFrom;
    lin.range[1] = xTo;
    lin.pos = pos;
    lin.w = width ? *width : 1;
    return (lin);
}
