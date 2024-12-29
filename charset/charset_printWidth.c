#include "alphabet_tileset.h"

/**
 ** charset_printWidth :
 ** Takes a SDL_Surface to print on,
 ** and a charset array. Set int x and int y
 ** position on screen.
 ** Set Width paramater like : seruface->w
 ** Use char *str as an ascii string input.
 ** Return: Current veertical position.
 ** Non Blocking.
 **
**/
int            charset_printWidth(SDL_Surface *s, t_ui_box *box, SDL_Surface **charset, int x, int y, uint width, uchar word, const char *str)
{
    uchar           wordSkip;
    uchar           startFlag;
    uint            wordLen;
    uint            counter;
    uint            height;
    int             _x;
    char         *p;
    char         c;
    SDL_Surface  *tile;

    ///if (!(p = (char *)str) || x < 0 || y < 0 || x + 16 >= s->w || y + 16 >= s->h) /* Original. Blocking */
    if (!(p = (char *)str)) /// Good;
        return (y + 32);
    height = (box ? (uint)((int)box->dim[1] + box->pos[1]) : s->h);
    if (y + 16 >= height - (16 + UI_BORDER_WIDTH))
        return (y + 32);
    wordSkip = 0;
    counter = 0;
    width >>= 4;
    if (width < 2)
        return (y + 32);
    width--;
    _x = x;
    startFlag = 1;
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
        if (y + 16 >= height - (16 + UI_BORDER_WIDTH))
            return (y + 32);
        if (!(tile = charset[(uint)c]))
            return (y + 32);
        if (is_printable(c)) /** Normal Character **/
        {
            blit_pos(tile, s, x, y);
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
        ///if (wordDelimiter(*p) == 1) /** Original **/
        if (wordDelimiter(*p) == 1)
            wordSkip = 0;
    }
    return (y + 32);
}