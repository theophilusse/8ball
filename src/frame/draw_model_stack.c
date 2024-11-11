#include "frame.h"

static void     put_zbuffer_to_backbuffer(double *zbuffer, SDL_Surface *backbuffer)
{
    int         w;
    int         h;
    int         x;
    int         y;
    uchar       rgb[4];

    rgb[3] = 255;
    w = backbuffer->w;
    h = backbuffer->h;
    y = -1;
    while (++y < h)
    {
        x = -1;
        while (++x < w)
        {
            if (zbuffer[(((y * w) + x) * 4) + 3] == DBL_MAX)
                continue ;
            rgb[0] = (uchar)zbuffer[((y * w + x) * 4)];
            rgb[1] = (uchar)zbuffer[((y * w + x) * 4) + 1];
            rgb[2] = (uchar)zbuffer[((y * w + x) * 4) + 2];
            put_pixel(backbuffer, rgb, x, y);
        }
    }
}

void     draw_model_stack(t_cam *c)
{
    int         i;
    t_camdata   *d;

    if (!c || !(d = c->data) || !d->backbuffer)
        return ;
    i = -1;
    while (++i < MAX_MODEL)
        if (d->model[i].active == 1)
            draw_f(c, d->zbuffer, d->backbuffer->w, d->backbuffer->h, (uchar *)&d->model[i]._ambiant_color, &d->model[i]);
    put_zbuffer_to_backbuffer(d->zbuffer, d->backbuffer);
}
