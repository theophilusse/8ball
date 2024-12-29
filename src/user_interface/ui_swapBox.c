#include "user_interface.h"

void ui_swapBox(t_userInterface *ui, uchar handle, uchar active)
{
    t_ui_box        *box;

    printf("UI @ %p\n", ui);
    if (!ui || handle >= UI_BOX_COUNT || !(box = &ui->box[0]))
        return ;
    DEBUG //
    if (box[handle].active == 1) /** BACKGROUND **/
    {
        DEBUG //
        ui_background(ui, handle, active);
    }
    if (box[handle].active == 0) /** FOREGROUND **/
    {
        DEBUG //
        ui_foreground(ui, handle, active);
    }
    DEBUG //
    ///BEEP ///
}
