#include "user_interface.h"

void        ui_eventItem_string_motion(t_mega *mega, t_userInterface *ui, t_box_item *item, int *relClick)
{
    int             swap;

    if (!mega || !ui || !item || !relClick)
        return ;
    swap = ui_stringGetPtrAt(mega, ui, item, relClick); ///
    if (swap != -1)
        ui->event.pIndex[1] = swap;
    ui->sigRefresh = 1;//Test.
}
