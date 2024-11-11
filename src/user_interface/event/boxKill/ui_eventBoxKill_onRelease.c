#include "user_interface.h"

struct s_ui_event           ui_eventBoxKill_onRelease(t_mega *mega, t_ui_box *box)
{
    struct s_ui_event       event;
    int                     relClick[2];

    if (!box || !mega)
        return (ui_setDefaultEvent());
    relClick[0] = mega->mouse.mousePos[0] - box->pos[0];
    relClick[1] = mega->mouse.mousePos[1] - box->pos[1];
    if (ui_isKill(box, relClick)) /** if onRelease is on button **/
        ui_swapBox(mega->ui, mega->ui->event.handle, 0); /** Close Window **/
    event = ui_setDefaultEvent();
    ///event.handle = ui_getFrontBoxHandle(mega->ui, 255); // Paça
    return (event);
}
