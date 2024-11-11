#include "user_interface.h"

void              ui_setPos(t_userInterface *ui, uchar handle, int *pos)
{
    t_ui_box        *box;

    if (!ui || !pos || handle > UI_BOX_COUNT)
        return ;
    box = &ui->box[handle];
    box->pos[0] = pos[0];
    box->pos[1] = pos[1];
    ui->sigRefresh = 1;
}
