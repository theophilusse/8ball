#include "alphabet_tileset.h"

/**
 ** get_tile :
 ** Build a single tile from Police (image, XPM style).
 ** Used for building a charset table.
**/
SDL_Surface          *get_tile(const char *image[], const uchar *color_bg, const uchar *color_fg)
{
    SDL_Surface       *ret;
    int row, col;

    /* if (!(ret = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF, 16, 16, 32, crmask, cgmask, cbmask, camask))) */ /// Old
    if (!(ret = new_surface32(16, 16))) /// Keep. Crash ?
        return (NULL);

    row = 0;
    while (row < 16)
    {
        col = 0;
        while (col < 16)
        {
            switch (image[3+row][col])
            {
                case '0':
                    put_pixel(ret, (uchar *)color_bg, col, row);
                        break;
                case '.':
                    put_pixel(ret, (uchar *)color_fg, col, row);
                        break;
            }
            col++;
        }
        row++;
    }
    return (ret);
}
