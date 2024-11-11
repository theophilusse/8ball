#include "sdl_util.h"

void                line_hrz_width(SDL_Surface *s, uchar *rgb, struct s_scanline scan)
{
    int      pos[2];
    int      sDim[2];
    uchar    *pPx;
    Uint16    bpp;

    sDim[0] = s->w;
    sDim[1] = s->h;
    bpp = s->pitch / sDim[0];
    pos[0] = scan.range[0];
    pos[1] = set_pos_lineWidth(scan.pos, scan.w);
    if (pos[1] < sDim[1] && pos[1] >= 0)
    {
        if (pos[0] < 0)
            pos[0] = 0;
        if (!(pPx = getpixel_addr(s, pos[0], pos[1])))
            return ;
        while (pos[0] < scan.range[1] && pos[0] < sDim[0])
        {
            pPx[0] = rgb[0];
            pPx[1] = rgb[1];
            pPx[2] = rgb[2];
            ///
            ///pPx[3] = rgb[3];
            if (bpp == 4)
                pPx[3] = SDL_ALPHA_OPAQUE;
            ///
            pPx += bpp;
            pos[0]++;
        }
    }
    scan.w--;
    if (scan.w < 0 || scan.w == INT_MAX)
        return ;
    line_hrz_width(s, rgb, scan);
}
