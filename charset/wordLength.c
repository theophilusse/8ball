#include "alphabet_tileset.h"

uint             wordLength(char *str)
{
    uint            counter;

    if (!str)
        return (0);
    counter = 0;
    while (*str && wordDelimiter(*str) == 0)
    {
        str++;
        counter++;
    }
    return (counter);
}