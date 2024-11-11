#include "user_interface.h"

int             ui_eventBarGrab_onClick(t_mega *mega, uchar boxHandle)
{
    mega->ui->event = ui_setEvent(UI_EVENT_BARGRAB, boxHandle);
    /*ui_foreground(mega->ui, boxHandle, 1); /// Test
    */
    return (0);;
}
