#ifndef SDL_UTIL_H
    #define SDL_UTIL_H

    #include "8ball.h"

    SDL_Surface             *new_surface32(uint width, uint height);
    SDL_Surface             *stretch_surface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);
    void        copy_surface(SDL_Surface *image, SDL_Surface *screen, const char *format_dst, const char *format_src);
    void            clean_surface(SDL_Surface *surface);
    void        blit(SDL_Surface *image, SDL_Surface *screen);
    void        blit_at(SDL_Surface *image, SDL_Surface *screen, int x, int y);
    void        blit_at_dimRect(SDL_Surface *image, SDL_Surface *screen, int xTo, int yTo, int *maxDim, int *minDim, int isBGRA);
    void        blit_at_dim(SDL_Surface *image, SDL_Surface *screen, int x, int y, int *maxDim, int *minDim, uchar isBGRA);
    void        blit_and_flip(SDL_Surface *image, SDL_Surface *screen);
    void        blit_and_flip_at(SDL_Surface *image, SDL_Surface *screen, int x, int y);
    void        blit_mergeAlpha(SDL_Surface *surface, SDL_Surface *screen);
    void        set_alpha(SDL_Surface *s, uchar alpha);
    void        setWhitePixelsTransparent(SDL_Surface *s);
    void        refresh(SDL_Surface *image, SDL_Surface *screen);
    void        refreshUI(SDL_Surface *image, SDL_Surface *screen);

    uint            getpixel_index(SDL_Surface *surface, int x, int y);
    void            *getpixel_addr(SDL_Surface *surface, int x, int y);
    void            put_pixel_dim_noAlpha(SDL_Surface *s, uchar *rgb, int x, int y, int *maxDim, int *minDim);
    void            put_pixel_dim(SDL_Surface *s, uchar *rgb, int x, int y, int *maxDim, int *minDim);
    void            put_pixel_noAlpha(SDL_Surface *s, uchar *rgb, int x, int y);
    void            put_pixel(SDL_Surface *s, uchar *rgb, int x, int y);
    ////void            put_pixel_rgba(SDL_Surface *s, uchar *rgba, int x, int y);
    void        square(SDL_Surface *s, int x, int y, int w, int h, uchar *rgb);
    void        square_dim(SDL_Surface *s, int x, int y, int w, int h, uchar *rgb, int *maxDim, int *minDim);
    void        square_dim_noAlpha(SDL_Surface *s, int x, int y, int w, int h, uchar *rgb, int *maxDim, int *minDim);
    void            draw_line(SDL_Surface *s, uchar *rgb, int x1, int y1, int x2, int y2);
    void            draw_line_width(SDL_Surface *s, uchar *rgb, int x1, int y1, int x2, int y2, int w);
    void        draw_line_dim(SDL_Surface *s, uchar *rgb, int x1, int y1, int x2, int y2, int *maxDim, int *minDim);

    void            mtp_color(uchar *color, double f);
    void            add_color(uchar *ca, uchar *cb, uchar *ret);

    struct s_ftData_zone    zone_upLeftCorner(void);
    int             isInCanva(SDL_Surface *canva, int *px, int *py, int isInt);
    int             isInZone(int *point, uint *dim, int *pos);
    int             isInTile(int x, int y, int *tileDim, int *onClick);

    void            print_farray(double *f, uint length, uint *mod);

    char * dtoa(char *s, double n);
    t_list          *putlist(t_list *l, const char *str);
    void            free_list(t_list *l);

    void                toggleFullscreen(t_mega *mega);
    void                setCursorPosition(t_mega *mega, int x, int y);
    void                halt_program(uchar *refresh, void *mega);
    void                super_blit(t_mega *mega);
    SDL_Surface *layer_merge(SDL_Surface **layer_stack, int sz, void (*func)(SDL_Surface *, SDL_Surface *));
    SDL_Surface *layer_popMerge(SDL_Surface **layer_stack, int sz, void (*func)(SDL_Surface *, SDL_Surface *));
    int 		        strnequ(const char *str, char *cmp, size_t sz);
    void                *ft_realloc(void *src, size_t bSz, size_t new_bSz);

    /** Shape **/
    void        circle(SDL_Surface *s, uchar *color, int x_centre, int y_centre, int r);
    void                 plain_circle(SDL_Surface *viewport, uchar *color, int *org, int ray);

    struct s_scanline       new_scanline(int pos, int xFrom, int xTo, int *width);
    int                     set_pos_lineWidth(int offset, int width);
    void                    line_hrz_width(SDL_Surface *s, uchar *rgb, struct s_scanline scan);
    void                    line_vrt_width(SDL_Surface *s, uchar *rgb, struct s_scanline scan);
    /** Shape **/
#endif // SDL_UTIL_H
