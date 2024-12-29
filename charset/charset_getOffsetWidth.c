#include "alphabet_tileset.h"

/**
 ** charset_getOffsetWidth
 ** retourne la position dans la chaine de caractere *str lorsque le charriot s'arrete sur onClick
 ** si curseur n'est pas dans la chaine, la fonction retourne NULL
**/
int             charset_getOffsetWidth(t_ui_box *box, SDL_Surface **charset,
                                                int x, int y, uint width, uchar word, const char *str, int *relClick)
{
    uchar           wordSkip;
    uchar           startFlag;
    uint            wordLen;
    uint            counter;
    int            tileDim[2];
    int             _x;
    char         *p;
    char         c;
    int          iter;
    int subClick[2];

    ///if (!(p = (char *)str) || x < 0 || y < 0 || x + 16 >= s->w || y + 16 >= s->h) /* Original. Blocking */
    if (!box || !charset)
        return (-1);
    if (!(p = (char *)str)) /// Good;
        return (-1);
    tileDim[0] = 16;
    tileDim[1] = 16;
    ///height = box ? (uint)((int)box->dim[1] + box->pos[1]) : s->h);
    ///height = (uint)((int)box->dim[1] + box->pos[1]);
    /** /// Original.
    if (y + 16 >= height)
        return (y + 32);
    */
        ///return (-1);
    wordSkip = 0;
    counter = 0;
    width >>= 4;
    if (width < 2)
        ///return (y + 32);
        return (-1);
    width--;
    _x = x;
    int _y = y;
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
        /** /// Original
        if (y + 16 >= height - 16)
            ///return (y + 32);
            ///return (p);
            return (-1);
        */
        if (is_printable(c)) /** Normal Character **/
        {
            subClick[0] = relClick[0] - 32;
            subClick[1] = relClick[1];
            ///printf("relClick:[%d][%d]; TileAt:[%d][%d]\n", relClick[0], relClick[1], x - _x, y - _y);///
            ///if (isInTsile(x, y, tileDim, relClick) == 1) /// Original.
            ///if (isInTile(x - _x, y - _y, tileDim, relClick) == 1)
            if (isInTile(x - _x, y - _y, tileDim, subClick) == 1)
                return (iter);
            /***
                blit_pos(tile, s, x, y);
            ***/
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
        if (!*p)
            return (-1);
            ///return (-1);
    }
    ///return (y + 32);
    ///return (p);
    ///return (-1);
    return (-1);
}