#ifndef ALPHABET_TILESET_H
    #define ALPHABET_TILESET_H

    #include "8ball.h"

    #include "charset_lowercase.h"
    #include "charset_uppercase.h"
    #include "charset_numbers.h"
    #include "charset_ponctuation.h"
    #include "charset_special.h"

    /**
     ** Author : ttrossea
     ** charset.c :
     ** Contain charset_print and several charset table loading functions.
     **
     ** Use load_charset and charset_print to display your text on an SDL_Surfce!
     **
     ** - charset_endian
     ** - blit_pos
     ** - get_tile
     ** - load_charset
     ** - is_printable
     ** - charset_print
     ** - ...
     **
    **/

    /**
     ** Charset's color mask.
     **
    **/
    Uint32          crmask, cgmask, cbmask, camask;

    uchar             wordDelimiter(char c);
    uint              wordLength(char *str);

    void                charset_endian(void);
    int                 is_printable(char c);
    void                blit_pos(SDL_Surface *image, SDL_Surface *screen, int x, int y);
    SDL_Surface         *get_tile(const char *image[], const uchar *color_bg, const uchar *color_fg);


    void            free_tileset(SDL_Surface **tileset);


    SDL_Surface    **load_charset(const uchar *color_bg, const uchar *color_fg);

    /** Voir papier **/
    void            gprintf(struct s_ftData_gTextData data, char *form, ...);

    void           charset_print_noAlpha(SDL_Surface *s, SDL_Surface **charset, int x, int y, const char *str);
    void           charset_print(SDL_Surface *s, SDL_Surface **charset, int x, int y, const char *str);

    int            charset_printWidth(SDL_Surface *s, t_ui_box *box, SDL_Surface **charset,
                                                int x, int y, uint width, uchar word, const char *str);

    int            charset_printWidthSelection(SDL_Surface *s, t_ui_box *box, SDL_Surface **charset, SDL_Surface **charset_highlight,
                                                int x, int y, uint width, uchar word, char *str, int *selectionIndex, int *maxDim, int *minDim);

    void           charset_printStopWidth_noAlpha(SDL_Surface *s, SDL_Surface **charset, int x, int y, uint width, const char *str);
    void           charset_printStopWidth(SDL_Surface *s, SDL_Surface **charset, int x, int y, uint width, const char *str);

    int             charset_getOffsetWidth(t_ui_box *box, SDL_Surface **charset,
                                                int x, int y, uint width, uchar word, const char *str, int *relClick);

    uint            charset_getOffsetHeight(t_ui_box *box, t_ui_font *font,
                                                int x, int y, uint width, uchar word, const char *str);

    void            charset_printStopWidthSelection(SDL_Surface *s, t_ui_box *box, SDL_Surface **charset, SDL_Surface **charset_highlight, int x, int y, uint width, char *str, int *selectionIndex, int *maxDim, int *minDim);;
    ///void            charset_printStopWidthSelection(SDL_Surface *s, t_ui_box *box, SDL_Surface **charset, SDL_Surface **charset_highlight, int x, int y, uint width, char *str, int *selectionIndex, int *maxDim, int *minDim)

#endif // ALPHABET_TILESET_H
