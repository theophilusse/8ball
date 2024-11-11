#include "user_interface.h"

int             ui_interfaceMotion(t_mega *mega, t_userInterface *ui, struct s_mouse mouse)
{
    t_ui_box        *box;

    if (ui->event.type != UI_EVENT_NONE)
    {
        box = NULL;
        if (ui->event.handle < UI_BOX_COUNT && ui->event.handle != 255)
            box = &ui->box[ui->event.handle];
        switch (ui->event.type)
        {
            case UI_EVENT_BOXKILL:
            {
                ui_eventBoxKill_motion(mega, ui, box, mouse);
                break; /** Nothing Appens for simple Buttons **/
            }
            case UI_EVENT_ITEMCLICK:
            {
                ui_eventItem_motion(mega, ui, box, mouse);
                break;
            }
            case UI_EVENT_SCROLLBAR:
            {
                /*** Scrollbar motion ***/
                ui_eventScrollbar_motion(ui, box, mouse);
                break;
            }
            case UI_EVENT_BARGRAB:
            {
                /*** Simple Button motion ***/
                ui_eventBarGrab_motion(ui, box, mouse.mouseDrag);
                break;
            }
            case UI_EVENT_BOXRESIZE:
            {
                ui_eventBoxSide_motion(mega, ui, box, mouse);
                break;
            }
            default : { break; }
        }
    }
    return (0);
}
