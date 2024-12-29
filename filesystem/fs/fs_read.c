#include "filesystem.h"

int         fs_read(char *path)
{
    int         fd;
	mode_t		mode = S_IRUSR | S_IWUSR /*| S_IRGRP | S_IROTH*/;

	/*DEBUG ///
	return (-1);*/
	if (!path)
		return (-1);
	///if ((fd = open(path, O_WRONLY | O_CREAT, mode)) == -1)
	if ((fd = open(path, O_RDONLY, mode)) == -1)
	{
		printf("Can't open %s !\n", path);
		return (-1);
	}
	return (fd);
}
