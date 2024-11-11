#include "alphabet_tileset.h"

/**
 ** charset_print_noAlpha :
 ** Takes a SDL_Surface to print on,
 ** and a charset array. Set int x and int y
 ** position on screen. Use char *str as an ascii string input.
 **
**/
void            charset_print_noAlpha(SDL_Surface *s, SDL_Surface **charset, int x, int y, const char *str)
{
    int             _x;
    char         *p;
    SDL_Surface  *tile;
    int          maxDim[2];
    int          minDim[2];


    /** charset_print(mega->screen, mega->charset, box->pos[0] + (i * 16), box->pos[1] + (j * 16), " "); **/ // Debug.
    ///if (!(p = (char *)str) || x < 0 || y < 0 || x + 16 >= s->w || y + 16 >= s->h)
    if (!(p = (char *)str) || x < 0 || y < 0 || x + 16 > s->w || y + 16 > s->h)
        return ;
    maxDim[0] = s->w;
    maxDim[1] = s->h;
    minDim[0] = 0;
    minDim[1] = 0;
    _x = x;
    while (*p)
    {
        if (!(tile = charset[(uint)*p]))
        {
            printf("Error Loading tile %u\n", (uint)*p);
            return ;
        }
        if (is_printable(*p))
            blit_pos(tile, s, x, y);
        x += 16;
        if (*p == '\t')
            x += 32;
        if (x >= s->w || *p == (uint)'\n')
        {
            x = _x;
            y += 16;
        }
        p++;
    }
}