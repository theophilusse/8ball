#include "filesystem.h"

int          getValidFileName(char *buf, const char *filename, const char *extension)
{
    char        number[TINY_STRING_SIZE];
    char        strFile[TINY_STRING_SIZE];
    uint        i;

    if (!buf || !filename || !extension)
        return (1);
    strFile[0] = '\0';
    strncat(strFile, filename, 64 - 5); /// MAX_FILENAME_SIZE
    i = -1;
    while (++i < 11111)
    {
        strFile[strlen(filename)] = '\0';
        number[0] = '\0';
        itoa(i, number, 10);
        strncat(strFile, (const char *)number, 5);
        if (extension)
        {
            strcat(strFile, ".");
            strncat(strFile, extension, 4); /// MAX_EXTENSIONNAME_SIZE
        }
        if (access(strFile, F_OK) == -1)
            break;
    }
    if (i >= 11111)
        return (1);
    strncpy(buf, strFile, TINY_STRING_SIZE);
    return (0);
}
