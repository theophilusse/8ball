#include "user_interface.h"

void            ui_eventItem_simpleButton_onClick(t_mega *mega, t_ui_box *box, uchar itemHandle, int *onClick)
{
    int             itmPos[2];
    DEBUG ///
    ///BEEP
    /// Test ///
    /*relClick[0] = onClick[0] - box->content->item[itemHandle].pos[0];
    relClick[1] = onClick[1] - box->content->item[itemHandle].pos[1];*/
    /*relClick[0] = onClick[0] - box->content->item[itemHandle].pos[0];
    relClick[1] = onClick[1] - box->content->item[itemHandle].pos[1];*/
    /// Test ///
    /// Test.
    /*relClick[0] = onClick[0] - item->pos[0];
    relClick[1] = onClick[1] - item->pos[1];*/
    /// Test.
    ///if (isInZone(relClick, box->content->item[itemHandle].dim, box->content->item[itemHandle].pos))
    itmPos[0] = box->content->item[itemHandle].pos[0] - box->horizontal_bar.shift;
    itmPos[1] = box->content->item[itemHandle].pos[1] - box->vertical_bar.shift;
    if (isInZone(onClick, box->content->item[itemHandle].dim, itmPos))
    {
        ///BEEP
        ///if (isInZone(onClick, box->content->item[itemHandle].dim, box->content->item[itemHandle].pos))
        mega->ui->event.flag = 1;
    }
    else
        mega->ui->event.flag = 0;
}
