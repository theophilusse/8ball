#include "alphabet_tileset.h"

/**
 ** load_charset :
 ** Build a charset table with the color of your choice.
 ** Return allocated pointer pointing to the resulting charset table, or NULL if error.
 **
**/
SDL_Surface         **load_charset(const uchar *color_bg, const uchar *color_fg)
{
    int                 i;
    SDL_Surface         **ret;

    charset_endian();
    if (!(ret = (SDL_Surface **)ALLOC(sizeof(SDL_Surface *) * 256))) /// LA DEDANS
        return (NULL);
    i = -1;
    while (++i < 256)
        ret[i] = get_tile(charset_default_tile, color_bg, color_fg);
    ret[(uint)'\b'] = get_tile(charset_spec_backspace, color_bg, color_fg);

    ret[(uint)'a'] = get_tile(charset_lowa, color_bg, color_fg);
    ret[(uint)'b'] = get_tile(charset_lowb, color_bg, color_fg);
    ret[(uint)'c'] = get_tile(charset_lowc, color_bg, color_fg);
    ret[(uint)'d'] = get_tile(charset_lowd, color_bg, color_fg);
    ret[(uint)'e'] = get_tile(charset_lowe, color_bg, color_fg);
    ret[(uint)'f'] = get_tile(charset_lowf, color_bg, color_fg);
    ret[(uint)'g'] = get_tile(charset_lowg, color_bg, color_fg);
    ret[(uint)'h'] = get_tile(charset_lowh, color_bg, color_fg);
    ret[(uint)'i'] = get_tile(charset_lowi, color_bg, color_fg);
    ret[(uint)'j'] = get_tile(charset_lowj, color_bg, color_fg);
    ret[(uint)'k'] = get_tile(charset_lowk, color_bg, color_fg);
    ret[(uint)'l'] = get_tile(charset_lowl, color_bg, color_fg);
    ret[(uint)'m'] = get_tile(charset_lowm, color_bg, color_fg);
    ret[(uint)'n'] = get_tile(charset_lown, color_bg, color_fg);
    ret[(uint)'o'] = get_tile(charset_lowo, color_bg, color_fg);
    ret[(uint)'p'] = get_tile(charset_lowp, color_bg, color_fg);
    ret[(uint)'q'] = get_tile(charset_lowq, color_bg, color_fg);
    ret[(uint)'r'] = get_tile(charset_lowr, color_bg, color_fg);
    ret[(uint)'s'] = get_tile(charset_lows, color_bg, color_fg);
    ret[(uint)'t'] = get_tile(charset_lowt, color_bg, color_fg);
    ret[(uint)'u'] = get_tile(charset_lowu, color_bg, color_fg);
    ret[(uint)'v'] = get_tile(charset_lowv, color_bg, color_fg);
    ret[(uint)'w'] = get_tile(charset_loww, color_bg, color_fg);
    ret[(uint)'x'] = get_tile(charset_lowx, color_bg, color_fg);
    ret[(uint)'y'] = get_tile(charset_lowy, color_bg, color_fg);
    ret[(uint)'z'] = get_tile(charset_lowz, color_bg, color_fg);

    ret[(uint)'A'] = get_tile(charset_upra, color_bg, color_fg);
    ret[(uint)'B'] = get_tile(charset_uprb, color_bg, color_fg);
    ret[(uint)'C'] = get_tile(charset_uprc, color_bg, color_fg);
    ret[(uint)'D'] = get_tile(charset_uprd, color_bg, color_fg);
    ret[(uint)'E'] = get_tile(charset_upre, color_bg, color_fg);
    ret[(uint)'F'] = get_tile(charset_uprf, color_bg, color_fg);
    ret[(uint)'G'] = get_tile(charset_uprg, color_bg, color_fg);
    ret[(uint)'H'] = get_tile(charset_uprh, color_bg, color_fg);
    ret[(uint)'I'] = get_tile(charset_upri, color_bg, color_fg);
    ret[(uint)'J'] = get_tile(charset_uprj, color_bg, color_fg);
    ret[(uint)'K'] = get_tile(charset_uprk, color_bg, color_fg);
    ret[(uint)'L'] = get_tile(charset_uprl, color_bg, color_fg);
    ret[(uint)'M'] = get_tile(charset_uprm, color_bg, color_fg);
    ret[(uint)'N'] = get_tile(charset_uprn, color_bg, color_fg);
    ret[(uint)'O'] = get_tile(charset_upro, color_bg, color_fg);
    ret[(uint)'P'] = get_tile(charset_uprp, color_bg, color_fg);
    ret[(uint)'Q'] = get_tile(charset_uprq, color_bg, color_fg);
    ret[(uint)'R'] = get_tile(charset_uprr, color_bg, color_fg);
    ret[(uint)'S'] = get_tile(charset_uprs, color_bg, color_fg);
    ret[(uint)'T'] = get_tile(charset_uprt, color_bg, color_fg);
    ret[(uint)'U'] = get_tile(charset_upru, color_bg, color_fg);
    ret[(uint)'V'] = get_tile(charset_uprv, color_bg, color_fg);
    ret[(uint)'W'] = get_tile(charset_uprw, color_bg, color_fg);
    ret[(uint)'X'] = get_tile(charset_uprx, color_bg, color_fg);
    ret[(uint)'Y'] = get_tile(charset_upry, color_bg, color_fg);
    ret[(uint)'Z'] = get_tile(charset_uprz, color_bg, color_fg);

    ret[(uint)'.'] = get_tile(charset_ponc_dot, color_bg, color_fg);
    ret[(uint)','] = get_tile(charset_ponc_comma, color_bg, color_fg);
    ret[(uint)'?'] = get_tile(charset_ponc_interrog, color_bg, color_fg);
    ret[(uint)'!'] = get_tile(charset_ponc_exclam, color_bg, color_fg);
    ret[(uint)';'] = get_tile(charset_ponc_semicol, color_bg, color_fg);
    ret[(uint)':'] = get_tile(charset_ponc_colon, color_bg, color_fg);
    ret[(uint)' '] = get_tile(charset_ponc_space, color_bg, color_fg);
    ret[(uint)'\''] = get_tile(charset_ponc_quote, color_bg, color_fg);
    ret[(uint)'"'] = get_tile(charset_ponc_doublequote, color_bg, color_fg);

    ret[(uint)'0'] = get_tile(charset_num_0, color_bg, color_fg);
    ret[(uint)'1'] = get_tile(charset_num_1, color_bg, color_fg);
    ret[(uint)'2'] = get_tile(charset_num_2, color_bg, color_fg);
    ret[(uint)'3'] = get_tile(charset_num_3, color_bg, color_fg);
    ret[(uint)'4'] = get_tile(charset_num_4, color_bg, color_fg);
    ret[(uint)'5'] = get_tile(charset_num_5, color_bg, color_fg);
    ret[(uint)'6'] = get_tile(charset_num_6, color_bg, color_fg);
    ret[(uint)'7'] = get_tile(charset_num_7, color_bg, color_fg);
    ret[(uint)'8'] = get_tile(charset_num_8, color_bg, color_fg);
    ret[(uint)'9'] = get_tile(charset_num_9, color_bg, color_fg);

    ret[(uint)'\\'] = get_tile(charset_spec_antislash, color_bg, color_fg);
    ret[(uint)'/'] = get_tile(charset_spec_slash, color_bg, color_fg);
    ret[(uint)'_'] = get_tile(charset_spec_underscore, color_bg, color_fg);
    ret[(uint)'+'] = get_tile(charset_spec_plus, color_bg, color_fg);
    ret[(uint)'-'] = get_tile(charset_spec_minus, color_bg, color_fg);
    ret[(uint)'|'] = get_tile(charset_spec_pipe, color_bg, color_fg);
    ret[(uint)'`'] = get_tile(charset_spec_graveacc, color_bg, color_fg);
    ret[(uint)'='] = get_tile(charset_spec_equal, color_bg, color_fg);
    ret[(uint)'>'] = get_tile(charset_spec_greater, color_bg, color_fg);
    ret[(uint)'<'] = get_tile(charset_spec_lower, color_bg, color_fg);

    ret[(uint)'('] = get_tile(charset_spec_open_parenthese, color_bg, color_fg);
    ret[(uint)')'] = get_tile(charset_spec_close_parenthese, color_bg, color_fg);
    ret[(uint)'{'] = get_tile(charset_spec_open_bracket, color_bg, color_fg);
    ret[(uint)'}'] = get_tile(charset_spec_close_bracket, color_bg, color_fg);
    return (ret);
}