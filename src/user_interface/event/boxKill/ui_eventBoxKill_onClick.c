#include "user_interface.h"

int             ui_eventBoxKill_onClick(t_mega *mega, uchar boxHandle)
{
    if (!mega)
        return (1);
    mega->ui->event = ui_setEvent(UI_EVENT_BOXKILL, boxHandle);
    return (0);
}
