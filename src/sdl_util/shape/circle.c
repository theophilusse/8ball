#include "sdl_util.h"

void        circle(SDL_Surface *s, uchar *color, int x_centre, int y_centre, int r)
{
    int     x, y;
    int     d;

    if (!s || !color)
        return ;
    r = abs(r);
    x = 0;
    y = r;
    d = r - 1;
    while (y >= x)
    {
            put_pixel( s, color, x_centre + x , y_centre + y );
            put_pixel( s, color, x_centre + y , y_centre + x );
            put_pixel( s, color, x_centre - x , y_centre + y );
            put_pixel( s, color, x_centre - y , y_centre + x );
            put_pixel( s, color, x_centre + x , y_centre - y );
            put_pixel( s, color, x_centre + y , y_centre - x );
            put_pixel( s, color, x_centre - x , y_centre - y );
            put_pixel( s, color, x_centre - y , y_centre - x );
        if (d >= 2 * x)
        {
            d = d- 2 * x -1;
            x = x+1;
        }
        else if (d < 2 * (r-y))
        {
            d = d+ 2 * y -1;
            y = y-1;
        }
        else
        {
            d = d+2*(y-x-1);
            y = y-1;
            x = x+1;
        }
    }
}

void                 plain_circle(SDL_Surface *viewport, uchar *color, int *org, int ray)
{
    if (!viewport || !org || !color)
        return ;
    while (ray > 0)
    {
        circle(viewport, (uchar *)color, org[0], org[1], ray);
        ray--;
    }
}
