#include "filesystem.h"

void      *fs_close(int fd, void *ret)
{
    if (fd != -1)
        close(fd);
    return (ret);
}
