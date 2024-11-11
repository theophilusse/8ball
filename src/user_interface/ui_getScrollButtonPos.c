#include "user_interface.h"

void            ui_getScrollButtonPos(t_ui_box *box, uchar axis, int *pos)
{
    t_ui_scrollbar      *bar;

    if (!box || axis >= 2 || !pos)
        return ;
    if (axis == 0)
    {
        bar = &box->horizontal_bar;
        pos[0] = (int)(bar->fPercent * bar->length) + (16 + UI_BORDER_WIDTH);
        pos[1] = box->dim[1] - (16 + UI_BORDER_WIDTH);
    }
    else
    {
        bar = &box->vertical_bar;
        pos[0] = box->dim[0] - (16 + UI_BORDER_WIDTH);
        pos[1] = (int)(bar->fPercent * bar->length) + ((16 + 16) + (UI_BORDER_WIDTH * 2));
    }
}
