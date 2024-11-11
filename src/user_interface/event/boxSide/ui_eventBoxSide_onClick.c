#include "user_interface.h"

int                 ui_eventBoxSide_onClick(t_mega *mega, uchar boxHandle, uchar sideGrab)
{
    mega->ui->event = ui_setEvent(UI_EVENT_BOXRESIZE, boxHandle);
    mega->ui->event.flag = sideGrab;
    return (0);
}
