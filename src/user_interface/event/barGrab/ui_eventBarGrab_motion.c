#include "user_interface.h"

void            ui_eventBarGrab_motion(t_userInterface *ui, t_ui_box *box,  int *mouseDrag)
{
    int                 newPos[2];
    /*uint                newDim[2];*/

    if (!box || !ui || !mouseDrag)
        return ;
    /*if (ui_isKill(box, mega->mouse.mousePos))
        ui_swapBox(mega->ui, mega->ui->event.handle);
    */
    newPos[0] = mouseDrag[0] + box->pos[0];
    newPos[1] = mouseDrag[1] + box->pos[1];
    ui_setPos(ui, ui->event.handle, newPos);
}
