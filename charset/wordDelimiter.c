#include "alphabet_tileset.h"

uchar             wordDelimiter(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
}