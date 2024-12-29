#include "alphabet_tileset.h"

/**
 ** charset_printStopWidthSelection :
 ** Takes a SDL_Surface to print on,
 ** and a charset array. Set int x and int y
 ** position on screen. Set Width like surface->w to put "..." in place of overflow.
 ** Use char *str as an ascii string input.
 **
**/
/// TODO
/// TODO
/// TODO
/* void            charset_printStopWidthSelection(SDL_Surface *s, SDL_Surface **charset, int x, int y, uint width, const char *str) */
void            charset_printStopWidthSelection(SDL_Surface *s, t_ui_box *box, SDL_Surface **charset, SDL_Surface **charset_highlight,
                                    int x, int y, uint width, char *str, int *selectionIndex, int *maxDim, int *minDim)
{
    size_t           stringLength;
    uchar           startFlag;
    uint            wordLen;
    uint            counter;
    int             _x;
    char         *p;
    char         c;
    SDL_Surface  *tile;
    uint          iter;
    int           pIndex[2];

    ///if (!(p = (char *)str) || x < 0 || y < 0 || x + 16 >= s->w || y + 16 >= s->h) /* Original. Blocking */
    if (!charset || (!charset_highlight && selectionIndex) || !(p = (char *)str))
        return ;
    if (selectionIndex)
    {
        pIndex[0] = selectionIndex[0] > selectionIndex[1] ? selectionIndex[1] : selectionIndex[0];
        pIndex[1] = selectionIndex[0] > selectionIndex[1] ? selectionIndex[0] : selectionIndex[1];
    }
    else
    {
        pIndex[0] = -1;
        pIndex[1] = -1;
    }
    ///height = (box ? (uint)((int)box->dim[1] + box->pos[1]) : s->h);
    /** /// Original
    if (y + 16 >= height - (16 + UI_BORDER_WIDTH))
        return (y + 32);
    */
    stringLength = strlen(str);
    counter = 0;
    if (width < 2)
        width = 2;
        /** /// Original
        return (y + 32);
        */
    width--;
    _x = x;
    startFlag = 1;
    iter = 0;
    while ((c = *p) != '\0')
    {
        /** /// Original.
        if (y + 16 >= height - (16 + UI_BORDER_WIDTH))
            return (y + 32);
        */
        /****/
        if (is_printable(c)) /** Normal Character **/
        {
            //
            ///if (pIndex && p >= h[0] && p <= h[1])
            ///if (pIndex && pIndex[0] != -1 && pIndex[1] != -1)
            if (pIndex[0] != -1 && pIndex[1] != -1 && (iter >= (uint)pIndex[0] && iter <= (uint)pIndex[1]))
            {
                tile = charset_highlight[(uint)c];
                /** /// Original
                if (!(tile = charset_highlight[(uint)c]))
                    return (y + 32);
                */
            }
            else
            {
                tile = charset[(uint)c];
                /** /// Original
                if (!(tile = charset[(uint)c]))
                    return (y + 32);
                */
            }
            //
            /** /// Original
            blit_pos(tile, s, x, y);
            */
            ///blit_at_dim(tile, s, x + (39 + box->pos[0]), y + (box->pos[1]), maxDim, minDim, 0);
            blit_at_dim(tile, s, x, y, maxDim, minDim, 0);
            counter++;
            if (startFlag == 1)
                startFlag = 0;
        }
        x += 16;
        if (c == '\t') /** Non-Printable Character Processing **/
            x += 32;
        if (x >= s->w || *p == (uint)'\n' || (stringLength > width && counter + 2 >= width))
        {
            if (x >= s->w)
                return ;
            if (!(tile = charset[(uint)'\b']))
            {
                printf("Error Loading tile %u\n", (uint)'.');
                return ;
            }
            /*
            blit_pos(tile, s, x, y);
            blit_pos(tile, s, x + 16, y);
            blit_pos(tile, s, x + 32, y);
            */
            blit_at_dim(tile, s, x - 16, y, maxDim, minDim, 0);
            /*
            blit_at_dim(tile, s, x, y, maxDim, minDim, 0);
            blit_at_dim(tile, s, x + 16, y, maxDim, minDim, 0);
            blit_at_dim(tile, s, x + 32, y, maxDim, minDim, 0);
            */
            return ;
        }
        if ( counter >= width
            /** || x >= s->w **/ /* Original. Blocking */
            || c == (uint)'\n') /** End Of Line - Conditions **/
        {
            counter = 0;
            x = _x;
            y += 16;
        }
        p++;
        iter++;
    }
}
