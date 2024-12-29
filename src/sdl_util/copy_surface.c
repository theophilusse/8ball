#include "sdl_util.h"

static int          _bad_format(const char *format)
{
    uint        i;

    i = -1;
    while (++i < 4)
        if ((format[i] == '\0' && i != 3) || format[i] < '0' || format[i] > '3')
            return (1);
    return (0);
}

void         copy_surface(SDL_Surface *image, SDL_Surface *screen, const char *format_dst, const char *format_src)
{
    ///void        blit_at_dim(SDL_Surface *image, SDL_Surface *screen,
                               ///int xTo, int yTo, int *maxDim, int *minDim, uchar isBGRA)
    /*SDL_Rect    src = {0, 0, (Uint16)image->w, (Uint16)image->h};
    SDL_Rect    dst = {x, y, 0, 0};
    SDL_BlitSurface(image, &src, screen, &dst);*/

    int         i;
    int         j;
    uchar       *pixel;
    uchar       x;
    uchar       y;
    uchar       z;
    uchar       w;
    uchar       a;
    uchar       b;
    uchar       c;
    uchar       d;
    uchar       color[4];

    if (!image || !screen)
        return ;
    if (!format_src || _bad_format(format_src))
    {
        x = 0;
        y = 1;
        z = 2;
        w = 3;
    }
    else
    {
        x = format_src[0] - '0';
        y = format_src[1] - '0';
        z = format_src[2] - '0';
        w = format_src[3] != '\0' ? format_src[3] - '0' : 255;
    }
    if (!format_dst || _bad_format(format_dst))
    {
        a = 0;
        b = 1;
        c = 2;
        d = 3;
    }
    else
    {
        a = format_dst[0] - '0';
        b = format_dst[1] - '0';
        c = format_dst[2] - '0';
        d = format_dst[3] != '\0' ? format_dst[3] - '0' : 255;
    }
    j = -1;
    while (++j < image->h)
    {
        i = -1;
        while (++i < image->w)
        {
            pixel = (uchar *)getpixel_addr(image, i, j);
            ///printf("PixAddr: %p\n", pixel); ///
            if (!pixel)
                return ;
            if (pixel && *(pixel + 3) == SDL_ALPHA_OPAQUE)
            {
                /*
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
                color[3] = pixel[3];
                */
                /*
                color[0] = 0;//pixel[0];
                color[1] = 0;
                color[2] = pixel[3];
                color[3] = pixel[3];
                */
                /*
                color[0] = pixel[3];
                color[1] = pixel[2];
                color[2] = pixel[1];
                color[3] = pixel[0];
                */
                color[a] = pixel[x];
                color[b] = pixel[y];
                color[c] = pixel[z];
                if (w != 255 && d != 255)
                {
                    color[d] = pixel[w];
                    if (color[d] != SDL_ALPHA_TRANSPARENT)
                        put_pixel(screen, color, i, j);
                }
                else
                {
                    put_pixel_noAlpha(screen, color, i, j);
                }
            }
        }
    }
}
