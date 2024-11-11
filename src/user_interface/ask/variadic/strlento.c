#include "user_interface.h"

uint     strlento(char *str, char c)
{
    uint        i;
    char        sym;

    if (!str)
        return (0);
    i = 0;
    while (*str)
    {
        sym = *str;
        if (sym == c)
            return (i);
        str++;
        i++;
    }
    return (i);
}
