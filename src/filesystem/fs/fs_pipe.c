#include "filesystem.h"

int 			fs_pipe(char *in_path, char *out_path, int *fd_in, int *fd_out)
{
	mode_t		mode = S_IRUSR | S_IWUSR /*| S_IRGRP | S_IROTH*/;

	if (!in_path || !fd_in)
		return (1);
	if ((*fd_in = open(in_path, O_RDONLY, mode)) == -1)
	{
		printf("Can't open %s !\n", in_path);
		return (1);
	}
	if (fd_out && out_path && \
		(*fd_out = open(out_path, O_WRONLY | O_CREAT, mode)) == -1)
	{
		printf("Can't open %s !\n", out_path);
		close(*fd_in);
		return (1);
	}
	return (0);
}
