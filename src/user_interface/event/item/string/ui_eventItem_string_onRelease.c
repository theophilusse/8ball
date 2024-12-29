#include "user_interface.h"

struct s_ui_event           ui_eventItem_string_onRelease(t_mega *mega, t_ui_box *box, t_box_item *item, struct s_ui_event event, int *onClick)
{
    int         relClick[2];
    int         itmPos[2];

    if (!mega || !box || !item || !onClick)
        return (event);
    itmPos[0] = item->pos[0] - box->horizontal_bar.shift;
    itmPos[1] = item->pos[1] - box->vertical_bar.shift;
    relClick[0] = onClick[0] - itmPos[0];
    relClick[1] = onClick[1] - itmPos[1];
    event.pIndex[1] = ui_stringGetPtrAt(mega, mega->ui, item, relClick); ///
    if (event.pIndex[1] == -1)
        event.pIndex[0] = -1;
    mega->ui->sigRefresh = 1;
    return (event);
}
