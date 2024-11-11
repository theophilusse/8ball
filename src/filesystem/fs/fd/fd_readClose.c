#include "filesystem.h"

char         *fd_readClose(int fd, uint *buf_size)
{
    char                buffer[STRING_SIZE];
	int                 bytes_read;
    char                *retBuf;
	size_t              bSz;

	bSz = 0;
	retBuf = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, (void *)buffer, STRING_SIZE);
		if (bytes_read == -1)
            return ((char *)fs_abort(fd, retBuf, NULL));
		if (bytes_read > 0)
		{
		    if (!(retBuf = (char *)ft_realloc(retBuf, bSz, bSz + bytes_read))) /// BUG HERE
                return ((char *)fs_abort(fd, retBuf, NULL));
            memcpy((void *)((char *)retBuf + bSz), buffer, (size_t)bytes_read);
		    bSz += (size_t)bytes_read;
		}
	}
    if (!(retBuf = (char *)ft_realloc(retBuf, bSz, bSz + 1))) /// BUG HERE
        return ((char *)fs_abort(fd, retBuf, NULL));
    retBuf[bSz] = '\0';
    bSz++;
	if (buf_size)
        *buf_size = (uint)bSz;
	return ((char *)fs_close(fd, retBuf));
}
