#include "alphabet_tileset.h"

/**
 ** charset_getOffsetHeight
 ** //retourne la position dans la chaine de caractere *str lorsque le charriot s'arrete sur onClick
 ** //si curseur n'est pas dans la chaine, la fonction retourne NULL
**/
uint            charset_getOffsetHeight(t_ui_box *box, t_ui_font *font,
                                                int x, int y, uint width, uchar word, const char *str)
{
    uchar           wordSkip;
    uchar           startFlag;
    uint            wordLen;
    uint            counter;
    int            tileDim[2];
    int             _x;
    char         *p;
    char         c;

    tileDim[0] = font->dim;
    tileDim[1] = font->dim;
    if (!box || !(p = (char *)str)) /// Good;
        return (0);

    uint        ret;

    ///ret = 0;
    ret = 16;
    wordSkip = 0;
    counter = 0;
    width >>= 4;
    if (width < 2)
        width = 2;
        ///return (ret + 32);
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
                ret += 16;
            }
        }
        if (is_printable(c)) /** Normal Character **/
        {
            counter++;
            if (startFlag == 1)
                startFlag = 0;
        }
        x += 16;
        if (c == '\t') /** Non-Printable Character Processing **/
            x += 32;
        if ( counter >= width
            || c == (uint)'\n') /** End Of Line - Conditions **/
        {
            counter = 0;
            x = _x;
            ret += 16;
        }
        p++;
        if (wordDelimiter(*p) == 1)
            wordSkip = 0;
        if (!*p)
            ///return (ret + 32);
            ///return (ret + 33); /// Test.
            ///return (ret + 48); /// Test.
            ///break;///return (ret); /// Test.
            return (ret); /// Test.
    }
    printf("charset_getOffsetHeight === [%u]\n", ret);
    ///return (ret + 32);
    ///return (ret + 48);
    ///return (ret);
    return (ret);
    ///return (ret + 33); /// Test.
}