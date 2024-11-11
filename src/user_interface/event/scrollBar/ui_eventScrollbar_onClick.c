#include "user_interface.h"

int             ui_eventScrollbar_onClick(t_mega *mega, uchar boxHandle, uchar scrollbarHandle)
{
    ///BEEP///
    /*struct s_ui_scrollbar   bar;

    bar = (scrollbarHandle == 0 ? box->horizontal_bar : box->vertical_bar);*/
    mega->ui->event = ui_setEvent(UI_EVENT_SCROLLBAR, boxHandle);
    mega->ui->event.itemHandle = (uchar)scrollbarHandle;
    DEBUG ///
    printf("scrollBarHandle IS [%u]\n", scrollbarHandle);
    mega->ui->sigRefresh = 1; /// Test
    return (0);
}
