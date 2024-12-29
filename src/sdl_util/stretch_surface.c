#include "user_interface.h"

SDL_Surface *stretch_surface(SDL_Surface *Surface, Uint16 Width, Uint16 Height)
{
    double      _stretch_factor_x;
    double      _stretch_factor_y;
    int         y;
    int         x;
    int         o_y;
    int         o_x;
    uchar       *addr;
    SDL_Surface *_ret;

    if(!Surface || !Width || !Height)
        return (NULL);

    /**
    if (!(_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask)))
    **/
    if (!(_ret = new_surface32(Width, Height)))
        return (NULL);
    _stretch_factor_x = ((double)Width / (double)Surface->w),
    _stretch_factor_y = ((double)Height / (double)Surface->h);
    //uchar color[4];
    y = -1;
    while (++y < Surface->h)
    {
        x = -1;
        while (++x < Surface->w)
        {
            ///ReadPixel(Surface, x, y)
            addr = (uchar *)getpixel_addr(Surface, x, y);
            //color[0] = *addr;
            //color[1] = *(addr + 1);
            //color[2] = *(addr + 2);
            //color[2] = *(addr + 3);
            o_y = -1;
            while (++o_y <= (int)_stretch_factor_y)
            {
                o_x = -1;
                while (++o_x <= (int)_stretch_factor_x)
                    ///put_pixel(_ret, color, (int)(_stretch_factor_x * x) + o_x, (int)(_stretch_factor_y * y) + o_y);
                    put_pixel(_ret, addr, (int)(_stretch_factor_x * x) + o_x, (int)(_stretch_factor_y * y) + o_y);
            }
        }
    }
    return (_ret);
}
