#include "alphabet_tileset.h"

/**
 ** charset_printStopWidth_noAlpha :
 ** Takes a SDL_Surface to print on,
 ** and a charset array. Set int x and int y
 ** position on screen. Set Width like surface->w to put "..." in place of overflow.
 ** Use char *str as an ascii string input.
 **
**/
void            charset_printStopWidth_noAlpha(SDL_Surface *s, SDL_Surface **charset, int x, int y, uint width, const char *str)
{
    uint            counter;
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
    counter = 0;
    width >>= 4;
    if (width < 2)
        return ;
    width--;
    while (*p)
    {
        if (!(tile = charset[(uint)*p]))
        {
            printf("Error Loading tile %u\n", (uint)*p);
            return ;
        }
        if (is_printable(*p))
            ///blit_pos(tile, s, x, y);
            blit_at_dim(tile, s, x, y, maxDim, minDim, 0);
        x += 16;
        if (*p == '\t')
            x += 32;
        if (x >= s->w || *p == (uint)'\n' || counter >= width)
        {
            if (x >= s->w)
                return ;
            if (!(tile = charset[(uint)'\b']))
            {
                printf("Error Loading tile %u\n", (uint)'.');
                return ;
            }
            /*blit_pos(tile, s, x - 48, y);
            blit_pos(tile, s, x - 32, y);*/
            ///blit_pos(tile, s, x - 16, y);
            blit_at_dim(tile, s, x - 16, y, maxDim, minDim, 0);
            return ;
        }
        p++;
        counter++;
    }
}