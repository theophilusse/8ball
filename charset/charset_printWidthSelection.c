#include "alphabet_tileset.h"

/**
 ** charset_printWidthSelection :
 ** Takes a SDL_Surface to print on,
 ** and a charset array. Set int x and int y
 ** position on screen.
 ** Set Width paramater like : seruface->w
 ** Use char *str as an ascii string input.
 ** If char **pStr is non a non-null value, highlight chars between pStr[0] and pStr[1] pointers.
 ** Return: Current veertical position.
 ** Non Blocking.
 **
**/
int            charset_printWidthSelection(SDL_Surface *s, t_ui_box *box, SDL_Surface **charset, SDL_Surface **charset_highlight,
                                           int x, int y, uint width, uchar word, char *str, int *selectionIndex, int *maxDim, int *minDim)
{
    uchar           wordSkip;
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
        return (y + 32);
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
    wordSkip = 0;
    counter = 0;
    width >>= 4;
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
        if (word == SDL_TRUE)
        {
            if ( (wordLen = wordLength(p)) > width && (wordDelimiter(*(p - 1)) == 0) )
                wordSkip = 1;
            else if (wordSkip == 0 && (counter != 0 && ((word == SDL_TRUE && counter + wordLen >= width) || counter >= width)))
            {
                counter = 0;
                x = _x;
                y += 16;
            }
        }
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
            /// Original
            ///blit_pos(tile, s, x, y); /// dont Keep
            ///blit_at_dimRect(tile, s, x, y, maxDim, minDim, 0); /// Crash.
            printf("C:[%u] x:%d y:%d  maxDim[%d][%d] minDim[%d][%d]\n", (uint)c, x + (39 + box->pos[0]), y + (box->pos[1]), maxDim[0], maxDim[1], minDim[0], minDim[1]); /// DEBUG ///
            blit_at_dim(tile, s, x + (39 + box->pos[0]), y + (box->pos[1]), maxDim, minDim, 0); /// Crash ???
            counter++;
            if (startFlag == 1)
                startFlag = 0;
        }
        x += 16;
        if (c == '\t') /** Non-Printable Character Processing **/
            x += 32;
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
        ///if (wordDelimiter(*p) == 1) /** Original **/
        if (wordDelimiter(*p) == 1)
            wordSkip = 0;
    }
    ///return (y + 32);
    return (y + 16);
    ///return (y); // Bad.
}
