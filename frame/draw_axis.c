#include "frame.h"

void            draw_axis(SDL_Surface *s, uchar *color, double *axis, int w, int h, int x, int y, int size, SDL_Surface **tileset, char *name)
{
    int     size_2;
    int     rx;
    int     ry;

    size_2 = size / 2;
    rx = x;
    ry = y;
    //rx += (axis[2] * (20 * w)) + axis[0] * (20 * w);
    //ry += (axis[0] * (20 * w)) - ((double)axis[1] * 0.5 + axis[2] * (20 * w));
    rx += (axis[0] * size) + (axis[2] * size_2);
    ry -= (axis[1] * size) - (axis[2] * size_2);// + axis[2] * (20 * w));
    draw_line_width(s, color, x, y, rx, ry, 3);
    if (tileset && name)
        charset_print(s, tileset, rx, ry, name);
}