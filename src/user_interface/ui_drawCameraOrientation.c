#include "user_interface.h"

void            ui_drawCameraOrientation(SDL_Surface *s, t_cam *c, int w, int h, SDL_Surface **tileset)
{
    char        str[32];
    int         i;

    draw_axis(s, (uchar *)_red, c->ux, w, h, w - 150, 150, 100, tileset, ".X");
    draw_axis(s, (uchar *)_green, c->uy, w, h, w - 150, 150, 100, tileset, ".Y");
    draw_axis(s, (uchar *)_blue, c->uz, w, h, w - 150, 150, 100, tileset, ".Z");
    charset_print(s, tileset, w - 500, 0, "Absolute Pitch-Yaw-Roll");
    i = -1;
    while (++i < 3)
    {
        dtoa((char *)str, (double)rad_to_deg(c->pyr[i]));
        charset_print(s, tileset, w - 500, 16 + (i * 16), str);
    }
}
