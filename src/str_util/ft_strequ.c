#include "sdl_util.h"

int 		strnequ(const char *str, char *cmp, size_t sz)
{
    uint            i;

	if (!str || !cmp)
		return (0);
    /** printf("strequ: str.[%s] cmp.[%s]\n", str, cmp);**/
    i = 0;
	while (*str == *cmp)
	{
		if (!*str)
		{
			if (*str != *cmp)
				return (0);
			else
				return (1);
		}
		str++;
		cmp++;
		if (++i >= sz)
            return (1);
	}
	return (0);
}

int 		strequ(const char *str, char *cmp)
{
	if (!str || !cmp)
		return (0);
    /**printf("strequ: str.[%s] cmp.[%s]\n", str, cmp);**/
	while (*str == *cmp)
	{
		if (!*str)
		{
			if (*str != *cmp)
				return (0);
			else
				return (1);
		}
		str++;
		cmp++;
	}
	return (0);
}
