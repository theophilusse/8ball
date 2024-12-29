#include "ascii_art_box.h"
#include <string.h>

char             smiley[119];

char            *tileset_smiley(void)
{
    return (strncpy(smiley, "   XXXX   \n  X    X  \n X      X \nX  *  *  X\nX        X\nX        X\nX  ****  X\n X  **  X \n  X    X  \n   XXXX   ", 119));
}
