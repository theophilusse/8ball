#include "sdl_util.h"

int                 set_pos_lineWidth(int offset, int width)
{
    if (width <= 0) // guard
        return (offset); // width is zero.
    if (width % 2)
    {
        width++;
        width >>= 1;
        return (offset + width); // width is impair.
    }
    width >>= 1;
    return (offset - width); // width is pair.
}