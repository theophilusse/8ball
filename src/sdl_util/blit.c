#include "8ball.h"

void        blit_at(SDL_Surface *image, SDL_Surface *screen, int x, int y)
{
    SDL_Rect    src = {0, 0, (Uint16)image->w, (Uint16)image->h};
    SDL_Rect    dst = {x, y, 0, 0};
    SDL_BlitSurface(image, &src, screen, &dst);
}

void        blit_at_dimRect(SDL_Surface *image, SDL_Surface *screen, int xTo, int yTo, int *maxDim, int *minDim, int isBGRA)
{
    int         i;
    int         j;
    uchar       pixel[4];
    uchar       color[4];
    uchar       *pix;

    if (!image)
        return ;
    if (!screen)
        return ;
    if (!(pix = image->pixels))
    {
        printf("image->locked = %u\n", image->locked);
        return ;
    }
    j = -1;
    while (++j < image->h)
    {
        if (minDim && minDim[1] > j + yTo)
            continue;
        if (maxDim && maxDim[1] <= j + yTo)
            break;
        i = -1;
        while (++i < image->w)
        {
            if (minDim && minDim[0] > i + xTo)
                continue;
            if (maxDim && maxDim[0] <= i + xTo)
                i = image->w;
            else
            {
                uint pixelIndex;
                pixelIndex = getpixel_index(image, i, j);
                pixel[0] = pix[ pixelIndex ];
                pixel[1] = pix[ pixelIndex + 1 ];
                pixel[2] = pix[ pixelIndex + 2 ];
                pixel[3] = pix[ pixelIndex + 3 ];
                if (pixel[3] == SDL_ALPHA_OPAQUE)
                {
                    if (isBGRA == 1)
                    {
                        color[0] = pixel[2];
                        color[1] = pixel[1];
                        color[2] = pixel[0];
                        color[3] = pixel[3];
                    }
                    else
                    {
                        color[0] = pixel[0];
                        color[1] = pixel[1];
                        color[2] = pixel[2];
                        color[3] = pixel[3];
                    }
                    pixelIndex = getpixel_index(screen, xTo + i, yTo + j);
                    pixel[0] = pix[ pixelIndex ];
                    pixel[1] = pix[ pixelIndex + 1 ];
                    pixel[2] = pix[ pixelIndex + 2 ];
                    pixel[3] = pix[ pixelIndex + 3 ];
                    if (pixel[3] == SDL_ALPHA_OPAQUE)
                    {
                        if (isBGRA == 1)
                        {
                            pixel[0] = color[2];
                            pixel[1] = color[1];
                            pixel[2] = color[0];
                            pixel[3] = color[3];
                        }
                        else
                        {
                            pixel[0] = color[0];
                            pixel[1] = color[1];
                            pixel[2] = color[2];
                            pixel[3] = color[3];
                        }
                        memcpy((void *)pix, (void *)pixel, sizeof(uchar) * 4);
                    }
                }
            }
        }
    }
}

void        blit_at_dim(SDL_Surface *image, SDL_Surface *screen, int xTo, int yTo, int *maxDim, int *minDim, uchar isBGRA)
{
    /*SDL_Rect    src = {0, 0, (Uint16)image->w, (Uint16)image->h};
    SDL_Rect    dst = {x, y, 0, 0};
    SDL_BlitSurface(image, &src, screen, &dst);*/

    int         i;
    int         j;
    uchar       *pixel;
    //uchar       color[4];

    ///if (!image || !screen) /// Original
    if (!image || !image->pixels || !screen)
        return ;
    j = -1;
    printf("[%p][%p]Screen.Bpp:[%u] ; Image->Bpp[%u]\n", screen, image, screen->format->BytesPerPixel, image->format->BytesPerPixel);
    isBGRA = 1; /// DEBUG
    ///isBGRA = 0; /// DEBUG Original
    printf("image->h = %d\n", image->h); /// DEBUG
    while (++j < image->h)
    {
        if (minDim && minDim[1] > j + yTo)
            continue;
        if (maxDim && maxDim[1] <= j + yTo)
            break;
        i = -1;
        while (++i < image->w)
        {
            if (minDim && minDim[0] > i + xTo)
                continue;
            if (maxDim && maxDim[0] <= i + xTo)
                i = image->w;
            else
            {
                pixel = (uchar *)getpixel_addr(image, i, j); /// Crash . no surface->pixels
                ///if (pixel && *(pixel + 3) == SDL_ALPHA_OPAQUE)
                if (pixel && pixel)
                {
                    ///DEBUG ///
                    ///printf("pix: %p\n", pixel);///
                    if (*(pixel + 3) == SDL_ALPHA_OPAQUE)
                    { /* */
                    /*
                    if (isBGRA == 1)
                    {
                        color[0] = pixel[2];
                        color[1] = pixel[1];
                        color[2] = pixel[0];
                        color[3] = pixel[3];
                    }
                    else
                    {
                        color[0] = pixel[0];
                        color[1] = pixel[1];
                        color[2] = pixel[2];
                        color[3] = pixel[3];
                    }*/
                    ///DEBUG ///
                    ///put_pixel_dim(screen, color, xTo + i, yTo + j, minDim, maxDim); /// Crash , Keep
                    ///DEBUG ///
                    ///put_pixel(screen, color, xTo + i, yTo + j);
                    } /* */
                }
            }
        }
    }
}

void        blit(SDL_Surface *image, SDL_Surface *screen)
{
    SDL_Rect    src = {0, 0, (Uint16)image->w, (Uint16)image->h};
    SDL_Rect    dst = {0, 0, 0, 0};
    SDL_BlitSurface(image, &src, screen, &dst);
}

void        blit_and_flip(SDL_Surface *image, SDL_Surface *screen)
{
    blit(image, screen);
    SDL_Flip(screen);
}

void        blit_and_flip_at(SDL_Surface *image, SDL_Surface *screen, int x, int y)
{
    blit_at(image, screen, x, y);
    SDL_Flip(screen);
}

void        refresh(SDL_Surface *image, SDL_Surface *screen)
{
    uchar       color[4] = { 0, 64, 0, SDL_ALPHA_OPAQUE };

    DEBUG //
    return ; /// DEBUG
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 64, 0));
    blit(image, screen);
    square(image, 0, 0, image->w, image->h, color);
    SDL_Flip(screen);
}

void        refreshUI(SDL_Surface *image, SDL_Surface *screen)
{
    uchar       color[4] = { 0, 64, 0, SDL_ALPHA_TRANSPARENT };

    blit(image, screen);
    square(image, 0, 0, image->w, image->h, color);
    SDL_Flip(screen);
}
