#include "filesystem.h"

void      *fs_abort(int fd, void *toFree, void *ret)
{
    if (fd != -1)
        close(fd);
    if (toFree)
        FREE(toFree);
    printf("ABORT\n");
    return (ret);
}
