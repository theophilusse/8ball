#include "alphabet_tileset.h"

/**
 ** is_printable :
 ** Takes a signed char c.
 ** Return 1 if c is printable.
 **
**/
int                 is_printable(char c)
{
    if (c >= 32 && c <= 126)
        return (1);
    return (0);
}