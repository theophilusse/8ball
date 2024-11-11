#include "user_interface.h"

void            ui_clampScrollBarFactor(t_ui_box *box)
{
    if (!box)
        return ;
    if (box->horizontal_bar.fPercent < 0)
        box->horizontal_bar.fPercent = 0.0;
    if (box->horizontal_bar.fPercent > 1.0)
        box->horizontal_bar.fPercent = 1.0;
    if (box->vertical_bar.fPercent < 0)
        box->vertical_bar.fPercent = 0.0;
    if (box->vertical_bar.fPercent > 1.0)
        box->vertical_bar.fPercent = 1.0;
}
