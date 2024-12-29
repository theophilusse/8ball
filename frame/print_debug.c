#include "frame.h"

void            print_debug(SDL_Surface *s, t_cam *c, SDL_Surface **charset, SDL_Surface **charset_bis, int x, int y)
{
    char        str[16][32];
    int         i;

    dtoa((char *)str[0], c->o[0]); // x
    dtoa((char *)str[1], c->o[1]); // y
    dtoa((char *)str[2], c->o[2]); // z

    dtoa((char *)str[3], c->ud[0]); // z
    dtoa((char *)str[4], c->ud[1]); // z
    dtoa((char *)str[5], c->ud[2]); // z

    dtoa((char *)str[6], c->ux[0]); // x
    dtoa((char *)str[7], c->ux[1]); // x
    dtoa((char *)str[8], c->ux[2]); // x

    dtoa((char *)str[9], c->uy[0]); // y
    dtoa((char *)str[10], c->uy[1]); // y
    dtoa((char *)str[11], c->uy[2]); // y

    dtoa((char *)str[12], c->uz[0]); // z
    dtoa((char *)str[13], c->uz[1]); // z
    dtoa((char *)str[14], c->uz[2]); // z
    ///printf("XAXIS dtoa: [%s][%s][%s]\n", str[12],str[13],str[14]);

    dtoa((char *)str[15], c->focal_distance); // Focal Length

    i = -1;
    while (++i < 21)
        charset_print(s, charset, x, y + (i * 16) , "                 ");
    charset_print(s, charset_bis, x, y , "Camera  Position ");
    charset_print(s, charset, x, y + 16 , str[0]);
    charset_print(s, charset, x, y + 32 , str[1]);
    charset_print(s, charset, x, y + 48 , str[2]);
    charset_print(s, charset_bis, x, y + 64, "Camera Direction ");
    charset_print(s, charset, x, y + 80 , str[3]);
    charset_print(s, charset, x, y + 96 , str[4]);
    charset_print(s, charset, x, y + 112 , str[5]);
    charset_print(s, charset_bis, x, y + 128, "Camera X--->     ");
    charset_print(s, charset, x, y + 144 , str[6]);
    charset_print(s, charset, x, y + 160 , str[7]);
    charset_print(s, charset, x, y + 176 , str[8]);
    charset_print(s, charset_bis, x, y + 192, "Camera Y--->     ");
    charset_print(s, charset, x, y + 208 , str[9]);
    charset_print(s, charset, x, y + 224 , str[10]);
    charset_print(s, charset, x, y + 240 , str[11]);
    charset_print(s, charset_bis, x, y + 256, "Camera Z--->     ");
    charset_print(s, charset, x, y + 272 , str[12]);
    charset_print(s, charset, x, y + 288 , str[13]);
    charset_print(s, charset, x, y + 304 , str[14]);
    charset_print(s, charset_bis, x, y + 320, "Focal Length: ");
    str[15][3 + (str[15][0] == '-' ? 1 : 0)] = '\0';
        charset_print(s, charset, x + (str[15][0] == '-' ? 208 : 224), y + 320 , str[15]);
}
