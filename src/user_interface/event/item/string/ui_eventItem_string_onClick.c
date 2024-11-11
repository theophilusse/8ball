#include "user_interface.h"

void            ui_eventItem_string_onClick(t_mega *mega, t_ui_box *box, t_box_item *item, int *onClick)
{
    int         itmPos[2];
    int         relClick[2];

    if (!mega || !box || !item || !onClick)
        return ;
    itmPos[0] = item->pos[0] - (int)box->horizontal_bar.shift;
    itmPos[1] = item->pos[1] - (int)box->vertical_bar.shift;
    relClick[0] = onClick[0] - itmPos[0];
    relClick[1] = onClick[1] - itmPos[1];
    DEBUG ///
    ///mega->ui->event.pIndex[0] = ui_stringGetPtrAt(mega, mega->ui, &box->content->item[itemHandle], relClick); /// Original.
    mega->ui->event.pIndex[0] = ui_stringGetPtrAt(mega, mega->ui, item, relClick); /// Test.
    mega->ui->event.pIndex[1] = mega->ui->event.pIndex[0];
}
