#include "HeightMap.h"

void        square_add(t_grid *data, int *click, Uint8 button, t_conf *conf)
{
    double            *cptr;
    int             i;
    int             j;

    if (button&SDL_BUTTON(1) || button&SDL_BUTTON(3))
    {
        click[0] -= conf->offset[0];
        click[1] -= conf->offset[1];
        click[0] /= conf->dim[0];
        click[1] /= conf->dim[1];
        cptr = data->ptr + (click[1] * data->x + click[0]);

        j = -conf->mouse_rad * conf->dim[1];
        while (j <= conf->mouse_rad * conf->dim[0])
        {
            i = -conf->mouse_rad * conf->dim[0];
            while (i < conf->mouse_rad * conf->dim[0])
            {
                if (click[0] + i < 0 || (uint)(click[0] + i) >= data->x || click[1] + j < 0 || (uint)(click[1] + j) >= data->y)
                {
                    i++;
                    continue;
                }
                if (((j + click[1]) * data->x) + i + click[0] >= 0 && ((j + click[1]) * data->x) + i + click[0] < (data->x * data->y) &&
                    i + click[0] > 1) // Meh ??
                {
                    if (button&SDL_BUTTON(1))
                    {
                        *(cptr + (j * data->x) + i) += conf->mouse_int;
                        if (*(cptr + (j * data->x) + i) > 255)
                            *(cptr + (j * data->x) + i) = 255;
                    }
                    else
                    {
                        *(cptr + (j * data->x) + i) -= conf->mouse_int;
                        if (*(cptr + (j * data->x) + i) < 0)
                            *(cptr + (j * data->x) + i) = 0;
                    }
                }
                i++;
            }
            j++;
        }
    }
}

void        square_add_grad(t_grid *data, int *click, Uint8 button, t_conf *conf)
{
    double            *cptr;
    int             i;
    int             j;

    if (button&SDL_BUTTON(1) || button&SDL_BUTTON(3))
    {
        click[0] -= conf->offset[0];
        click[1] -= conf->offset[1];
        click[0] /= conf->dim[0];
        click[1] /= conf->dim[1];
        cptr = data->ptr + (click[1] * data->x + click[0]);

        j = -conf->mouse_rad * conf->dim[1];
        while (j <= conf->mouse_rad * conf->dim[0])
        {
            i = -conf->mouse_rad * conf->dim[0];
            while (i < conf->mouse_rad * conf->dim[0])
            {
                if (click[0] + i < 0 || (uint)(click[0] + i) >= data->x || click[1] + j < 0 || (uint)(click[1] + j) >= data->y)
                {
                    i++;
                    continue;
                }
                if (((j + click[1]) * data->x) + i + click[0] >= 0 && ((j + click[1]) * data->x) + i + click[0] < (data->x * data->y) &&
                    i + click[0] > 1) // Meh ??
                {
                    if (button&SDL_BUTTON(1))
                    {
                        *(cptr + (j * data->x) + i) += conf->mouse_int;
                        if (*(cptr + (j * data->x) + i) > 255)
                            *(cptr + (j * data->x) + i) = 255;
                    }
                    else
                    {
                        *(cptr + (j * data->x) + i) -= conf->mouse_int;
                        if (*(cptr + (j * data->x) + i) < 0)
                            *(cptr + (j * data->x) + i) = 0;
                    }
                }
                i++;
            }
            j++;
        }
    }
}

void        square_del(t_grid *data, int *click, Uint8 button, t_conf *conf)
{
    double            *cptr;
    int             i;
    int             j;

    DEBUG //
    if (button&SDL_BUTTON(1) || button&SDL_BUTTON(3))
    {
        click[0] -= conf->offset[0];
        click[1] -= conf->offset[1];
        click[0] /= conf->dim[0];
        click[1] /= conf->dim[1];
        cptr = data->ptr + (click[1] * data->x + click[0]);
        j = -conf->mouse_rad * conf->dim[1];
        while (j <= conf->mouse_rad * conf->dim[0])
        {
            i = -conf->mouse_rad * conf->dim[0];
            while (i < conf->mouse_rad * conf->dim[0])
            {
                if (click[0] + i < 0 || (uint)(click[0] + i) >= data->x || click[1] + j < 0 || (uint)(click[1] + j) >= data->y)
                {
                    i++;
                    continue;
                }
                if (((j + click[1]) * data->x) + i + click[0] >= 0 && ((j + click[1]) * data->x) + i + click[0] < (data->x * data->y) &&
                    i + click[0] > 1) // Meh ??
                {
                    if (button&SDL_BUTTON(3))
                        *(cptr + (j * data->x) + i) = 255; /// Full
                    else
                        *(cptr + (j * data->x) + i) = 0; /// Zero
                }
                i++;
            }
            j++;
        }
    }
}
