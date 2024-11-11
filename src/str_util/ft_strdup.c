#include "str_util.h"

char        *ft_strdup(const char *str)
{
    uint        i;
    uint        len;
    char        *dupStr;

    if (!str || ((len = strlen(str)) == 0) ||    /** Invalid str **/
        (!(dupStr = ALLOC(sizeof(char) * (len + 1))))) /** Alloc Error **/
        return (NULL);
    i = -1;
    while (++i <= len)
        dupStr[i] = str[i];
    return (dupStr);
}
