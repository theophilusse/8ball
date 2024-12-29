#include "HeightMap.h"

void        perspective(t_grid *grid, t_conf *conf, SDL_Surface *viewport, int *rx, int *ry, uint ix, uint iy, int height)
{
    *rx = 0;
    *ry = 0;

    *rx += (ix * (20 * conf->dim[0])) + iy * (20 * conf->dim[0]);
    *ry += (iy * (20 * conf->dim[0])) - ((double)height * conf->f + ix * (20 * conf->dim[0]));
}

void        perspective_msk(t_grid *grid, t_conf *conf, SDL_Surface *viewport, int *rx, int *ry, uint ix, uint iy, int height)
{
    *rx = 0;
    *ry = 0;

    *rx += (ix * (20 * conf->dim[0])) + iy * (20 * conf->dim[0]);
    *ry += (iy * (20 * conf->dim[0])) - ((double)height * conf->f + ix * (20 * conf->dim[0]));
}
