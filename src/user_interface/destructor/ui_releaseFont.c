#include "user_interface.h"

void            ui_releaseFont(t_ui_font *ch)
{
    if (!ch)
        return ;
    free_tileset(ch->charset);
}
