#include "HeightMap.h"

double             *get_heightmap(SDL_Surface *img)
{
    uchar               *p;
    int                 i;
    int                 j;
    double               *heightmap;
    double               *m;
    SDL_PixelFormat     *fmt;

    if (!(heightmap = (double *)malloc(sizeof(double) * (img->w * img->h))) || !(fmt = img->format))
        return ((double *)NULL);
    m = heightmap;
    i = -1;
    if (fmt->BytesPerPixel != 3 && fmt->BytesPerPixel != 4)
        return ((double *)NULL);
    while (++i < (int)(img->w * img->h))
    {
        m[i] = 0;
        p = (uchar *)getpixel_addr(img, i % img->w, i / img->h);
        j = 3;
        if (p)
        {
            while (j--)
                m[i] += p[j];
            m[i] /= 3;
        }
    }
    return (heightmap);
}

/*static SDL_Surface      *get_static_mask(const char *mask_file)
{
    SDL_Surface         *ret;

    if (!mask_file || !(ret = SDL_LoadBMP(mask_file)))
        return ((SDL_Surface *)NULL);
    return (ret);
}*/

t_grid          *get_grid(const char *file, SDL_Surface **img)
{
    SDL_Surface         *bmp;
    t_grid              *grid;

    if (!(bmp = SDL_LoadBMP(file)) ||
        !(grid = (t_grid *)malloc(sizeof(struct s_grid))))
    {
        printf("BMP %p\nSDL : %s\n", bmp, SDL_GetError());
        return ((t_grid *)NULL);
    }
    *img = bmp;
    printf("bmp: w[%d] h[%d]\n", bmp->w, bmp->h); ///
    grid->x = bmp->w;
    grid->y = bmp->h;
    grid->sz = grid->x * grid->y;
    grid->ptr = NULL;
    grid->conf = NULL;
    grid->persp = 0;
    if (!(grid->ptr = get_heightmap(bmp)))
        return ((t_grid *)NULL);
    /*if (!(grid->mask = get_static_mask("rc/MASK_HEIGHTMAP.bmp")))
        return ((t_grid *)NULL);*/
    return (grid);
}
