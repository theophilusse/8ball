#include "user_interface.h"

void ui_swapBox(t_userInterface *ui, uchar handle, uchar active)
{
    t_ui_box        *box;

    if (!ui || handle >= UI_BOX_COUNT || !(box = &ui->box[0]))
        return ;
    /*if (old_handle != 255 && old_handle == handle)
        return ;*/
    if (box[handle].active == 1) /** BACKGROUND **/
    {
        /*if (old_handle == handle)
            ;*/
        DEBUG ///
        ///ui_background(ui, handle, 0);
        ui_background(ui, handle, active);
    }
    if (box[handle].active == 0) /** FOREGROUND **/
    {
        ///ui_foreground(ui, handle, 1);
        ui_foreground(ui, handle, active);
        DEBUG ///
    }
    ///BEEP ///
}
