#include "user_interface.h"

void              ui_setDim(t_userInterface *ui, uchar handle, uint *dim)
{
    t_ui_box        *box;

    if (!ui || !dim || handle > UI_BOX_COUNT)
        return ;
    box = &ui->box[handle];
    box->dim[0] = dim[0];
    box->dim[1] = dim[1];
    ui->sigRefresh = 1;
}
