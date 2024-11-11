#include "user_interface.h"

void            ui_releaseItem_simpleButton(t_box_item *item)
{
    t_simple_button         *s_button;

    if (!item)
        return ;
    if (!(s_button = item->ptr))
        return ;
    SDL_FreeSurface(s_button->srf);
    s_button->srf = NULL;
}
