#include "filesystem.h"

int      obj_comment(int fd, const char *comment)
{
    char        buf[BUFSIZ];
    char        sym[3] = "# \n";
    char        *ptr;
    size_t      len;

    if (!comment || fd == -1 ||
        (len = strlen(comment) * sizeof(char)) >= BUFSIZ - 3)
        return (1);
    memcpy(ptr, &sym[0], 2 * sizeof(char));
    ptr += 2;
    memcpy(ptr, comment, len);
    ptr += len;
    memcpy(ptr, &sym[2], 1);
    write(fd, buf, sizeof(char) * 3 + len);
    return (0);
}
