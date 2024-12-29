#include "helloworld.h"

static char		*encode_bitstream(char *data, size_t size)
{
	size_t		i;
	size_t		j;
	char		*bitstream;
	char 		c;

	if (!(bitstream = ALLOC(sizeof(char) * size * 8 + 1)))
		return (NULL);
	memset(bitstream, '\0', sizeof(char) * size * 8 + 1);
	i = -1;
	j = 0;
	while (++i < size)
	{
		c = data[i];
		bitstream[j++] = c & 0x80 ? '1' : '0';
		bitstream[j++] = c & 0x40 ? '1' : '0';
		bitstream[j++] = c & 0x20 ? '1' : '0';
		bitstream[j++] = c & 0x10 ? '1' : '0';
		bitstream[j++] = c & 0x08 ? '1' : '0';
		bitstream[j++] = c & 0x04 ? '1' : '0';
		bitstream[j++] = c & 0x02 ? '1' : '0';
		bitstream[j++] = c & 0x01 ? '1' : '0';
	}
	return (bitstream);
}

static void		encode_lsb_model(t_model *model, char *data, size_t size)
{
	char		*bitstream;
	int		i;
	int		pt;
	int		length;

	if (!(bitstream = encode_bitstream(data, size)))
		return ;
	length = strlen(bitstream);
	i = -1;
	pt = -1;
	while (++i < length)
	{
        if (i / 3 >= model->nv)
            break;
        if ((int)(model->v[i] * HELLO_DECODE_EPSILON) % 2)
            model->v[i] -= HELLO_EPSILON;
        model->v[i] += HELLO_EPSILON * (bitstream[i] == '1' ? 1 : 0);
	}
	FREE(bitstream);
}

static uint helloworld_get_buffer_size(t_model *model)
{
    if (!model)
        return (0);
    return ((model->nv * 3) / 8);
}

void inject_helloworld(t_model *model, void *payload, uint size)
{
    char        *crafted;

    if (!payload || size + 8 > helloworld_get_buffer_size(model) || !(crafted = ALLOC(size + 8)))
        return ;
    *((uint *)crafted) = model->nv;
    *((uint *)crafted + 1) = size;
    memcpy(crafted + 8, payload, size);
    encode_lsb_model(model, crafted, size + 8);
    FREE(crafted);
}
