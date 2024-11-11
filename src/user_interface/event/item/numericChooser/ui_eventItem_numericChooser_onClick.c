#include "user_interface.h"

void            ui_eventItem_numericChooser_onClick(t_mega *mega, t_ui_box *box, uchar itemHandle, int *onClick)
{
    int             itmPos[2];

    itmPos[0] = box->content->item[itemHandle].pos[0] - box->horizontal_bar.shift;
    itmPos[1] = box->content->item[itemHandle].pos[1] - box->vertical_bar.shift;
    mega->ui->event.flag = 0;
    if (isInZone(onClick, box->content->item[itemHandle].dim, itmPos))
    {
        int     posShift[2];
        uint    dim[2];
        dim[0] = 16;
        dim[1] = 16;
        posShift[0] = itmPos[0] + (box->content->item[itemHandle].dim[0] - 16);
        posShift[1] = itmPos[1];
        ///BEEP
        mega->ui->event.flag = 1;
        if (isInZone(onClick, dim, itmPos))
        {
            mega->ui->event.flag = 2;
        }
        else if (isInZone(onClick, dim, posShift))
        {
            mega->ui->event.flag = 3;
        }
    }
    /*else
        mega->ui->event.flag = 0;*/
}
