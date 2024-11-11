#include "sdl_util.h"

void                line_vrt_width(SDL_Surface *s, uchar *rgb, struct s_scanline scan)
{
    int      pos[2];
    int      sDim[2];
    uchar    *pPx;
    Uint16    bpp;
    uint      pitch;

    sDim[0] = s->w;
    sDim[1] = s->h;
    bpp = s->pitch / sDim[1];
    pitch = s->pitch;
    pos[0] = scan.pos;
    pos[1] = scan.range[0];
    if (pos[0] < sDim[0] && pos[0] >= 0)
    {
        if (pos[1] < 0)
            pos[1] = 0;
        if (!(pPx = getpixel_addr(s, pos[0], pos[1])))
            return ;
        while (pos[1] < scan.range[1] && pos[1] < sDim[1])
        {
            pPx[0] = rgb[0];
            pPx[1] = rgb[1];
            pPx[2] = rgb[2];
            ///
            ///pPx[3] = rgb[3];
            if (bpp == 4)
                pPx[3] = SDL_ALPHA_OPAQUE;
            ///
            pPx += pitch;
            pos[1]++;
        }
    }
    scan.pos = scan.w * ((scan.w % 2) ? -1 : 1);
    scan.w--;
    if (scan.w < 0)
        return ;
    line_vrt_width(s, rgb, scan);
}
