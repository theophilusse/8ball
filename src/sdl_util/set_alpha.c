#include "sdl_util.h"

/*void        refresh(SDL_Surface *image, SDL_Surface *screen)*/
void            set_alpha(SDL_Surface *s, uchar alpha)
{
    uchar       transparent[4] = { 0, 0, 0, 0 };

    if (!s)
        return ;
    transparent[3] = alpha;
    ///SDL_FillRect(scref (!(pixl = (uchar *)getpixel_addr(s, x, y)))en, 0, SDL_MapRGB(screen->format, 0, 64, 0));
    square(s, 0, 0, s->w, s->h, transparent);
    SDL_Flip(s);
}

void            setWhitePixelsTransparent(SDL_Surface *s)
{
    uchar           *pix;
    uint            totalPix;
    uint            i;

    if (!s)
        return ;
    if (!(pix = (uchar *)s->pixels))
        return ;
    totalPix = s->w * s->h;
    i = -1;
    while (++i < totalPix)
    {
        if (pix[0] == 255 && pix[1] == 255 && pix[2] == 255)
            *(pix + 3) = SDL_ALPHA_TRANSPARENT;
        pix += 4;
    }
    return ;
}

void            blit_mergeAlpha(SDL_Surface *surface, SDL_Surface *screen)
{
    uint            i;
    uint            j;
    uchar           *pixl[2];
    uchar           color[4] = { 0, 0, 0, 0 };

    DEBUG //
    if (!surface || !screen)
        return ;
    DEBUG //
    if (surface->w != screen->w || surface->h != screen->h)
    {
        printf("blit_mergeAlpha usage : dimensions musts be equal.\n");
        return ;
    }
    DEBUG //
    i = -1;
    while (++i < surface->w)
    {
        j = -1;
        while (++j < surface->h)
        {
            ///adr = getpixel_index(surface i, j);
            pixl[0] = (uchar *)getpixel_addr(surface, i, j);
            pixl[1] = (uchar *)getpixel_addr(screen, i, j);
            ///if ( *(pixl[0] + 3) == SDL_ALPHA_OPAQUE )
            return ; // DEBUG
            if ( *(pixl[0] + 3) != SDL_ALPHA_TRANSPARENT )
            {
                *pixl[1] = *pixl[0];
                *(pixl[1] + 1) = *(pixl[0] + 1);
                *(pixl[1] + 2) = *(pixl[0] + 2);
                *(pixl[1] + 3) = SDL_ALPHA_OPAQUE;
                ///put_pixel(screen, ((uchar *)surface->pixels + adr), i, j);
                ///*((uchar *)surface->pixels + adr + 3) = SDL_ALPHA_TRANSPARENT;
            }
        }
    }
    DEBUG //
    ///SDL_Flip(screen);
}
