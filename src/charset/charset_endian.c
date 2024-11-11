#include "alphabet_tileset.h"

/**
 ** charset_endian :
 ** Set endianess.
 **
**/
void                 charset_endian(void)
{
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        crmask = 0xff000000;
        cgmask = 0x00ff0000;
        cbmask = 0x0000ff00;
        camask = 0x000000ff;
    }
    else
    {
        crmask = 0x000000ff;
        cgmask = 0x0000ff00;
        cbmask = 0x00ff0000;
        camask = 0xff000000;
    }
}