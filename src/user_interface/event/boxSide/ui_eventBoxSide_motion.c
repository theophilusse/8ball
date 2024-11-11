#include "user_interface.h"

void            ui_eventBoxSide_motion(t_mega *mega, t_userInterface *ui, t_ui_box* box, struct s_mouse mouse)
{
    if (!box)
        return (0);

    ui_setBoxSide(ui, box, ui->event.flag, &mouse);
    box->horizontal_bar.length = ui_getScrollBarLength(box, 0);
    box->vertical_bar.length = ui_getScrollBarLength(box, 1);

    ///ui_getBoxEnvDim(ui, box); /// Test
    box->envDim[1] = ui_getBoxEnvHeight(ui, box); /// Test

    if (box->dim[0] < box->envDim[0] /**+ (39 + 18)**/)
        box->horizontal_bar.shift = (int)(box->horizontal_bar.fPercent * (float)(box->envDim[0] - (box->dim[0] /**- (39 + 18)**/))); /// Test
    else
        box->horizontal_bar.shift = 0;
    if (box->dim[1] < box->envDim[1] + (39 + 18))
        box->vertical_bar.shift = (int)(box->vertical_bar.fPercent * (float)(box->envDim[1] - (box->dim[1] - (39 + 18)))); /// Test
    else
        box->vertical_bar.shift = 0;
}
